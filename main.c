#include "simple_shell.h"

/**
 * display_prompt - Affiche le prompt de commande.
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_command - Lit une ligne de commande de l'entrée standard.
 * @line: Pointeur vers la ligne lue.
 * @len: Taille de la ligne.
 *
 * Retourne le nombre de caractères lus ou -1 en cas d'erreur.
 */
ssize_t read_command(char **line, size_t *len)
{
	ssize_t nread = getline(line, len, stdin);

	if (nread == -1) /* Gérer l'erreur EOF ou erreur de lecture */
	{
		if (feof(stdin)) /* Gestion EOF (Ctrl+D) */
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			perror("getline");
		}
	}

	return (nread);
}

/**
 * process_command - Traite et exécute la commande.
 * @line: Ligne de commande entrée.
 */
void process_command(char *line)
{
	if (line == NULL)
		return;

	line[strcspn(line, "\n")] = '\0'; /* Supprimer le saut de ligne */

	/* Exécuter la commande */
	if (command_exists(line))
	{
		if (fork() == 0) /* Processus enfant */
		{
			if (execve(line, &line, environ) == -1)
			{
				perror(line);
			}
			exit(1);
		}
		wait(NULL); /* Attendre que le processus enfant termine */
	}
	else
	{
		write(STDOUT_FILENO, "Command not found\n", 18);
	}
}

/**
 * main - Fonction principale du shell.
 *
 * Retourne 0 si tout va bien.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		display_prompt(); /* Afficher le prompt */

		nread = read_command(&line, &len); /* Lire la commande */
		if (nread == -1)
			break;

		process_command(line); /* Traiter la commande */
	}

	free(line); /* Libérer la mémoire allouée pour la ligne */
	return (0);
}
