#include "simple_shell.h"

/**
 * handle_command - Processes and executes a user command.
 * @command: The user input command.
 *
 * Return: 1 to continue, 0 to exit the shell.
 */
int handle_command(char *command)
{
	char *argv[64], *path = NULL, full_path[1024];
	int i = 0;
	pid_t pid;

	command[strcspn(command, "\n")] = '\0'; /* Remove trailing newline */

	if (_strcmp(command, "exit") == 0) /* Handle built-in exit */
		return (0);

	if (_strcmp(command, "env") == 0) /* Handle built-in env */
	{
		print_env();
		return (1);
	}

	argv[i] = strtok(command, " ");
	while (argv[i] != NULL && i < 63)
		argv[++i] = strtok(NULL, " ");
	argv[i] = NULL;

	if (!argv[0]) /* Ignore empty commands */
		return (1);

	path = search_path(argv[0], full_path);
	if (!path)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		return (1);
	}

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (pid == 0) /* Child process */
	{
		if (execve(path, argv, environ) == -1)
		{
			perror(argv[0]);
			exit(127);
		}
	}
	else /* Parent process */
		wait(NULL);

	return (1);
}
