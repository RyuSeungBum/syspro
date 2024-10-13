#include <stdio.h>
#include <stdlib.h>

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

void printReversedLines(char savedText[MAX_LINES][MAX_LENGTH], int lineCount) {
    for (int i = lineCount - 1; i >= 0; i--) {
        printf("%s", savedText[i]);
    }
}

int main() {
    char savedText[MAX_LINES][MAX_LENGTH];
    int lineCount = 0;

    readFile(savedText, &lineCount);

    printReversedLines(savedText, lineCount);

    return 0;
}
