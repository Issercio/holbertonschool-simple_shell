#include "simple_shell.h"

/**
 * execute_command - Executes the given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

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
		/* Execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			perror(command); /* Print the specific command that failed */
			exit(127); /* Exit child process with error */
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for child process */
	}
}

/**
 * handle_input - Handles user input and processes commands.
 * @command: Pointer to the command buffer.
 * @len: Pointer to the length of the command buffer.
 *
 * Return: 1 to continue the shell, 0 to exit.
 */
int handle_input(char **command, size_t *len)
{
	ssize_t read;

	/* Display prompt if in interactive mode */
	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");
	fflush(stdout);

	read = getline(command, len, stdin);
	if (read == -1) /* Handle EOF (Ctrl+D) */
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (0); /* Indicate to exit the shell */
	}

	/* Remove newline character */
	if ((*command)[read - 1] == '\n')
		(*command)[read - 1] = '\0';

	/* Ignore empty input */
	if ((*command)[0] == '\0')
		return (1);

	/* Check if the command is executable */
	if (access(*command, X_OK) == 0)
	{
		execute_command(*command);
	}
	else
	{
		/* Print error if the command is not found or not executable */
		fprintf(stderr, "./hsh: %s: command not found\n", *command);
	}

	return (1);
}

/**
 * main - Entry point for the simple shell.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	int running = 1;

	while (running)
	{
		running = handle_input(&command, &len); /* Process user input */
	}

	free(command); /* Free memory before exiting */
	return (0);
}
