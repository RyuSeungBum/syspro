#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_environment_variable(const char *var_name) {
    const char *value = getenv(var_name);
    if (value) {
        printf("%s=%s\n", var_name, value);
    } else {
        printf("Environment variable %s does not exist.\n", var_name);
    }
}

void print_user_info() {
    printf("My Realistic User ID : %d (%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("My Valid User ID : %d (%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
}

void print_group_info() {
    printf("My Realistic Group ID : %d (%s)\n", getgid(), getgrgid(getgid())->gr_name);
    printf("My Valid Group ID : %d (%s)\n", getegid(), getgrgid(getegid())->gr_name);
}

void print_process_info() {
    printf("My Process Number : [%d]\n", getpid());
    printf("My Parent's Process Number : [%d]\n", getppid());
}

void print_all_environment_variables() {
    extern char **environ;
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Please enter an option.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                print_environment_variable(argv[i + 1]);
                i++;
            } else {
                print_all_environment_variables();
            }
        } else if (strcmp(argv[i], "-u") == 0) {
            print_user_info();
        } else if (strcmp(argv[i], "-g") == 0) {
            print_group_info();
        } else if (strcmp(argv[i], "-i") == 0) {
            printf("my process number : [%d]\n", getpid());
        } else if (strcmp(argv[i], "-p") == 0) {
            printf("my parent's process number : [%d]\n", getppid());
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}

