#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Accès global aux variables d'environnement */
extern char **environ;

/* Déclarations des fonctions */
void handle_error(const char *error_message);
void execute_command(char *command);
int handle_input(char **command, size_t *len);

#endif /* SIMPLE_SHELL_H */
