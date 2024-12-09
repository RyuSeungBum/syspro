#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid1, cpid2;
    char buf[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("parent process start\n");

    cpid1 = fork();

    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) {
        close(pipefd[0]);
        printf("input string: ");
        fgets(buf, sizeof(buf), stdin);
        write(pipefd[1], buf, strlen(buf) + 1);
        close(pipefd[1]);
        _exit(EXIT_SUCCESS);
    } else {
        cpid2 = fork();

        if (cpid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid2 == 0) {
            close(pipefd[1]);
            read(pipefd[0], buf, sizeof(buf));
            printf("I LOVE PROGRAMMING\n");
            close(pipefd[0]);
            _exit(EXIT_SUCCESS);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

