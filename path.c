#include "simple_shell.h"
#include <sys/stat.h>

/**
* search_path - Searches for a command in the directories listed in PATH.
* @command: The command to search for.
* @full_path: A buffer to store the full path if found.
*
* Return: The full path of the executable or NULL if not found.
*/
char *search_path(char *command, char *full_path)
{
	char *path_env = getenv("PATH");

	char *dir = strtok(path_env, ":");

	char buffer[1024];

	while (dir)
	{
		_sprintf(buffer, "%s/%s", dir, command);
		if (access(buffer, X_OK) == 0)
		{
			_strcpy(full_path, buffer);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	return (NULL);
}
