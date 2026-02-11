#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main(void) {
    char *input_line = NULL;
    size_t len = 0;
    char *args[100];
    pid_t pid;
    int status;

    while(1) {
        if(isatty(STDIN_FILENO))
            printf("$ ");

        if(getline(&input_line, &len, stdin) == -1) {
            printf("\nBye!\n");
            break;
        }

        // Remove newline
        input_line[strcspn(input_line, "\n")] = 0;

        int arg_count = 0;
        char *word = strtok(input_line, " \t");
        while(word && arg_count < 99) {
            args[arg_count++] = word;
            word = strtok(NULL, " \t");
        }
        args[arg_count] = NULL;

        if(!args[0]) continue;

        pid = fork();
        if(pid == 0) {
            if(execve(args[0], args, environ) == -1) {
                fprintf(stderr, "Can't run '%s'\n", args[0]);
                exit(1);
            }
        } else {
            wait(&status);
        }
    }

    free(input_line);
    return 0;
}
