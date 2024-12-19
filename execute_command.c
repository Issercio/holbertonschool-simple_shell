#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
* execute_command - Exécute une commande donnée.
* @command: La commande à exécuter.
*
* Description: Cette fonction crée un
* processus fils pour exécuter la commande
* en utilisant execve. Avant d'exécuter la commande,
* elle enregistre la commande
* dans un fichier journal.
*/
void execute_command(char *command)
{
	pid_t pid;    /* Identifiant du processus pour le fork */
	int status;    /* Statut du processus fils */

	/* Si la commande est vide, retourner à l'invite */
	if (command == NULL || strlen(command) == 0)
	{
		return;
	}

	/* Enregistrer la commande dans le fichier journal */
	log_command(command);

	/* Fork pour créer un processus fils */
	pid = fork();
	if (pid == -1)
	{
		perror("Erreur");
		return;
	}

	if (pid == 0)
	{
		/* Processus fils */
		char *argv[2];  /* Tableau d'arguments pour execve */

		argv[0] = command;
		argv[1] = NULL; /* Tableau d'arguments null-terminé */

		/* Exécuter la commande */
		if (execve(command, argv, environ) == -1)
		{
			perror("Commande introuvable");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Processus parent, attend la fin du processus fils */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
