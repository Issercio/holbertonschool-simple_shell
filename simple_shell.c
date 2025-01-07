#include "simple_shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: The number of arguments passed to the shell (currently unused).
 * @argv: The arguments passed to the shell (currently unused).
 * @envp: The environment variables.
 *
 * Description: This function runs the shell. It repeatedly calls the function
 * handle_input() to read commands and execute them. It exits when the user
 * types `exit` or presses `Ctrl+D` (EOF).
 *
 * Return: 0 on successful exit of the shell.
 */

int main(int argc, char **argv, char **envp)
{
	char *command = NULL;
	size_t len = 0;
	int running = 1;

	/* Suppress unused parameter warnings for argc and argv */
	(void)argc;
	(void)argv;

	/* Continuously handle input until the user exits */
	while (running)
	{
		running = handle_input(&command, &len, envp); /* Process user input */
	}

	/* Free memory allocated for the command before exiting */
	free(command);

	return (0);
}
