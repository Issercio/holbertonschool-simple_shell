#include "simple_shell.h"

/**
 * handle_input - Reads user input, processes commands, and executes them.
 * @command: A pointer to a string that will hold the user's input.
 * @len: A pointer to the size of the buffer for storing user input.
 * @envp: A pointer to the environment variables.
 *
 * Return: 0 if the shell should exit, 1 if the shell should continue running.
 */
int handle_input(char **command, size_t *len, char **envp)
{
    ssize_t read;

    /* Display prompt if in interactive mode */
    if (isatty(STDIN_FILENO))
    {
        printf("#cisfun$ ");
    }
    fflush(stdout);

    /* Read the user input */
    read = getline(command, len, stdin);
    if (read == -1)  /* Handle EOF (Ctrl+D) */
    {
        if (isatty(STDIN_FILENO))
        {
            printf("\n");
        }
        return (0); /* Exit the shell */
    }

    /* Remove newline character at the end of the command */
    if ((*command)[read - 1] == '\n')
    {
        (*command)[read - 1] = '\0';
    }

    /* If the input is empty, return 1 to continue */
    if ((*command)[0] == '\0')
    {
        return (1);
    }

    /* If the command is "exit", terminate the shell */
    if (strcmp(*command, "exit") == 0)
    {
        return (0); /* Exit the shell */
    }

    /* Execute the command */
    execute_command(*command, envp);

    return (1); /* Continue the shell */
}
