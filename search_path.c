#include "simple_shell.h"

/**
 * search_path - Searches for a command in the PATH environment variable.
 * @command: The command to search for.
 * @full_path: Buffer to store the full path.
 *
 * Return: Pointer to the full path if found, or NULL if not found.
 */
char *search_path(char *command, char *full_path)
{
	char *path, *dir;
	char buffer[1024];

	if (access(command, X_OK) == 0) /* Check if command is executable */
		return (command);

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path = _strdup(path); /* Duplicate PATH to tokenize */
	if (!path)
		return (NULL);

	dir = strtok(path, ":");

	while (dir)
	{
		_sprintf(buffer, "%s/%s", dir, command);
		if (access(buffer, X_OK) == 0) /* Check if executable exists */
		{
			_strcpy(full_path, buffer);
			free(path);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
