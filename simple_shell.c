#include "simple_shell.h"

/**
 * execute_command - Exécute une commande utilisateur
 * @command: La commande entrée par l'utilisateur
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2]; /* Tableau pour la commande et NULL */

	/* Initialisation du tableau dynamiquement */
	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0) /* Processus enfant */
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror("./shell");
			exit(127);
		}
	}
	else /* Processus parent */
	{
		wait(&status);
	}
}

/**
 * main - Fonction principale du shell
 *
 * Return: Toujours 0
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&command, &len, stdin);
		if (read == -1) /* Gestion de Ctrl+D (EOF) */
		{
			free(command);
			printf("\n");
			break;
		}

		/* Retirer le saut de ligne de la commande */
		command[read - 1] = '\0';

		/* Vérification si la commande est vide */
		if (strlen(command) == 0)
			continue;

		/* Exécuter la commande */
		if (access(command, X_OK) == 0)
		{
			execute_command(command);
		}
		else
		{
			fprintf(stderr, "./shell: %s: command not found\n", command);
		}

		free(command);
		command = NULL;
	}

	return (0);
}
