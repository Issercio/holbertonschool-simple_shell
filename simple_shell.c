#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024

/**
 * execute_command - Executes a command entered by the user.
 * @cmd: A string containing the command to execute.
 * 
 * This function forks a child process to execute the given command. If the 
 * command is successful, it will be executed in the child process. The parent
 * process waits for the child to complete.
 */
void execute_command(char *cmd)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        /* Child process */
        char *args[MAX_CMD_LENGTH];
        char *token = strtok(cmd, " ");
        int i = 0;

        /* Tokenize the command string into arguments */
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  /* Null-terminate the argument list */

        if (execvp(args[0], args) == -1) {
            perror(cmd);  /* Print error if execvp fails */
            exit(1);
        }
    } else {
        /* Parent process */
        wait(NULL);  /* Wait for child process to complete */
    }
}

/**
 * main - Main function for the shell program.
 * 
 * This function runs a simple shell that continuously prompts the user for
 * a command, reads the input, and executes the command in a new process.
 * The loop continues until the user exits the shell.
 * 
 * Return: Always 0.
 */
int main(void)
{
    char cmd[MAX_CMD_LENGTH];

    while (1) {
        /* Print the prompt */
        printf("#cisfun$ ");

        /* Read the user input */
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL) {
            printf("\n");
            exit(0);  /* Exit on EOF (Ctrl+D) */
        }

        /* Remove the trailing newline character from the input */
        cmd[strcspn(cmd, "\n")] = 0;

        /* If the user entered an empty command, skip it */
        if (strlen(cmd) == 0) {
            continue;
        }

        /* Execute the command */
        execute_command(cmd);
    }

    return 0;
}
