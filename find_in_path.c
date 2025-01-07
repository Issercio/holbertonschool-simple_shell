#include "simple_shell.h"

/**
* find_in_path - Cherche une commande dans le PATH.
* @command: La commande à chercher.
*
* Return: Le chemin complet vers la commande, ou NULL si introuvable.
*/
char *find_in_path(const char *command)
{
	char *path = getenv("PATH");

	char *path_copy = strdup(path); /* Faites une copie pour strtok */

	char *dir = strtok(path_copy, ":");

	char *full_path = NULL;

	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc failed");
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path); /* Commande trouvée */
		}

		free(full_path);
		full_path = NULL;
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Commande non trouvée */
}
