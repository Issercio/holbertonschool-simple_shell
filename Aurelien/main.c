#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_CMD_LENGTH 1024
#define HIST_SIZE 100


/*
*char history[HIST_SIZE];   Tableau d'historique de commandes
*int history_index Index pour l'historique
*/


/* Déclaration des variables globales */



/*
* main - Function principale qui exécute un shell simple.
*
* Description:
*   La fonction principale gère le flux de commande du shell. Elle lit
*   une commande entrée par l'utilisateur, l'ajoute à l'historique, et
*   exécute la commande correspondante. Elle fonctionne en boucle infinie
*   pour accepter les commandes de l'utilisateur jusqu'à ce qu'une
* interruption soit effectuée (par exemple, un signal de sortie).
*
* Paramètres:
*   Aucun.
*
* Valeur de retour:
*   Return 0. Cependant, la boucle étant infinie, cette valeur n'est
*   jamais atteinte.
*/
int main(void)
{
/* Déclaration des variables */
char input[MAX_CMD_LENGTH];

/*history_index = 0;   Initialisation de l'index d'historique */


while (1)
{
	/* Lire l'entrée de l'utilisateur */
	read_input(input);

	/* Ajouter la commande à l'historique */
	add_to_history(input);

	/* Exécuter la commande */
	execute_command(input);
}

return (0);
}
