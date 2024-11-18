#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (execvp(args[0], args) == -1) {
        perror("execvp failed");
    }
}

void redirect_output(char *cmd, char *outfile) {
    int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execute_command(cmd);
}

void redirect_input(char *cmd, char *infile) {
    int fd = open(infile, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    execute_command(cmd);
}

int main() {
    char shell_input[MAX_CMD_LENGTH];

    while (1) {
        printf("[shell] ");
        if (!fgets(shell_input, sizeof(shell_input), stdin)) {
            break;
        }
        
        shell_input[strcspn(shell_input, "\n")] = 0;

        if (strlen(shell_input) == 0) {
            continue;
        }

        if (shell_input[strlen(shell_input) - 1] == '&') {
            shell_input[strlen(shell_input) - 1] = 0;
            if (fork() == 0) {
                execute_command(shell_input);
                exit(0);
            }
        }
        else if (strstr(shell_input, ">") != NULL) {
            char *cmd = strtok(shell_input, ">");
            char *outfile = strtok(NULL, ">");
            redirect_output(cmd, outfile);
        }
        else if (strstr(shell_input, "<") != NULL) {
            char *cmd = strtok(shell_input, "<");
            char *infile = strtok(NULL, "<");
            redirect_input(cmd, infile);
        }
        else {
            char *token = strtok(shell_input, ";");
            while (token != NULL) {
                if (fork() == 0) {
                    execute_command(token);
                    exit(0);
                }
                token = strtok(NULL, ";");
            }
        }
    }
    return 0;
}

