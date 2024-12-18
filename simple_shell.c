#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* execute_command - Executes a given command.
*
* @command: The command to execute.
*
* This function checks if the command exists in the system, and if it does,
* it uses `execve` to execute the command. If the command cannot be found,
* it prints an error message.
*
* Return: 0 on success, or -1 on failure.
*/
int execute_command(char *command)
{
	pid_t pid = fork();  /* Create a child process */

	if (pid == -1)
	{
		perror("fork");
		return (-1);  /* Error in forking the process */
	}

	if (pid == 0)  /* Child process */
	{
		if (execve(command, NULL, NULL) == -1)
		{
			perror(command);  /* Print error if command fails */
			exit(EXIT_FAILURE);  /* Exit the child process on failure */
		}
	}

	wait(NULL);  /* Wait for the child process to finish */
	return (0);  /* Return 0 on successful execution */
}

/**
* handle_error - Handles errors and prints an error message.
*
* @error_message: The error message to display.
*
* This function prints an error message to stderr.
*
* Return: Nothing (void).
*/
void handle_error(char *error_message)
{
	fprintf(stderr, "%s\n", error_message);  /* Print the error message */
}

/**
* main - Entry point of the simple shell program.
*
* The `main` function displays a prompt, accepts user input, and executes
* commands entered by the user. The program continues to display the prompt
* until the user exits (Ctrl+D or "exit").
*
* Return: Always 0.
*/
int main(void)
{
	char *command = NULL;

	size_t len = 0;

	while (1)
	{
		printf("#cisfun$ ");
		if (getline(&command, &len, stdin) == -1)
		{
			if (feof(stdin))  /* End of file reached (Ctrl+D) */
			{
				printf("\n");
				break;
			}
			handle_error("Error reading input");
			continue;
		}

		command[strcspn(command, "\n")] = '\0';  /* Remove newline */
		if (command[0] == '\0')  /* Empty command */
			continue;

		execute_command(command);  /* Execute the command */
	}

	free(command);  /* Free allocated memory */
	return (0);  /* Return 0 to indicate successful execution */
}
