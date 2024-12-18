#include "simple_shell.h"

/**
 * execute_command - Exécute la commande donnée
 * @cmd: La chaîne de caractères représentant la commande
 *
 * Cette fonction crée un processus enfant pour exécuter la commande donnée.
 * Si la commande est `exit`, le shell se termine.
 * Si la commande est `env`, les variables d'environnement sont affichées.
 * Si la commande est trouvée, elle est exécutée, sinon une erreur est affichée.
 */
void execute_command(char *cmd)
{
    pid_t pid;
    char **args;

    /* Vérifie si l'utilisateur a entré la commande "exit" */
    if (strcmp(cmd, "exit") == 0)
    {
        exit(0); /* Quitte le shell */
    }

    /* Vérifie si l'utilisateur a entré la commande "env" */
    if (strcmp(cmd, "env") == 0)
    {
        /* Affiche toutes les variables d'environnement */
        print_env();
        return;
    }

    pid = fork(); /* Crée un processus enfant */
    if (pid == -1)
    {
        perror("Erreur lors du fork"); /* Erreur de fork */
        return;
    }

    if (pid == 0) /* Processus enfant */
    {
        args = parse_args(cmd); /* Analyse la ligne de commande en arguments */

        if (command_exists(args[0])) /* Si la commande est dans PATH */
        {
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");
            char full_cmd[MAX_CMD_LENGTH];

            /* Essayer chaque répertoire dans PATH */
            while (dir != NULL)
            {
                snprintf(full_cmd, sizeof(full_cmd), "%s/%s", dir, args[0]);

                if (execve(full_cmd, args, environ) == -1) /* Essayer d'exécuter la commande */
                {
                    dir = strtok(NULL, ":");
                    continue;
                }
            }

            /* Si la commande n'a pas été trouvée, afficher une erreur */
            perror(args[0]);
            exit(1);
        }
        else
        {
            /* Commande non trouvée ou non exécutable */
            perror(args[0]);
            exit(1);
        }
    }
    else /* Processus parent */
    {
        wait(NULL); /* Attendre la fin du processus enfant */
    }
}
