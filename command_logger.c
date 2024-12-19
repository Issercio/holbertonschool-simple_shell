#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
* log_command - Enregistre une commande dans un fichier journal.
* @command: La commande à enregistrer.
*
* Description: Cette fonction enregistre
* la commande exécutée dans un fichier journal
* et ajoute un horodatage.
*/
void log_command(char *command)
{
	FILE *file;
	time_t current_time;
	char *timestamp;

	/* Ouvrir le fichier journal en mode ajout */
	file = fopen("command_log.txt", "a");
	if (file == NULL)
	{
		perror("Erreur lors de l'ouverture du fichier journal");
		return;
	}

	/* Obtenir l'heure actuelle */
	current_time = time(NULL);
	timestamp = ctime(&current_time);

	/* Enlever le saut de ligne à la fin de l'horodatage */
	timestamp[strcspn(timestamp, "\n")] = 0;

	/* Écrire l'horodatage et la commande dans le fichier */
	fprintf(file, "[%s] Commande exécutée: %s\n", timestamp, command);

	/* Fermer le fichier */
	fclose(file);
}
