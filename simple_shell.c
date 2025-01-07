#include "simple_shell.h"

/**
 * execute_command - Executes the given command.
 * @command: The command to execute.
 * @envp: The environment variables.
 */
void execute_command(char *command, char **envp)
{
	pid_t pid;
	int status;
	char *argv[2]; /* Command and NULL */

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
		if (execve(command, argv, envp) == -1)
		{
			perror(command); /* Print error for the specific command */
			exit(127); /* Exit child process with error */
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for child process to terminate */
	}
}

/**
 * handle_input - Handles user input and processes commands.
 * @command: Pointer to the command buffer.
 * @len: Pointer to the length of the command buffer.
 * @envp: The environment variables.
 *
 * Return: 1 to continue the shell, 0 to exit.
 */
int handle_input(char **command, size_t *len, char **envp)
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
		execute_command(*command, envp);
	}
	else
	{
		/* Print error if the command is not found or not executable */
		fprintf(stderr, "./hsh: %s: not found\n", *command);
	}

	return (1);
}

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count.
 * @argv: Argument vector (unused in this case).
 * @envp: Environment pointer.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv, char **envp)
{
	char *command = NULL;
	size_t len = 0;
	int running = 1;

	(void)argc; /* Unused */
	(void)argv; /* Unused */

	while (running)
	{
		running = handle_input(&command, &len, envp); /* Process user input */
	}

	free(command); /* Free memory before exiting */
	return (0);
}
