#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* execute_command - Executes a command in a child process.
* @command: The command to execute.
*
* Description: This function creates a child process using `fork()`. If the
* command is valid, it attempts to execute it using `execve()`. If execution
* fails (e.g., command not found), it prints an error message.
* The function waits for the child process to complete in the parent process.
*/
void execute_command(char *command)
{
	pid_t pid;
	int status;

	if (command == NULL || strlen(command) == 0)
	{
		return; /* Ignore empty commands */
	}

	pid = fork();  /* Create a new child process */
	if (pid == -1)
	{
		perror("Error");
		return;  /* Return if there is an error in forking */
	}

	if (pid == 0)  /* Child process */
	{
		/* Prepare argv for execve */
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL; /* Null-terminate the argument list */

		/* Try to execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			perror("Command not found");
			exit(EXIT_FAILURE);  /* Exit if command cannot be executed */
		}
	}
	else  /* Parent process */
	{
		waitpid(pid, &status, WUNTRACED);  /* Wait for the child process to finish */
	}
}

/**
* main - Entry point of the simple shell.
*
* Description: This function displays a prompt, waits for user input,
* and executes commands. It loops indefinitely until the user exits or
* provides EOF (Ctrl+D).
*
* Return: Always returns 0.
*/
int main(void)
{
	char *line = NULL; /* Input line */

	size_t len = 0;    /* Length of the line */
	ssize_t nread;     /* Number of characters read */

	/* Main loop to handle commands */
	while (1)
	{
		/* Display prompt in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		/* Read input from the user */
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			/* Handle EOF (Ctrl+D) */
			if (isatty(STDIN_FILENO))
				printf("\n");
			break; /* Exit the loop */
		}

		/* Remove the newline character from the input */
		line[strcspn(line, "\n")] = '\0';

		/* Execute the command entered by the user */
		execute_command(line);
	}

	/* Free the allocated memory for the input line */
	free(line);
	return (0);
}
