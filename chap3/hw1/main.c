#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX_LINES 5
#define MAX_LENGTH MAXLINE

int main() {
    char lines[MAX_LINES][MAX_LENGTH];
    char temp[MAX_LENGTH];
    int i = 0;

    while (i < MAX_LINES) {
        fgets(lines[i], MAX_LENGTH, stdin);
        lines[i][strcspn(lines[i], "\n")] = 0;
        i++;
    }

    for (int j = 0; j < MAX_LINES - 1; j++) {
        for (int k = 0; k < MAX_LINES - 1 - j; k++) {
            if (strlen(lines[k]) < strlen(lines[k + 1])) {
                copy(lines[k], temp);
                copy(lines[k + 1], lines[k]);
                copy(temp, lines[k + 1]);
            }
        }
    }

    for (int j = 0; j < MAX_LINES; j++) {
        printf("%s\n", lines[j]);
    }

    return 0;
}

