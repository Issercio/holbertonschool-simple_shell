#include "simple_shell.h"

/**
 * execute_ls - Exécute la commande 'ls'
 */
void execute_ls(void)
{
	pid_t pid;
	int status;
	char *argv[] = {"/bin/ls", NULL};

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	wait(&status);
}

/**
 * execute_command - Exécute une commande utilisateur
 * @command: La commande entrée par l'utilisateur
 */
void execute_command(char *command)
{
	if (strcmp(command, "ls") == 0 || strcmp(command, "/bin/ls") == 0)
	{
		execute_ls();
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", command);
	}
}

/**
 * main - Fonction principale du shell
 *
 * Return: 0 en cas de succès, ou une erreur
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
			return (0);
		}
		command[read - 1] = '\0';

		if (access(command, X_OK) == 0 || strcmp(command, "ls") == 0)
		{
			execute_command(command);
		}
		else
		{
			fprintf(stderr, "./shell: %s: No such file or directory\n", command);
		}

		free(command);
		command = NULL;
	}
	return (0);
}
