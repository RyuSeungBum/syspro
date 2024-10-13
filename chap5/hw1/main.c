#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

void readFile(char savedText[MAX_LINES][MAX_LENGTH], int *lineCount) {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    while (fgets(savedText[*lineCount], MAX_LENGTH, file) != NULL) {
        (*lineCount)++;
        if (*lineCount >= MAX_LINES) break;
    }

    fclose(file);
}

void printLines(char savedText[MAX_LINES][MAX_LENGTH], int lineCount, char *input) {
    if (strcmp(input, "*") == 0) {
        // 모든 줄 출력
        for (int i = 0; i < lineCount; i++) {
            printf("%d: %s", i + 1, savedText[i]);
        }
        return;
    }

    char *token = strtok(input, ",");
    while (token != NULL) {
        if (strchr(token, '-')) {
            int start, end;
            sscanf(token, "%d-%d", &start, &end);
            for (int i = start - 1; i <= end - 1 && i < lineCount; i++) {
                printf("%d: %s", i + 1, savedText[i]);
            }
        } else {
            int lineNumber = atoi(token);
            if (lineNumber > 0 && lineNumber <= lineCount) {
                printf("%d: %s", lineNumber, savedText[lineNumber - 1]);
            }
        }
        token = strtok(NULL, ",");
    }
}

int main() {
    char savedText[MAX_LINES][MAX_LENGTH];
    int lineCount = 0;

    readFile(savedText, &lineCount);

    char input[100];
    printf("input : ");
    fgets(input, sizeof(input), stdin);
    
    input[strcspn(input, "\n")] = 0;

    printLines(savedText, lineCount, input);

    return 0;
}

