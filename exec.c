#include "main.h"
#include <sys/wait.h>
#include <errno.h>

/*void handle_process(char *command, char **args)     printf("Exécution de la commande : %s\n", command);*/

/* Fonction pour exécuter des commandes externes*/
void handle_process(char **args) {

    pid_t pid = fork();

 
    if (pid == -1) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        /* Enfant*/
       char *path = args[0];
        
        if (args[0][0] != '/' && args[0][0] != '.') {
            /* Tenter d'ajouter un './' au début si aucun '/' n'est fourni*/
            char *command_with_path = malloc(strlen("./") + strlen(path) + 1);  /* pour './' + nom de la commande + '\0'*/
            if (command_with_path == NULL) {
                perror("malloc failed");
                exit(1);
            }
            strcpy(command_with_path, "./");
            strcat(command_with_path, path);
            path = command_with_path;
        }

        /* Exécuter la commande via execve avec le chemin absolu*/
        if (execve(path, args, environ) == -1)
		{
           if (errno == ENOENT) 
		   {
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		   }
		   else
		   {			
			perror("./hsh");
		   }
            exit(1);
        }
    } else {
        /* Parent*/
        wait(NULL);
    }
}