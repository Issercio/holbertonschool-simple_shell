#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
* execute_exit - Gère la commande exit.
*/
void execute_exit(void)
{
	exit(0);
}

/**
* execute_ls - Exécute la commande ls en utilisant execve.
*/
void execute_ls(void)
{
	char *argv[2]; /* Déclaration du tableau avant utilisation */

	argv[0] = "/bin/ls";
	argv[1] = NULL;

	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("execve");
	}
	exit(EXIT_FAILURE);
}

/**
* execute_command - Gère les commandes saisies par l'utilisateur.
* @command: La commande saisie.
*/
void execute_command(char *command)
{
	pid_t pid;  /* Déclaration de la variable au début */

	/* Vérifie la commande 'exit' */
	if (strcmp(command, "exit") == 0)
	{
		execute_exit();
	}

	/* Vérifie la commande 'ls' ou '/bin/ls' */
	if (strcmp(command, "ls") == 0 || strncmp(command, "/bin/ls", 7) == 0)
	{
		execute_ls();
	}

	/* Exécution de la commande générale */
	pid = fork(); /* Déclaration de pid avant l'exécution du code */
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		char *argv[2]; /* Déclaration avant l'utilisation */

		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, NULL) == -1)
		{
			perror("execve");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL); /* Le parent attend que le processus fils se termine */
	}
}

/**
* main - Boucle principale pour gérer l'entrée utilisateur.
*
* Return: Toujours 0.
*/
int main(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}

		line[strcspn(line, "\n")] = 0; /* Supprime le caractère de nouvelle ligne */
		execute_command(line);
	}

	free(line);
	return (0);
}
