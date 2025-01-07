#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Function Prototypes */
void execute_command(char *command);
int handle_input(char **command, size_t *len);

#endif /* SIMPLE_SHELL_H */
