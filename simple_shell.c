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

    (void)argc; /* Avoid unused parameter warning */
    (void)argv;

    while (status) /* Run the shell loop until the user exits */
    {
        if (isatty(STDIN_FILENO)) /* Check if in interactive mode */
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        if (getline(&command, &len, stdin) == -1) /* Handle EOF (Ctrl+D) */
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (command[0] != '\n') /* Ignore empty input */
        {
            char *argv[64];
            int i = 0;

            /* Tokenize the input command into arguments */
            argv[i] = strtok(command, " \n");
            while (argv[i] && i < 63)
                argv[++i] = strtok(NULL, " \n");
            argv[i] = NULL;

            if (argv[0]) /* If the command is not empty */
            {
                if (strcmp(argv[0], "exit") == 0) /* Handle built-in exit command */
                    break;
                else if (strcmp(argv[0], "env") == 0) /* Handle built-in env command */
                {
                    print_env();
                }
                else /* Execute the user command */
                    execute_command(argv);
            }
        }
    }

    free(command); /* Free memory allocated for command input */
    return (0); /* Return 0 to indicate successful execution */
}
