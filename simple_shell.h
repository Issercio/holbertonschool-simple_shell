#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

/* Fonction pour afficher les erreurs */
void handle_error(const char *error_message);

/* Fonction pour exécuter la commande */
void execute_command(char *command, char **envp);

/* Fonction pour gérer l'entrée de l'utilisateur */
int handle_input(char **command, size_t *len, char **envp);

#endif /* SIMPLE_SHELL_H */
