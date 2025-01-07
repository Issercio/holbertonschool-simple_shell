#include "simple_shell.h"

/**
* execute_command - Executes the given command.
* @command: The command to execute.
*/
void execute_command(char *command)
{
	pid_t pid;
	int status;

	char *argv[2];  /* Declare the array with space for command and NULL */

	/* Dynamically set the first element of argv */
	argv[0] = command;
	argv[1] = NULL;  /* The second element is NULL to mark the end of arguments */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		/* Execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			perror("./hsh");
			exit(127); /* Exit child process on error */
		}
	}
	else
	{
		wait(&status); /* Parent waits for child process */
	}
}

/**
* handle_input - Handles user input and processes commands.
* @command: Pointer to the command buffer.
* @len: Pointer to the length of the command buffer.
*
* Return: 1 to continue, 0 to exit the shell.
*/
int handle_input(char **command, size_t *len)
{
	ssize_t read;

	printf("#cisfun$ ");
	read = getline(command, len, stdin);
	if (read == -1) /* Handle EOF (Ctrl+D) */
	{
		free(*command);
		printf("\n");
		return (0);
	}
	if ((*command)[read - 1] == '\n') /* Remove newline character */
	{
		(*command)[read - 1] = '\0';
	}
	if ((*command)[0] == '\0') /* Ignore empty input */
	{
		return (1);
	}
	if (access(*command, X_OK) == 0) /* Check if command is executable */
	{
		execute_command(*command);
	}
	else /* Print error for invalid commands */
	{
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
		running = handle_input(&command, &len);
	}
	free(command); /* Free memory before exiting */
	return (0);
}
