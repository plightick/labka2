#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int firstCheck(char *input) {
    if (input[0] == '-') {
        for (int i = 1; input[i] != '\n' && input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                return 0;
            }
        }
    } else {
        for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                return 0;
            }
        }
    }
    return 1;
}

int secondCheck(char* input, int* integer) {
    int temp;
    if (firstCheck(input) && sscanf(input, "%d", &temp) == 1) {
        *integer = temp;
        return 1;
    } else {
        return 0;
    }
}

int p() {
    char in[20];
    int Int = 0;
    while (1) {
        fgets(in, sizeof(in), stdin);
        if (secondCheck(in, &Int) == 1) {
            break;
        } else if (in[0] == '\n') {
            return INT_MIN;
        } else {
            printf("Invalid input. Please enter an integer: ");
        }
    }
    return Int;
}

int check(int a, int b) {
    int c;
    while (1) {
        c = p();
        if (c == INT_MIN) {
            return INT_MIN;
        }
        if (c >= a && c <= b) {
            break;
        } else {
            printf("Input out of range. Please enter a number between %d and %d: ", a, b);
        }
    }
    return c;
}

int checker(int value) {
    int valid = 0;
    while (!valid) {
        printf("Enter a number (1 or 2): ");
        if (scanf("%d", &value) == 1) {
            if (value == 1 || value == 2) {
                valid = 1;
            } else {
                printf("Invalid input. Please enter 1 or 2.\n");
            }
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

void foundMinAndMax(const char *filename, int* max, int* min) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error");
        return;
    }

    *max = INT_MIN;
    *min = INT_MAX;
    int num;

    while (fscanf(file, "%d", &num) == 1) {
        if (*max < num) *max = num;
        if (*min > num) *min = num;
    }

    fseek(file, 0 ,SEEK_SET);

    printf("Minimal value: \n");

    while (fscanf(file, "%d", &num) == 1) {
        if(*min == num){
            printf("%d\n", num);
        }
    }

    fclose(file);
}

void readingFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error");
        return;
    }

    int num;

    while (fscanf(file, "%d", &num) == 1) {
        printf("%d\n", num);
    }

    fclose(file);
}

void swapValue(const char *filename, int min, int max) {
    FILE *file = fopen(filename, "r"); 
    if (!file) {
        perror("Error");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error");
        fclose(file);
        return;
    }

    char line[20]; 
    int num;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d", &num) == 1) {  
            if (num == max) {
                fprintf(tempFile, "%10d\n", min);  
            } else if (num == min) {
                fprintf(tempFile, "%10d\n", max); 
            } else {
                fprintf(tempFile, "%s", line); 
            }
        } else {
            fprintf(tempFile, "%s", line); 
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);           
    rename("temp.txt", filename); 
}

void fillingOutTheFile(const char *filename) {
    FILE *file = fopen(filename, "w+");
    if (!file) {
        perror("Error");
        return;
    }

    printf("Press Enter on an empty line to finish:\n");

    int min, max;

    while (1) {
        int number = check(INT_MIN, INT_MAX);

        if (number == INT_MIN) {
            break;
        }

        fprintf(file, "%10d\n", number);
    }

    fclose(file);

    printf("File contents:\n");
    readingFile(filename);

    foundMinAndMax(filename, &max, &min);
    swapValue(filename, min, max);

    printf("New file contents:\n");
    readingFile(filename);

}
