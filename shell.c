#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - simple UNIX shell (Task 0)
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char *argv[2];

    while (1)
    {
        /* Display prompt only in interactive mode */
        if (isatty(STDIN_FILENO))
        {
            printf("#cisfun$ ");
            fflush(stdout);
        }

        /* Read a line from stdin */
        nread = getline(&line, &len, stdin);
        if (nread == -1) /* Ctrl+D or EOF */
        {
            free(line);
            exit(0);
        }

        /* Remove trailing newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Skip empty lines */
        if (line[0] == '\0')
            continue;

        /* Prepare argv array for execve */
        argv[0] = line;
        argv[1] = NULL;

        /* Fork a child process */
        pid = fork();

        if (pid == 0)
        {
            /* Child process: execute command */
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("./hsh");
                exit(1);
            }
        }
        else
        {
            /* Parent process: wait for child */
            wait(&status);
        }
    }

    return (0);
}
