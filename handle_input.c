#include "simple_shell.h"

/**
 * handle_input - Reads user input and processes the command.
 * @command: A pointer to a buffer for storing the user's command.
 * @len: A pointer to the size of the buffer.
 *
 * Return: 0 to exit the shell, 1 to continue.
 */
int handle_input(char **command, size_t *len)
{
    ssize_t read;
    char *argv[64];
    char *token;
    int i;

    /* Display prompt if interactive */
    if (isatty(STDIN_FILENO))
        printf("#cisfun$");
    fflush(stdout);

    /* Read user input */
    read = getline(command, len, stdin);
    if (read == -1)
    {
        if (isatty(STDIN_FILENO))
            printf("\n");
        return (0); /* Exit on EOF (Ctrl+D) */
    }

    /* Remove newline character from input */
    if ((*command)[read - 1] == '\n')
        (*command)[read - 1] = '\0';

    /* Split input into arguments */
    i = 0;
    token = strtok(*command, " ");
    while (token && i < 63)
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    /* Check for "exit" command */
    if (argv[0] && strcmp(argv[0], "exit") == 0)
        return (0);

    /* Execute the command */
    if (argv[0])
        execute_command(argv);

    return (1); /* Continue shell */
}
