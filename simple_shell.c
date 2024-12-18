#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

extern char **environ;

/**
 * parse_args - Splits the command line into an array of arguments
 * @cmd: The input command string
 *
 * Return: A dynamically allocated array of arguments. The array is null-terminated.
 */
char **parse_args(char *cmd)
{
    char **args;
    char *token;
    int i = 0;

    args = malloc(MAX_ARGS * sizeof(char *));
    if (args == NULL)
    {
        perror("malloc");
        exit(1);
    }

    /* Tokenize the input command string */
    token = strtok(cmd, " ");
    while (token != NULL)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; /* Null-terminate the argument list */
    return (args);
}

/**
 * command_exists - Checks if a command exists in the directories listed in PATH
 * @cmd: The command to search for
 *
 * Return: 1 if the command exists in the PATH, 0 otherwise
 */
int command_exists(char *cmd)
{
    char *path;
    char *path_copy;
    char *dir;
    char full_cmd[MAX_CMD_LENGTH];

    path = getenv("PATH");
    if (!path)
    {
        return (0); /* If PATH is not set, assume command doesn't exist */
    }

    path_copy = strdup(path); /* Declare this variable at the beginning */
    if (path_copy == NULL)
    {
        perror("strdup");
        return (0);
    }

    dir = strtok(path_copy, ":");

    /* Try each directory in PATH */
    while (dir != NULL)
    {
        /* Construct the full command path */
        snprintf(full_cmd, sizeof(full_cmd), "%s/%s", dir, cmd);

        /* Check if the command is executable */
        if (access(full_cmd, X_OK) == 0)
        {
            free(path_copy);
            return (1); /* Command found and executable */
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (0); /* Command not found in any directory in PATH */
}

/**
 * execute_command - Executes the given command
 * @cmd: The command string
 *
 * This function forks a child process to execute the given command.
 * If the command is `exit`, the shell will terminate.
 * If the command is `env`, the environment variables will be printed.
 * If the command is found, it is executed, otherwise, an error is printed.
 */
void execute_command(char *cmd)
{
    pid_t pid;
    char **args;
    int i;

    /* Check if the user entered the "exit" command */
    if (strcmp(cmd, "exit") == 0)
    {
        exit(0); /* Exit the shell */
    }

    /* Check if the user entered the "env" command */
    if (strcmp(cmd, "env") == 0)
    {
        /* Print all environment variables */
        for (i = 0; environ[i] != NULL; i++)
        {
            printf("%s\n", environ[i]);
        }
        return;
    }

    pid = fork(); /* Create a child process */
    if (pid == -1)
    {
        perror("Fork failed"); /* Error forking */
        return;
    }

    if (pid == 0) /* Child process */
    {
        args = parse_args(cmd); /* Parse the command line into arguments */

        /* Check if the command is a valid executable in the PATH */
        if (access(args[0], X_OK) == 0)
        {
            if (execve(args[0], args, environ) == -1) /* Execute the command */
            {
                perror(args[0]);
                exit(1);
            }
        }
        else if (command_exists(args[0])) /* If command is in PATH */
        {
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");

            /* Try each directory in PATH */
            while (dir != NULL)
            {
                char full_cmd[MAX_CMD_LENGTH];
                snprintf(full_cmd, sizeof(full_cmd), "%s/%s", dir, args[0]);

                if (execve(full_cmd, args, environ) == -1) /* Try executing the command */
                {
                    dir = strtok(NULL, ":");
                    continue;
                }
            }

            /* If command is not found, print error */
            perror(args[0]);
            exit(1);
        }
        else
        {
            /* Command is not executable or found in PATH */
            perror(args[0]);
            exit(1);
        }
    }
    else /* Parent process */
    {
        wait(NULL); /* Wait for the child process to finish */
    }
}

/**
 * main - Main function of the simple shell
 *
 * This function runs the shell loop, prompting the user for input,
 * reading the input, and then executing the appropriate command.
 * It also handles `exit` and `env` built-in commands.
 *
 * Return: Always returns 0
 */
int main(void)
{
    char cmd[MAX_CMD_LENGTH];

    /* Shell prompt loop */
    while (1)
    {
        /* Display the prompt */
        printf("$ ");

        /* Read user input */
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL)
        {
            /* End of file (Ctrl+D) condition */
            printf("\n");
            exit(0);
        }

        /* Remove the newline character from the input (if any) */
        cmd[strcspn(cmd, "\n")] = 0;

        /* Check if the command is empty */
        if (strlen(cmd) == 0)
        {
            continue; /* Ignore empty commands */
        }

        /* Try to execute the command */
        execute_command(cmd);
    }

    return (0); /* This line is never reached */
}
