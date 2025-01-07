#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024
extern char **environ;  /* Pour accéder aux variables d'environnement*/

/* Fonction pour afficher le prompt*/
void display_prompt(void);

/* Fonction pour exécuter une commande interne ou externe*/
void execute_command(char *command);

/* Fonction pour gérer les processus fils*/
void handle_process(char **args);

/* Fonction pour gérer la commande env*/
void print_env(void);



#endif