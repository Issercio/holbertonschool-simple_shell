#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* execute_command - Executes a command in a new process.
* @command: The command to execute.
*/
void execute_command(char *command)
{
	pid_t pid;
	int status;

	if (command == NULL || strlen(command) == 0)
	{
		return;
	}

	pid = fork();  /* Create a child process */
	if (pid == -1)
	{
		perror("Error forking");
		return;
	}

	if (pid == 0)  /* Child process */
	{
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL;  /* No arguments */

		if (execve(command, argv, NULL) == -1)  /* Execute the command */
		{
			handle_error(command);  /* Handle errors */
		}
		exit(EXIT_FAILURE);  /* Exit if execve fails */
	}
	else  /* Parent process */
	{
		do {
			waitpid(pid, &status, WUNTRACED);  /* Wait for the child process */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
* handle_error - Handles error when command is not found.
* @command: The command that failed.
*/
void handle_error(char *command)
{
	fprintf(stderr, "Command not found: %s\n", command);
}
