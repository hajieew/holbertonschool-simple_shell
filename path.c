#include "shell.h"

/**
 * find_command - search command in PATH
 * @command: command name
 *
 * Return: full path if found, otherwise NULL
 */
char *find_command(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	static char full_path[1024];
	int i;

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}

	path_env = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
		i++;
	}

	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
