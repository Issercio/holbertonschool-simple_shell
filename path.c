#include "simple_shell.h"
#include <sys/stat.h>

/**
* search_path - Searches for a command in the directories listed in PATH.
* @command: The command to search for.
* @full_path: A buffer to store the full path if the command is found.
*
* Return: The full path of the executable if found, or NULL if not found.
*/
char *search_path(char *command, char *full_path)
{
	/* Retrieve the PATH environment variable */
	char *path_env = getenv("PATH");

	/* Use strtok to iterate through directories in PATH */
	char *dir = strtok(path_env, ":");

	/* Buffer to store the constructed path */
	char buffer[1024];

	/* Loop through each directory in the PATH variable */
	while (dir)
	{
		/* Construct the full path for the command: "<dir>/<command>" */
		_sprintf(buffer, "%s/%s", dir, command);

		/* Check if the constructed path is executable */
		if (access(buffer, X_OK) == 0)
		{
			/* If executable, copy the path to the full_path buffer */
			_strcpy(full_path, buffer);
			return (full_path); /* Return the full path */
		}

		/* Move to the next directory in PATH */
		dir = strtok(NULL, ":");
	}

	/* If the command is not found, return NULL */
	return (NULL);
}
