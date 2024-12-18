#include "simple_shell.h"

/**
* parse_args - Divise une ligne de commande en mots.
* @line: La ligne de commande entrée par l'utilisateur.
*
* Retourne un tableau de chaînes de caractères représentant les arguments.
*
* Retour: Un tableau de chaînes de caractères (arguments) ou NULL si échec.
*/
char **parse_args(char *line)
{
	char **args = malloc(sizeof(char *) * 64); /* Allocation d'un tableau */

	int i = 0;

	if (!args)
	{
		perror("malloc failed");
		exit(1);
	}

	/* Diviser la ligne en arguments à l'aide de strtok() */
	char *token = strtok(line, " ");

	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL; /* Marquer la fin de la liste des arguments */

	return (args); /* Parenthèses ajoutées */
}

/**
* command_exists - Vérifie si une commande existe dans le répertoire actuel.
* @command: Le nom de la commande à vérifier.
*
* Retourne 1 si la commande existe, 0 sinon.
*
* Retour: 1 si la commande existe, sinon 0.
*/
int command_exists(char *command)
{
	if (access(command, X_OK) == 0)
		return (1); /* Parenthèses ajoutées */
	return (0); /* Parenthèses ajoutées */
}

/**
* print_env - Affiche les variables d'environnement.
*
* Cette fonction parcourt et affiche toutes les variables d'environnement.
*/
void print_env(void)
{
	/* Déplacer cette ligne dans simple_shell.h */
	/* extern char **environ; */

	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
