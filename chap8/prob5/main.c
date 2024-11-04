#include <stdio.h>
#include <unistd.h>

int main() {    
    printf("My process NUM : [%d] \n", getpid()); 
    printf("My parent NUM  : [%d] \n", getppid()); 
}

