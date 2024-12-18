#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 1024

int main() {
char input[MAX_CMD_LENGTH];

while (1) {
	printf("MonShell> ");
	if (fgets(input, MAX_CMD_LENGTH, stdin) == NULL) {
		perror("Erreur de lecture");
		exit(1);
	}
	input[strcspn(input, "\n")] = 0;  /* Enlever le saut de ligne*/

	/* Si la commande est "exit", effacer l'historique et quitter le shell*/
	if (strcmp(input, "exit") == 0) {
		clear_history();  /* Effacer l'historique*/
		printf("Sortie du shell.\n");
		break;
	}

	/* Ajouter la commande à l'historique*/
	add_to_history(input);

	/* Si la commande existe, l'exécuter*/
	if (check_command_exists(input)) {
		execute_command(input);
	} else {
		printf("Commande introuvable : %s\n", input);
	}
}

return 0;
}