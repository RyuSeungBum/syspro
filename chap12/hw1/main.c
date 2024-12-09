#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(pipefd[1]);
        read(pipefd[0], buf, sizeof(buf));
        printf("Recv: [%d] %s\n", getpid(), buf);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]);
        const char *message = "Hello from PID";
        snprintf(buf, sizeof(buf), "%s %d", message, getpid());
        write(pipefd[1], buf, strlen(buf) + 1);
        printf("Send: [%d] %s\n", getpid(), buf); 
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}

