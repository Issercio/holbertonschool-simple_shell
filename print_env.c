#include "simple_shell.h"

/**
* print_env - Prints all environment variables.
*/
void print_env(void)
{
	char **env = environ;

	while (*env) /* Iterate through the environment variables */
	{
		write(STDOUT_FILENO, *env, _strlen(*env)); /* Print each variable */
		write(STDOUT_FILENO, "\n", 1); /* Print a newline */
		env++;
	}
}
