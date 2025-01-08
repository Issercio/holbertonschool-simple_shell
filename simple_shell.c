#include "simple_shell.h"

/**
 * main - Entry point for the simple shell.
 * @argc: Number of arguments passed (not used here).
 * @argv: Array of arguments passed (not used here).
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char *command = NULL;
	size_t len = 0;
	int status = 1;

	(void)argc;
	(void)argv;

	while (status)
	{
		if (isatty(STDIN_FILENO)) /* Interactive mode check */
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		if (getline(&command, &len, stdin) == -1) /* Handle EOF */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (command[0] != '\n') /* Ignore empty input */
			status = handle_command(command);
	}

	free(command); /* Free memory allocated for command */
	return (0);
}
