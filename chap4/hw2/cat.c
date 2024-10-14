#include <stdio.h>
#include <stdlib.h>

void print_file(FILE *fp, int show_line_numbers) {
    int c;
    int line_number = 1;
    int is_first_line = 1;
    int last_char = 0;  

    while ((c = getc(fp)) != EOF) {
        if (show_line_numbers && is_first_line) {
            printf("%d ", line_number);
            is_first_line = 0;
        }

        putc(c, stdout);
        last_char = c;  
        
        if (c == '\n') {
            line_number++;
            if (show_line_numbers) {
                printf("%d ", line_number);
            }
            is_first_line = 1;
        }
    }

    if (show_line_numbers && last_char != '\n') {
        printf("%d ", line_number);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int show_line_numbers = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'n') {
            show_line_numbers = 1;
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror("Unable");
                exit(EXIT_FAILURE);
            }
            print_file(fp, show_line_numbers);
            fclose(fp);
        }
    }

    if (argc < 2) {
        print_file(stdin, show_line_numbers);
    }

    return 0;
}

