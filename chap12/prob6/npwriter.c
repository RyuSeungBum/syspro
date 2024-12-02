#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 100

int main() 
{
    int fd, length, i;
    char message[MAXLINE];

    mkfifo("myPipe", 0666);

    do {
        fd = open("myPipe", O_WRONLY);
        if (fd == -1) sleep(1);
    } while (fd == -1);

    sprintf(message, "Hello from PID %d", getpid());
    length = strlen(message) + 1;

    for (i = 0; i < 4; i++) {
        write(fd, message, length);
        sleep(3);
    }
    
    close(fd);
    return 0;
}

