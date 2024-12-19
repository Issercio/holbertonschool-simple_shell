#include "simple_shell.h"

/**
 * main - Entry point of the shell program.
 *
 * Description: Displays a prompt, reads user input, and executes
 * commands in a loop until EOF or termination. Supports both
 * interactive and non-interactive modes.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *line = NULL; /* Input line */
	size_t len = 0;    /* Length of the line */
	ssize_t nread;     /* Number of characters read */

	/* Loop indefinitely to read and execute commands */
	while (1)
	{
		/* Display prompt in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
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
