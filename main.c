#include "simple_shell.h"

/**
* read_command - Reads a command from user input.
*
* @command: A pointer to a string where the command will be stored.
*
* This function prompts the user for a command and reads it using the
* `getline` function. It handles the case when the user inputs EOF (Ctrl+D).
*
* Return: The number of characters read, or -1 if there is an error.
*/
ssize_t read_command(char **command)
{
	size_t len = 0;
	ssize_t nread;

	nread = getline(command, &len, stdin);
	if (nread == -1)  /* Check for end-of-file (Ctrl+D) or error */
	{
		if (feof(stdin))  /* End of file */
		{
			printf("\n");
			exit(0);  /* Exit the shell if EOF is detected */
		}
		else
		{
			perror("getline");
			return (-1);  /* Error reading input */
		}
	}

	return (nread);  /* Return number of bytes read */
}

/**
* process_command - Processes and executes the user input command.
*
* @command: The command entered by the user.
*
* This function handles the logic of executing the command entered by the
* user. If the command is found, it is executed; otherwise, an error message
* is displayed.
*
* Return: 0 on success, or -1 if an error occurs during execution.
*/
int process_command(char *command)
{
	pid_t pid = fork();  /* Create a child process */

	if (pid == -1)
	{
		perror("fork");
		return (-1);  /* Error forking the process */
	}

	if (pid == 0)  /* Child process */
	{
		if (execve(command, NULL, NULL) == -1)  /* Attempt to execute command */
		{
			perror(command);  /* Print error if command fails */
			exit(EXIT_FAILURE);  /* Exit child process on failure */
		}
	}
	wait(NULL);  /* Parent process waits for child to finish */
	return (0);  /* Command executed successfully */
}

/**
* main - The entry point of the shell program.
*
* The `main` function continuously displays a prompt, reads the user's input,
* and processes the command.
* The program loops until the user exits (Ctrl+D or "exit").
*
* Return: Always 0.
*/
int main(void)
{
	char *command = NULL;

	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = read_command(&command);  /* Read user command */
		if (nread == -1)  /* Check if error occurred */
			continue;

		command[strcspn(command, "\n")] = '\0';  /* Remove newline from command */
		if (command[0] == '\0')  /* Ignore empty commands */
			continue;

		process_command(command);  /* Process and execute the command */
	}

	free(command);  /* Free memory allocated for command */
	return (0);  /* Exit the program */
}
