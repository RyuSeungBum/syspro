#include <stdio.h>

static void exit_handler1(void);
static void exit_handler2(void);

int main(void) {
    if (atexit(exit_handler1) != 0)	
        perror("exit_handler1 unable"); 
    if (atexit(exit_handler2) != 0) 	
        perror("exit_handler2 unable"); 
    printf("END main \n"); 
    exit(0);
}

static void exit_handler1(void) {
    printf("First exit dispose\n"); 
}

static void exit_handler2(void) {
    printf("Second exit dispose\n"); 
}

