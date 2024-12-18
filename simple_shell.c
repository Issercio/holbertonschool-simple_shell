#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>  // Include this header for the wait function

#define MAX_CMD_LENGTH 1024

// Function to execute a command
void execute_command(char *cmd) {
    pid_t pid = fork();  // Create a child process

    if (pid == -1) {
        // Error forking
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        // Child process: Try to execute the command
        if (execve(cmd, (char *[]){cmd, NULL}, NULL) == -1) {
            // If execve fails, print an error message
            perror(cmd);
            exit(1);
        }
    } else {
        // Parent process: Wait for the child to finish
        wait(NULL);  // This line requires sys/wait.h
    }
}

int main(void) {
    char cmd[MAX_CMD_LENGTH];

    // Shell prompt loop
    while (1) {
        // Display the prompt
        printf("#cisfun$ ");
        
        // Read user input
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL) {
            // End of file (Ctrl+D) condition
            printf("\n");
            exit(0);
        }

        // Remove the newline character from the input (if any)
        cmd[strcspn(cmd, "\n")] = 0;

        // Check if the command is empty
        if (strlen(cmd) == 0) {
            continue; // Ignore empty commands
        }

        // Try to execute the command
        execute_command(cmd);
    }

    return 0;
}
