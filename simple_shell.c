#include "simple_shell.h"

/**
* main - Point d'entrée pour le programme shell.
* @argc: Le nombre d'arguments passés au shell (non utilisé ici).
* @argv: Les arguments passés au shell (non utilisés ici).
* @envp: Les variables d'environnement.
*
* Description: Cette fonction fait tourner le shell en boucle. Elle appelle
* handle_input() pour lire et exécuter des commandes. Le shell se termine
* lorsque l'utilisateur entre "exit" ou appuie sur Ctrl+D (EOF).
*
* Return: 0 si le shell se termine avec succès.
*/
int main(int argc, char **argv, char **envp)
{
	char *command = NULL;

	size_t len = 0;
	int running = 1;

	/* Supprimer les avertissements sur les paramètres non utilisés */
	(void)argc;
	(void)argv;

	/* Continuer à traiter les entrées tant que l'utilisateur ne quitte pas */
	while (running)
	{
		running = handle_input(&command, &len, envp);
	}

	/* Libérer la mémoire allouée pour la commande avant de quitter */
	free(command);

	return (0);
}
