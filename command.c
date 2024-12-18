#include "simple_shell.h"

/**
 * execute_command - Executes the parsed command by creating a child process.
 *
 * @command: The command string to be executed.
 *
 * This function attempts to execute the provided command using `execve`. It
 * creates a new process using `fork`. The child process calls `execve` to
 * execute the command, and if execution fails,
 * it will display an error message.
 *
 * Return: 0 on success, or -1
 * if an error occurs during execution (e.g., command not found).
 */
int execute_command(char *command)
{
	pid_t pid = fork();  /* Create a child process */

	if (pid == -1)  /* Error creating process */
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)  /* In the child process */
	{
		if (execve(command, NULL, NULL) == -1)  /* Execute the command */
		{
			perror(command);  /* If execution fails, print error */
			exit(EXIT_FAILURE);  /* Exit child process on error */
		}
	}

	wait(NULL);  /* Parent waits for the child process to finish */
	return (0);  /* Command executed successfully */
}

/**
 * parse_command - Parses the user input to determine the command to execute.
 *
 * @input: The raw input string entered by the user.
 *
 * This function processes the raw input string to determine the appropriate
 * command. It may involve trimming whitespace, tokenizing the string,
 * or other operations needed to prepare the command for execution.
 *
 * Return: A string representing the parsed command, or NULL if parsing fails.
 */
char *parse_command(char *input)
{
	char *command = NULL;

	if (input == NULL)  /* Check for NULL input */
	{
		fprintf(stderr, "Error: No command entered\n");
		return (NULL);
	}

	command = strtok(input, " \t\n");  /* Tokenize the input to get the command */

	if (command == NULL)  /* Check if the input is empty or invalid */
	{
		fprintf(stderr, "Error: Invalid command\n");
		return (NULL);
	}

	return (command);  /* Return the parsed command */
}
