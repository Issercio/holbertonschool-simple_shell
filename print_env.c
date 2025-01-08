#include "simple_shell.h"

/**
 * print_env - Prints the current environment variables.
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
