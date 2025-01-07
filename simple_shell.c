#include "simple_shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>

/**
 * find_command_in_path - Searches for a command in directories listed in PATH.
 * @command: The command to search for.
 * @envp: The environment variables (currently unused).
 *
 * Description: This function splits the PATH environment variable into individual
 * directories and checks each one for the given command. If found, the full
 * path to the command is returned. If not found, NULL is returned.
 *
 * Return: Full path of the command if found, NULL if not found.
 */
char *find_command_in_path(char *command, char **envp)
{
    char *path_env, *path = NULL, *full_path = NULL;

    (void)envp; /* Suppress unused parameter warning */

    /* Get PATH from the environment */
    path_env = getenv("PATH");

    /* If PATH is not set, return NULL */
    if (path_env == NULL)
    {
        return (NULL);
    }

    /* Split the PATH into directories using strtok() */
    path = strtok(path_env, ":");
    while (path != NULL)
    {
        /* Allocate memory for full command path */
        full_path = malloc(strlen(path) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            return (NULL);
        }

        /* Build the full path by appending command to directory */
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, command);

        /* Check if command is executable */
        if (access(full_path, X_OK) == 0)
        {
            return (full_path); /* Return the full path if executable */
        }

        /* Free allocated memory and check the next directory in PATH */
        free(full_path);
        path = strtok(NULL, ":");
    }

    return (NULL); /* Command not found in any directory */
}

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

    /* Set up argument vector for execve */
    argv[0] = command;
    argv[1] = NULL;

    /* Create a new child process using fork */
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0) /* Child process */
    {
        char *path_command = command;

        /* If the command is not an absolute or relative path, search in PATH */
        if (command[0] != '/' && command[0] != '.')
        {
            path_command = find_command_in_path(command, envp);
            if (path_command == NULL)
            {
                perror(command); /* Command not found */
                exit(127); /* Exit child process with error code */
            }
        }

        /* Execute the command */
        if (execve(path_command, argv, envp) == -1)
        {
            perror(command); /* If execve fails */
            exit(127); /* Exit child process with error code */
        }
    }
    else /* Parent process */
    {
        wait(&status); /* Wait for the child process to terminate */
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

    /* Check if the command is executable and execute it */
    if (access(*command, X_OK) == 0)
    {
        execute_command(*command, envp);
    }
    else
    {
        /* Check if the command is found in PATH and execute */
        execute_command(*command, envp);
    }

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
