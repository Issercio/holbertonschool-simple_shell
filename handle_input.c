#include "simple_shell.h"

/**
* handle_input - Lit l'entrée de l'utilisateur, traite les commandes et les exécute.
* @command: Un pointeur vers une chaîne pour stocker la commande de l'utilisateur.
* @len: Un pointeur vers la taille du tampon pour stocker l'entrée de l'utilisateur.
*
* Return: 0 si le shell doit quitter, 1 si le shell doit continuer.
*/
int handle_input(char **command, size_t *len)
{
	ssize_t read;

	/* Afficher le prompt si nous sommes en mode interactif */
	if (isatty(STDIN_FILENO)) 
    {
		printf("#cisfun$ ");
	}
	fflush(stdout);

	/* Lire l'entrée de l'utilisateur */
	read = getline(command, len, stdin);
	if (read == -1) 
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

	/* Si la commande est vide, retourner 1 pour continuer */
	if ((*command)[0] == '\0') 
    {
		return (1);
	}

	/* Si la commande est "exit", terminer le shell */
	if (strcmp(*command, "exit") == 0) 
    {
		return (0); /* Quitter le shell */
	}

	/* Exécuter la commande */
	execute_command(*command);

	return (1); /* Continuer le shell */
}
