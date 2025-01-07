#include "simple_shell.h"

/**
* execute_command - Exécute la commande utilisateur dans un processus enfant.
* @command: La commande à exécuter.
*/
void execute_command(char *command)
{
	pid_t pid;
	char *argv[64];  /* Tableau d'arguments pour execve */

	char *token;

	int i = 0;

	/* Tokenize the command string to separate arguments */
	token = strtok(command, " ");
	while (token != NULL && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;  /* Null-terminate the argument list */

	pid = fork(); /* Créer un processus enfant */

	if (pid == -1)
	{
		handle_error("Fork failed");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			fprintf(stderr, "Command not found or failed: %s\n", argv[0]);
			exit(127); /* Code de retour standard pour commande introuvable ou erreur */
		}
	}
	else
	{
		wait(NULL); /* Attendre que le processus enfant se termine */
	}
}
