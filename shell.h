#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

char *find_command(char *command);
void builtin_env(void);
int parse_line(char *line, char **argv);
int exec_command(char **argv, char *cmd_path);

#endif 