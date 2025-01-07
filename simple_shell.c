#include "simple_shell.h"

/**
 * execute_command - Executes the given command using execve().
 * @command: The command to execute.
 * @envp: The environment variables.
 *
 * Description: This function creates a child process using fork(). In the child
 * process, it executes the command using execve(). If execve() fails, an error
 * message is printed, and the child process exits with status 127. The parent process
 * waits for the child process to terminate.
 *
 * Return: None.
 */
void execute_command(char *command, char **envp)
{
    pid_t pid;
    int status;
    char *argv[2];

    argv[0] = command;
    argv[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0) /* Child process */
    {
        printf("Child process: executing command '%s'\n", command);
        if (execve(command, argv, envp) == -1)
        {
            perror(command);
            exit(127);
        }
    }
    else /* Parent process */
    {
        wait(&status); /* Wait for the child process to terminate */
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf("Error: Child process failed with status %d\n", WEXITSTATUS(status));
        }
    }
}

/**
 * handle_input - Handles user input, executes commands, and returns whether to continue.
 * @command: Pointer to the command buffer.
 * @len: Pointer to the length of the command buffer.
 * @envp: The environment variables.
 *
 * Description: This function displays a prompt if running interactively, reads
 * user input, checks if the command is valid, and executes it. If the input is
 * empty, it does nothing. It returns 1 to continue the shell or 0 to exit.
 *
 * Return: 1 to continue the shell, 0 to exit.
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
    if (read == -1) /* Handle EOF (Ctrl+D) */
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

    /* If command is "exit", terminate the shell */
    if (strcmp(*command, "exit") == 0)
    {
        return 0; /* Exit the shell */
    }

    /* Execute the command */
    execute_command(*command, envp);

    return (1); /* Continue the shell */
}

/**
 * main - Entry point for the shell program.
 * @argc: The number of arguments passed to the shell (currently unused).
 * @argv: The arguments passed to the shell (currently unused).
 * @envp: The environment variables.
 *
 * Description: This function runs the shell. It repeatedly calls handle_input()
 * to read commands and execute them. It exits when the user types `exit` or
 * presses `Ctrl+D` (EOF).
 *
 * Return: 0 on successful exit of the shell.
 */
int main(int argc, char **argv, char **envp)
{
    char *command = NULL;
    size_t len = 0;
    int running = 1;

    (void)argc; /* Suppress unused parameter warning */
    (void)argv; /* Suppress unused parameter warning */

    /* Continuously handle input until the user exits */
    while (running)
    {
        running = handle_input(&command, &len, envp); /* Process user input */
    }

    /* Free memory allocated for the command before exiting */
    free(command);
    return (0);
}
