#include "main.h"

/* Fonction pour afficher les variables d'environnement*/
void print_env(void) {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}