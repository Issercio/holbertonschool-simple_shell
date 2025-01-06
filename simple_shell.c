#include "simple_shell.h"

/**
 * execute_command - Executes a user command.
 * @command: The command entered by the user.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2]; /* Array for the command and NULL */

	/* Initialize the array dynamically */
	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0) /* Child process */
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror("./shell");
			exit(127); /* Exit with error code 127 */
		}
	}
	else /* Parent process */
	{
		wait(&status);
	}
}

/**
 * main - Main shell function.
 *
 * Return: Always 0
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		/* Display the prompt */
		printf("#cisfun$ ");
		read = getline(&command, &len, stdin);

		/* Handle Ctrl+D (EOF) */
		if (read == -1)
		{
			free(command);
			printf("\n");
			break;
		}

		/* Remove the trailing newline character */
		command[read - 1] = '\0';

		/* Check if command is empty */
		if (strlen(command) == 0)
			continue;

		/* Execute the command if accessible */
		if (access(command, X_OK) == 0)
		{
			execute_command(command);
		}
		else
		{
			fprintf(stderr, "./shell: %s: command not found\n", command);
		}

		/* Free command for the next iteration */
		free(command);
		command = NULL;
	}

	return (0);
}
