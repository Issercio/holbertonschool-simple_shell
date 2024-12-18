#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#include <stddef.h>
#include <sys/types.h>

#define MAX_CMD_LENGTH 1024
/* Fonction pour gérer la commande "exit"*/
void handle_exit(void)
{
printf("Sortie du shell.\n");
exit(0);
}



/* Fonction pour exécuter la commande*/
void execute_command(char *input) {
pid_t pid;
char *args[MAX_CMD_LENGTH / 2];  /* Tableau pour les arguments */
char *token = strtok(input, " ");  /* Séparer la commande en mots */
char *path = getenv("PATH");  /* Obtenir la variable d'environnement PATH */
extern char **environ;  /* Déclaration de la variable environ*/
int j = 0;

while (token != NULL) {
args[j++] = token;
token = strtok(NULL, " ");
}
args[j] = NULL;  /* Terminer la liste d'arguments par NULL */

if (args[0] == NULL) {
return;  /* Si la commande est vide, rien à faire */
}

/* Vérifier si la commande "exit" a été entrée */
if (strcmp(args[0], "exit") == 0) {
	clear_history();
handle_exit();
return;
}

/* Vérifier si la commande "env" a été entrée */
if (strcmp(args[0], "env") == 0) {
/*Afficher les variables d'environnement*/
for (j = 0; environ[j] != NULL; j++) {
	printf("%s\n", environ[j]);
}
return;
}

/* Créer un processus pour exécuter la commande */
pid = fork();
if (pid == -1) {
perror("Erreur fork");
return;
}

if (pid == 0) {
/* Enfant : essayer d'exécuter la commande avec execve */
 {
char cmd_path[MAX_CMD_LENGTH];

char *dir = strtok(path, ":");  /* Diviser PATH par ':' */

/* Chercher dans chaque répertoire du PATH */
while (dir != NULL)
{
	/* Construire le chemin complet de la commande */
	sprintf(cmd_path,"%s/%s", dir, args[0]);

	/* Vérifier si le fichier est exécutable */
	if (access(cmd_path, X_OK) == 0)
	{
		/* Si la commande existe, utiliser execve pour l'exécuter */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("Erreur execve");
			exit(1);
		}
	}

	/* Passer au répertoire suivant dans PATH */
	dir = strtok(NULL, ":");
}
}

/* Si la commande n'est pas trouvée dans PATH */
fprintf(stderr, "Commande introuvable : %s\n", args[0]);
exit(1);
}
else
{
/* Parent : attendre la fin du processus enfant */
wait(NULL);
}
}

/* Fonction pour lire l'entrée de l'utilisateur */
void read_input(char *input) {
printf("MonShell> ");
if (fgets(input, MAX_CMD_LENGTH, stdin) == NULL) {
	clear_history();
	printf("Historique effacé.");
perror("Erreur de lecture");
exit(1);
}
input[strcspn(input, "\n")] = 0;  /* Enlever le saut de ligne */
}

/* Fonction pour vérifier si une commande existe dans PATH */
int check_command_exists(char *command)
{
char *path = getenv("PATH");
char command_with_path[MAX_CMD_LENGTH];
char *token = strtok(path, ":");

while (token != NULL)
{
sprintf(command_with_path,"%s/%s", token, command);
if (access(command_with_path, X_OK) == 0)
{
	return (1);  /* La commande existe */
}
token = strtok(NULL, ":");
}

return (0);  /* La commande n'existe pas */
}
