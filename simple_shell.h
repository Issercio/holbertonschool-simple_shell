#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

/* Function prototypes */
void execute_command(char *command, char **envp);
int handle_input(char **command, size_t *len, char **envp);

#endif /* SIMPLE_SHELL_H */
