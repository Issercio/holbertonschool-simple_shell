#include "simple_shell.h"

/**
* execute_command - Forks a child process to execute a command.
* @command: The command to be executed.
* @envp: The environment variables passed to execve.
*
* Return: None. The function executes the command or reports an error.
*/
void execute_command(char *command, char **envp)
{
	pid_t pid;
	int status;

	char *argv[2];

	/* Set up argument vector for execve */
	argv[0] = command;
	argv[1] = NULL;

	/* Create a new child process using fork */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)  /* Child process */
	{
		/* Execute the command */
		if (execve(command, argv, envp) == -1)
		{
			perror(command);  /* If execve fails */
			exit(127);  /* Exit child process with error code */
		}
	}
	else  /* Parent process */
	{
		wait(&status);  /* Wait for the child process to terminate */
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			printf("Error: Child process failed with status %d\n", WEXITSTATUS(status));
		}
	}
}
