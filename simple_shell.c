#include "simple_shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>

/**
 * find_command_in_path - Recherche une commande dans les répertoires listés dans PATH.
 * @command: La commande à rechercher.
 * @envp: Les variables d'environnement (non utilisées ici).
 *
 * Description: Cette fonction découpe la variable PATH en répertoires individuels et
 * vérifie chaque répertoire pour la commande donnée. Si trouvée, le chemin complet vers
 * la commande est retourné. Sinon, NULL est retourné.
 *
 * Return: Le chemin complet de la commande si trouvé, NULL sinon.
 */
char *find_command_in_path(char *command, char **envp)
{
    char *path_env, *path = NULL, *full_path = NULL;

    (void)envp; /* Supprime l'avertissement sur le paramètre inutilisé */

    /* Récupère le PATH depuis les variables d'environnement */
    path_env = getenv("PATH");

    /* Si PATH n'est pas défini, retourne NULL */
    if (path_env == NULL)
    {
        return (NULL);
    }

    /* Découpe le PATH en répertoires avec strtok() */
    path = strtok(path_env, ":");
    while (path != NULL)
    {
        /* Alloue de la mémoire pour le chemin complet */
        full_path = malloc(strlen(path) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            return (NULL);
        }

        /* Construit le chemin complet en ajoutant la commande au répertoire */
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, command);

        /* Vérifie si la commande est exécutable */
        if (access(full_path, X_OK) == 0)
        {
            return (full_path); /* Retourne le chemin complet si exécutable */
        }

        /* Libère la mémoire allouée et vérifie le répertoire suivant dans PATH */
        free(full_path);
        path = strtok(NULL, ":");
    }

    return (NULL); /* Commande non trouvée dans aucun répertoire */
}

/**
 * execute_command - Exécute la commande donnée avec execve().
 * @command: La commande à exécuter.
 * @envp: Les variables d'environnement.
 *
 * Description: Cette fonction crée un processus fils avec fork(). Dans le processus
 * fils, la commande est exécutée avec execve(). Si execve() échoue, un message d'erreur
 * est affiché, et le processus fils se termine avec le code d'erreur 127. Le processus
 * parent attend que le processus fils se termine.
 *
 * Return: Aucun.
 */
void execute_command(char *command, char **envp)
{
    pid_t pid;
    int status;
    char *argv[2];

    /* Prépare le vecteur d'arguments pour execve */
    argv[0] = command;
    argv[1] = NULL;

    /* Crée un nouveau processus fils avec fork */
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0) /* Processus fils */
    {
        char *path_command = command;

        /* Si la commande n'est pas un chemin absolu ou relatif, chercher dans PATH */
        if (command[0] != '/' && command[0] != '.')
        {
            path_command = find_command_in_path(command, envp);
            if (path_command == NULL)
            {
                fprintf(stderr, "%s: command not found\n", command); /* Commande non trouvée */
                exit(127); /* Quitter le processus fils avec le code d'erreur */
            }
        }

        /* Exécuter la commande */
        if (execve(path_command, argv, envp) == -1)
        {
            perror(command); /* Si execve échoue */
            exit(127); /* Quitter le processus fils avec le code d'erreur */
        }
    }
    else /* Processus parent */
    {
        wait(&status); /* Attendre que le processus fils se termine */
    }
}

/**
 * handle_input - Gère l'entrée de l'utilisateur, exécute les commandes et retourne si on continue.
 * @command: Pointeur vers le buffer de commande.
 * @len: Pointeur vers la longueur du buffer de commande.
 * @envp: Les variables d'environnement.
 *
 * Description: Cette fonction affiche un prompt si on est en mode interactif, lit
 * l'entrée de l'utilisateur, vérifie si la commande est valide et l'exécute. Si l'entrée
 * est vide, elle ne fait rien. Elle retourne 1 pour continuer le shell ou 0 pour sortir.
 *
 * Return: 1 pour continuer le shell, 0 pour quitter.
 */
int handle_input(char **command, size_t *len, char **envp)
{
    ssize_t read;

    /* Afficher le prompt si on est en mode interactif */
    if (isatty(STDIN_FILENO))
    {
        printf("#cisfun$ ");
    }
    fflush(stdout);

    /* Lire l'entrée de l'utilisateur */
    read = getline(command, len, stdin);
    if (read == -1) /* Gérer l'EOF (Ctrl+D) */
    {
        if (isatty(STDIN_FILENO))
        {
            printf("\n");
        }
        return (0); /* Quitter le shell */
    }

    /* Supprimer le caractère de nouvelle ligne à la fin de la commande */
    if ((*command)[read - 1] == '\n')
    {
        (*command)[read - 1] = '\0';
    }

    /* Si l'entrée est vide, retourner 1 pour continuer */
    if ((*command)[0] == '\0')
    {
        return (1);
    }

    /* Vérifier si la commande est exécutable et l'exécuter */
    if (access(*command, X_OK) == 0)
    {
        execute_command(*command, envp);
    }
    else
    {
        /* Vérifier si la commande est trouvée dans PATH et l'exécuter */
        execute_command(*command, envp);
    }

    return (1); /* Continuer le shell */
}

/**
 * main - Point d'entrée du programme shell.
 * @argc: Le nombre d'arguments passés au shell (non utilisés ici).
 * @argv: Les arguments passés au shell (non utilisés ici).
 * @envp: Les variables d'environnement.
 *
 * Description: Cette fonction exécute le shell. Elle appelle continuellement handle_input()
 * pour lire et exécuter les commandes. Elle quitte lorsque l'utilisateur tape `exit` ou
 * appuie sur `Ctrl+D` (EOF).
 *
 * Return: 0 lors de la sortie du shell avec succès.
 */
int main(int argc, char **argv, char **envp)
{
    char *command = NULL;
    size_t len = 0;
    int running = 1;

    (void)argc; /* Supprime l'avertissement sur le paramètre inutilisé */
    (void)argv; /* Supprime l'avertissement sur le paramètre inutilisé */

    /* Boucle infinie pour gérer l'entrée de l'utilisateur */
    while (running)
    {
        running = handle_input(&command, &len, envp); /* Traiter l'entrée de l'utilisateur */
    }

    /* Libérer la mémoire allouée pour la commande avant de quitter */
    free(command);
    return (0);
}
