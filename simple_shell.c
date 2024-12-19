#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* execute_exit - Gère la commande 'exit'
* @command: La commande entrée par l'utilisateur
*
* Retour: 1 pour exit ou 0 pour continuer l'exécution
*/
int execute_exit(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		free(command);
		exit(0);
	}
	return (0);
}

/**
* execute_ls - Exécute la commande 'ls' ou '/bin/ls'
* @command: La commande entrée par l'utilisateur
*
* Retour: 1 si 'ls' ou '/bin/ls' est exécuté, 0 sinon
*/
int execute_ls(char *command)
{
	pid_t pid;
	int status;

	char *argv[] = {"/bin/ls", NULL};

	if (strcmp(command, "ls") == 0 || strcmp(command, "/bin/ls") == 0)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			execve("/bin/ls", argv, NULL);
			perror("execve");
			exit(1);
		}
		wait(&status);
		return (1);
	}
	return (0);
}

/**
* execute_command - Exécute une commande
* @command: La commande entrée par l'utilisateur
*
* Retour: 0 si la commande a été exécutée correctement, -1 sinon
*/
int execute_command(char *command)
{
	if (execute_exit(command))
		return (0);

	if (execute_ls(command))
		return (0);

	fprintf(stderr, "%s: command not found\n", command);
	return (-1);
}

/**
* main - Fonction principale du shell
*
* Retour: 0
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

		if (read == -1)
		{
			free(command);
			printf("\n");
			exit(0);
		}

		command[read - 1] = '\0';

		if (execute_command(command) == -1)
			perror("Execution error");

		free(command);
		command = NULL;
	}

	return (0);
}
