#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - simple shell
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
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        /* remove newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        argv[0] = line;
        argv[1] = NULL;

        pid = fork();

        if (pid == 0)
        {
            if (execve(line, argv, environ) == -1)
            {
                perror("./hsh");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }

    return (0);
}
