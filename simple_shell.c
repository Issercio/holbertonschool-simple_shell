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
		return;
	}

	pid = fork();  /* Create a new child process */
	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)  /* Child process */
	{
		/* Dynamically allocate space for argv and set it */
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL;

		/* Try to execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			perror("Command not found");
		}
		exit(EXIT_FAILURE);  /* Exit child process if execve fails */
	}
	else  /* Parent process */
	{
		waitpid(pid, &status, WUNTRACED);  /* Wait for the child process to finish */
	}
}

/**
* main - Entry point of the simple shell program.
*
* Description: This function continuously displays the prompt,
* waits for user input,
* and calls `execute_command` to execute the entered command. The shell handles
* EOF (Ctrl+D) and gracefully exits when EOF is encountered.
*
* Return: Always returns 0 (success).
*/
int main(void)
{
	char *line = NULL;  /* Input line */

	size_t len = 0;     /* Length of the line */
	ssize_t nread;      /* Number of characters read */

	/* Continuously show prompt and execute commands */
	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);  /* Flush output buffer to ensure prompt is displayed */

		nread = getline(&line, &len, stdin);  /* Read input line */
		if (nread == -1)  /* Handle EOF (Ctrl+D) */
		{
			printf("\n");
			break;  /* Exit the loop on EOF */
		}

		/* Remove the newline character from the input */
		line[strcspn(line, "\n")] = '\0';

		/* Execute the command entered by the user */
		execute_command(line);
	}

	free(line);  /* Free the memory allocated for the input line */
	return (0);
}
