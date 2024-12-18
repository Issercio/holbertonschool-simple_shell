#include "simple_shell.h"

/**
 * parse_args - Divise la chaîne de commande en un tableau d'arguments
 * @cmd: La chaîne de commande d'entrée
 *
 * Return: Un tableau dynamiquement alloué d'arguments. Le tableau est null-terminé.
 */
char **parse_args(char *cmd)
{
    char **args;
    char *token;
    int i = 0;

    args = malloc(MAX_ARGS * sizeof(char *));
    if (args == NULL)
    {
        perror("malloc");
        exit(1);
    }

    /* Divise la chaîne de commande en tokens */
    token = strtok(cmd, " ");
    while (token != NULL)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; /* Null-terminer la liste des arguments */
    return (args);
}

/**
 * command_exists - Vérifie si une commande existe dans les répertoires listés dans PATH
 * @cmd: La commande à rechercher
 *
 * Return: 1 si la commande existe dans le PATH, 0 sinon
 */
int command_exists(char *cmd)
{
    char *path;
    char *path_copy;
    char *dir;
    char full_cmd[MAX_CMD_LENGTH];

    path = getenv("PATH");
    if (!path)
    {
        return (0); /* Si PATH n'est pas défini, on suppose que la commande n'existe pas */
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        return (0);
    }

    dir = strtok(path_copy, ":");

    /* Essayer chaque répertoire dans PATH */
    while (dir != NULL)
    {
        snprintf(full_cmd, sizeof(full_cmd), "%s/%s", dir, cmd);

        if (access(full_cmd, X_OK) == 0)
        {
            free(path_copy);
            return (1); /* Commande trouvée et exécutable */
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (0); /* Commande non trouvée dans aucun répertoire de PATH */
}

/**
 * print_env - Affiche toutes les variables d'environnement
 */
void print_env(void)
{
    int i;

    /* Affiche toutes les variables d'environnement */
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}
