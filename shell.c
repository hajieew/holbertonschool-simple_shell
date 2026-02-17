#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * find_command - finds full path of a command using PATH
 * @command: command name
 *
 * Return: full path if found, otherwise NULL
 */
char *find_command(char *command)
{
    char *path_env, *path_copy, *dir;
    static char full_path[1024];

    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return command;
        return NULL;
    }

    int i = 0;

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
        i++;
    }

if (path_env == NULL)
    return NULL;


    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return NULL;

    dir = strtok(path_copy, ":");

    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * main - simple UNIX shell
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
    char *argv[100];
    char *token;
    int i;
    char *cmd_path;

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("newshell$ ");
            fflush(stdout);
        }

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        i = 0;
        token = strtok(line, " \t");

        while (token != NULL && i < 99)
        {
            argv[i++] = token;
            token = strtok(NULL, " \t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL)
            continue;

        if (strcmp(argv[0], "exit") == 0)
        {
            free(line);
            exit(0);
        }

        cmd_path = find_command(argv[0]);

        if (cmd_path == NULL)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            continue;
        }

        pid = fork();

        if (pid == 0)
        {
            if (execve(cmd_path, argv, environ) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
