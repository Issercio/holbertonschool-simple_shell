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

/* Fonction pour afficher les erreurs */
void handle_error(const char *error_message);

/* Fonction pour exécuter la commande */
void execute_command(char *command);

/* Fonction pour gérer l'entrée de l'utilisateur */
int handle_input(char **command, size_t *len);


#endif /* SIMPLE_SHELL_H */
