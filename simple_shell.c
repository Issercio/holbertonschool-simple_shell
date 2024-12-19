#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* main - Entry point of the shell program.
*
* Description: Displays a prompt, reads user input, and executes
* commands in a loop until EOF (Ctrl+D) or termination.
*
* Return: Always returns 0.
*/
int main(void)
{
	char *line = NULL;  /* Input line */

	size_t len = 0;     /* Length of the line */
	ssize_t nread;      /* Number of characters read */

	while (1)
	{
		/* Display prompt */
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		/* Read input from the user */
		nread = getline(&line, &len, stdin);
		if (nread == -1)  /* Handle EOF (Ctrl+D) */
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		/* Remove the newline character */
		line[strcspn(line, "\n")] = '\0';

		/* Execute the command */
		execute_command(line);
	}

	free(line);
	return (0);
}
