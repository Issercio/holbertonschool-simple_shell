#include "simple_shell.h"

/**
* execute_command - Executes a user command in a child process.
* @argv: Array of arguments for the command.
*/
void execute_command(char **argv)
{
	pid_t pid;
	char *executable;

	executable = find_executable(argv[0]);
	if (!executable) /* If executable not found */
	{
		fprintf(stderr, "%s: command not found\n", argv[0]);
		return;
	}

	pid = fork(); /* Create a child process */
	if (pid == -1) /* Check for fork failure */
	{
		perror("Fork failed");
		free(executable);
		return;
	}

	if (pid == 0) /* Child process */
	{
		if (execve(executable, argv, environ) == -1) /* Execute the command */
		{
			perror(argv[0]);
			free(executable);
			exit(127);
		}
	}
	else /* Parent process */
		wait(NULL); /* Wait for the child process to finish */

	free(executable); /* Free memory allocated for the executable */
}
