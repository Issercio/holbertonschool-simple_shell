#include "simple_shell.h"

/**
 * execute_command - Exécute la commande utilisateur dans un processus enfant.
 * @command: La commande à exécuter.
 * @envp: Les variables d'environnement pour le nouveau processus.
 *
 * Description: Cette fonction crée un processus enfant. Dans le processus enfant,
 * elle tente d'exécuter la commande avec execve(). Si la commande ne peut pas être
 * exécutée, un message d'erreur est affiché avec un message spécifique pour "ls".
 * Le processus parent attend la fin du processus enfant avant de continuer.
 */
void execute_command(char *command, char **envp)
{
    pid_t pid;
    char *full_command = NULL;
    char *argv[2];  /* Tableau d'arguments pour execve */

    pid = fork();  /* Créer un processus enfant */

    if (pid == -1)
    {
        handle_error("Fork failed");
        return;
    }

    if (pid == 0)  /* Dans le processus enfant */
    {
        /* Allocation pour le chemin complet de la commande (ex : /bin/ls) */
        full_command = malloc(strlen(command) + 1);
        if (full_command == NULL)
        {
            handle_error("Memory allocation failed");
            exit(1);
        }

        strcpy(full_command, command);  /* Copie de la commande dans full_command */

        /* Préparer argv pour execve */
        argv[0] = full_command;  /* La commande complète */
        argv[1] = NULL;  /* Aucun autre argument à passer */

        /* Essayer d'exécuter la commande avec execve */
        if (execve(full_command, argv, envp) == -1)
        {
            /* Vérifier si la commande est "ls" et afficher le message personnalisé */
            if (strcmp(command, "ls") == 0)
            {
                fprintf(stderr, "Command not found: No such file or directory\n");
            }
            else
            {
                handle_error("Command not found");
            }
            free(full_command);  /* Libérer la mémoire si l'exécution échoue */
            exit(1);
        }

        free(full_command);  /* Libérer la mémoire après l'exécution */
    }
    else  /* Dans le processus parent */
    {
        wait(NULL);  /* Attendre que le processus enfant se termine */
    }
}
