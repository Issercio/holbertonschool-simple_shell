#include "simple_shell.h"

/**
* display_prompt - Affiche l'invite de commande.
*/
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
}

/**
* execute_command - Exécute la commande entrée.
* @command: La commande à exécuter.
*
* Retourne 0 si la commande a été exécutée correctement, sinon -1.
*/
int execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();  /* Créer un processus fils */

	if (pid == -1)  /* Vérifier l'échec du fork */
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)  /* Si c'est le processus fils */
	{
		if (execvp(command, &command) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else  /* Si c'est le processus parent */
	{
		wait(&status);  /* Attendre que le processus fils termine */
	}

	return (0);
}

/**
* handle_error - Gère les erreurs en cas d'échec.
*/
void handle_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

/**
* main - Fonction principale du shell.
* @argc: Nombre d'arguments.
* @argv: Tableau des arguments.
*
* Retourne 0 en cas de succès.
*/
int main(int argc, char **argv)
{
	char *command = NULL;

	size_t len = 0;

	display_prompt();  /* Afficher l'invite de commande */

	while (getline(&command, &len, stdin) != -1)
	{
		if (command[0] != '\n')
		{
			if (execute_command(command) == -1)
			{
				handle_error();  /* Si l'exécution échoue */
			}
		}
		display_prompt();  /* Afficher l'invite après chaque commande */
	}

	free(command);  /* Libérer la mémoire */
	return (0);
}
