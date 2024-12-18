#include "simple_shell.h"

/**
* parse_args - Splits a command into arguments.
*
* @line: The input string (command).
* @args: A pointer to an array of strings that will hold the arguments.
*
* This function takes a command line input, splits it into individual
* arguments, and stores them in an array. It returns the number of arguments
* parsed.
*
* Return: The number of arguments parsed.
*/
int parse_args(char *line, char **args)
{
	int i = 0;

	/* Split the command line into arguments */
	args[i] = strtok(line, " ");
	while (args[i] != NULL)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}

	return (i);  /* Return the number of arguments parsed */
}

/**
* command_exists - Checks if a command exists in the system.
*
* @command: The name of the command to search for.
*
* This function checks if a command exists in the directories listed in
* the PATH environment variable. It attempts to find the command in each
* directory, using the access system call to verify its existence.
*
* Return: 1 if the command exists, 0 otherwise.
*/
int command_exists(char *command)
{
	char *path = getenv("PATH");  /* Get the PATH environment variable */

	char *dir = strtok(path, ":"); /* Split the PATH into directories */

	while (dir != NULL)
	{
		char full_path[1024];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

		if (access(full_path, F_OK) == 0)
		{
			return (1);  /* Command found in the system */
		}

		dir = strtok(NULL, ":");  /* Check the next directory */
	}

	return (0);  /* Command does not exist in any directory */
}

/**
* print_env - Prints the environment variables.
*
* This function loops through the environment variables and prints them
* to the standard output in the format "key=value".
*
* Return: Nothing.
*/
void print_env(void)
{

int i = 0;

	/* Print each environment variable */
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
