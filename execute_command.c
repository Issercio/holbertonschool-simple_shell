#include "simple_shell.h"

/**
* execute_command - Exécute la commande utilisateur dans un processus enfant.
* @command: La commande à exécuter.
*/
void execute_command(char *command)
{
	pid_t pid;
	char *argv[2]; /* Tableau d'arguments pour execve */

	pid = fork(); /* Créer un processus enfant */

	if (pid == -1)
	{
		handle_error("Fork failed");
		return;
	}

	if (pid == 0) /* Dans le processus enfant */
	{
		/* Préparer argv pour execve */
		argv[0] = command; /* La commande complète (chemin absolu ou relatif) */
		argv[1] = NULL;    /* Aucun autre argument à passer */

		/* Exécuter la commande */
		if (execve(command, argv, environ) == -1)
		{
			fprintf(stderr, "Command not found or failed: %s\n", command);
			exit(127); /* Code de retour standard pour commande introuvable ou erreur */
		}
	}
	else /* Dans le processus parent */
	{
		wait(NULL); /* Attendre que le processus enfant se termine */
	}
}
