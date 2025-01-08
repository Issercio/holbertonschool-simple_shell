#include "simple_shell.h"
#include <sys/stat.h>

/**
* find_executable - Searches for an executable in the PATH.
* @command: The command to search for.
*
* Return: Full path to the executable if found, otherwise NULL.
*/
char *find_executable(char *command)
{
	char *path_env, *path, *token, *full_path;

	struct stat st;

	if (!command || access(command, X_OK) == 0)
		return (_strdup(command));

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path = _strdup(path_env);
	if (!path)
		return (NULL);

	token = strtok(path, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
