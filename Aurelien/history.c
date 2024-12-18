#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#include <stddef.h>


void add_to_history(char *command)
{
FILE *history_file = fopen(HISTORY_FILE, "a");
if (!history_file)
{
perror("Erreur d'ouverture du fichier historique");
return;
}
fprintf(history_file, "Commande : %s\n", command);
fclose(history_file);
}

void clear_history(void)
{
if (remove("history.txt") == 0) {
printf("Historique effacé.\n");
} else {
perror("Erreur lors de l'effacement de l'historique");
}
}