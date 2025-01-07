#include "simple_shell.h"

/**
 * execute_command - Executes the given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2]; /* Command array with space for the command and NULL */

	argv[0] = command; /* First element is the command itself */
	argv[1] = NULL;    /* Null-terminated array for execve */

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
			perror("./hsh");
			exit(127); /* Exit child process with error */
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for child to finish */
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

	/* Display the shell prompt */
	printf("#cisfun$ ");
	fflush(stdout);

	read = getline(command, len, stdin);
	if (read == -1) /* Handle EOF (Ctrl+D) */
	{
		free(*command);
		printf("\n");
		return (0);
	}

	/* Remove newline character */
	if ((*command)[read - 1] == '\n')
	{
		(*command)[read - 1] = '\0';
	}

	/* Ignore empty input */
	if ((*command)[0] == '\0')
	{
		return (1);
	}

	/* Check if the command is executable */
	if (access(*command, X_OK) == 0)
	{
		execute_command(*command);
	}
	else
	{
		/* Command not found error */
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
	char *command = NULL; /* Buffer to store the command */
	size_t len = 0;       /* Length of the buffer */
	int running = 1;      /* Flag to keep the shell running */

	while (running)
	{
		running = handle_input(&command, &len); /* Process user input */
	}

	free(command); /* Free the command buffer before exiting */
	return (0);
}
