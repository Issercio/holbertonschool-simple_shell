#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

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

/* Prototypes des fonctions */
char **parse_args(char *cmd);
int command_exists(char *cmd);
void execute_command(char *cmd);
void print_env(void);

#endif /* SIMPLE_SHELL_H */
