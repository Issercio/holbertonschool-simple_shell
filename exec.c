#include "main.h"
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Fonction pour exécuter des commandes externes */
void handle_process(char **args) {
    pid_t pid = fork();  // Crée un nouveau processus

    if (pid == -1) {
        // En cas d'erreur avec fork()
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        // Processus enfant
        if (execve(args[0], args, environ) == -1) {  // Essaie d'exécuter la commande
            // Si execve échoue, on affiche l'erreur
            if (errno == ENOENT) {
                fprintf(stderr, "Error: '%s' command not found\n", args[0]);
            } else {
                perror("execve failed");
            }
            exit(1);  // Quitte le processus enfant en cas d'échec
        }
    } else {
        // Processus parent
        wait(NULL);  // Attends que l'enfant ait fini son exécution
    }
}