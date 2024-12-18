#include "simple_shell.h"

/**
* execute_command - Exécute la commande entrée par l'utilisateur.
* @command: La commande à exécuter.
*
* Retourne 0 si la commande est exécutée avec succès, sinon -1.
*/
int execute_command(char *command)
{
	char *args[] = {command, NULL};  /* Initialisation des arguments */

	pid_t pid;
	int status;

	if (command == NULL)
	{
		return (-1);
	}

	pid = fork();  /* Créer un processus fils */

	if (pid == -1)  /* Vérifier l'échec du fork */
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)  /* Si c'est le processus fils */
	{
		if (execvp(command, args) == -1)  /* Exécuter la commande */
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else  /* Si c'est le processus parent */
	{
		wait(&status);  /* Attendre que le processus fils se termine */
	}

	return (0);
}

/**
* parse_command - Analyse la commande et vérifie sa validité.
* @input: Entrée de l'utilisateur.
*
* Retourne 1 si la commande est valide, sinon 0.
*/
int parse_command(char *input)
{
	if (input == NULL || *input == '\0')
	{
		return (0);  /* Commande vide */
	}

	if (strchr(input, ';') != NULL)
	{
		write(STDOUT_FILENO, "Semicolon is not allowed in the command.\n", 41);
		return (0);  /* Interdiction des points-virgules */
	}

	return (1);  /* Commande valide */
}
