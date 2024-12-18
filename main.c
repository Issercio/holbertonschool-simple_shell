#include "simple_shell.h"

/**
 * main - Fonction principale du shell
 *
 * Cette fonction lance une boucle de shell, invite l'utilisateur, lit 
 * l'entrée et exécute la commande correspondante.
 * Elle gère aussi les commandes intégrées `exit` et `env`.
 *
 * Return: Retourne toujours 0.
 */
int main(void)
{
    char cmd[MAX_CMD_LENGTH];

    /* Boucle de shell */
    while (1)
    {
        /* Affiche l'invite */
        printf("$ ");

        /* Lire l'entrée de l'utilisateur */
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL)
        {
            /* Condition EOF (Ctrl+D) */
            printf("\n");
            exit(0);
        }

        /* Retirer le caractère de nouvelle ligne de l'entrée (si présent) */
        cmd[strcspn(cmd, "\n")] = 0;

        /* Vérifie si la commande est vide */
        if (strlen(cmd) == 0)
        {
            continue; /* Ignorer les commandes vides */
        }

        /* Essayer d'exécuter la commande */
        execute_command(cmd);
    }

    return (0); /* Cette ligne n'est jamais atteinte */
}
