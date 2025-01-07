#include "main.h"

/* Fonction pour gérer les commandes internes*/
void execute_command(char *command) {
    char *args[MAX_INPUT / 2];
    char *token;
    int i = 0;

   /* Découper la commande en arguments*/
    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;  /* Terminer la liste d'arguments*/

    /* Vérifier les commandes internes*/
    if (strcmp(args[0], "exit") == 0) {
        exit(0);  /* Quitter le shell*/
    } else if (strcmp(args[0], "env") == 0) {
        print_env();  /* Afficher les variables d'environnement*/
    } else {
        handle_process(args);  /* Exécuter des commandes externes*/
    }
}