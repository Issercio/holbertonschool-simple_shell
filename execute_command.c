#include "simple_shell.h"

/**
* execute_command - Exécute la commande utilisateur dans un processus enfant.
* @command: La commande à exécuter.
* @envp: Les variables d'environnement pour le nouveau processus.
*/
void execute_command(char *command, char **envp)
{
	pid_t pid;
	char *full_command = NULL;

	char *argv[2];  /* Tableau d'arguments pour execve */

	pid = fork();  /* Créer un processus enfant */

	if (pid == -1)
	{
		handle_error("Fork failed");
		return;
	}

	if (pid == 0)  /* Dans le processus enfant */
	{
		/* Chercher la commande dans le PATH */
		full_command = find_in_path(command);
		if (full_command == NULL)
		{
			fprintf(stderr, "Command not found: %s\n", command);
			exit(127); /* Code de retour standard pour commande introuvable */
		}

		/* Préparer argv pour execve */
		argv[0] = full_command;  /* La commande complète */
		argv[1] = NULL;  /* Aucun autre argument à passer */

		/* Exécuter la commande */
		if (execve(full_command, argv, envp) == -1)
		{
			handle_error("Execution failed");
			free(full_command);
			exit(1);
		}
	}
	else  /* Dans le processus parent */
	{
		wait(NULL);  /* Attendre que le processus enfant se termine */
	}
}
