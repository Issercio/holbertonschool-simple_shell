#include "main.h"
#include <sys/wait.h>
#include <errno.h>

/*void handle_process(char *command, char **args)     printf("Exécution de la commande : %s\n", command);*/

/* Fonction pour exécuter des commandes externes avec execve */
void handle_process(char **args) {
char *path = args[0];
pid_t pid = fork();

/* Si la commande ne commence pas par '/' ou './', on la cherche dans PATH*/
if (path[0] != '/' && path[0] != '.') {
	/* Chercher l'exécutable dans les répertoires du PATH*/
	char *path_env = getenv("PATH");
	char *path_copy = strdup(path_env);  /* Dupliquer la chaîne PATH*/
	char *dir = strtok(path_copy, ":");  /* Séparer les répertoires dans PATH*/
	int found = 0;  /* Variable pour vérifier si la commande a été trouvée*/

	while (dir != NULL) {
		/* Construire le chemin absolu en ajoutant le répertoire au nom de la commande*/
		char *full_path = malloc(strlen(dir) + strlen(path) + 2);  /* +2 pour '/' et '\0'*/
		if (full_path == NULL) {
			perror("malloc failed");
			free(path_copy);
			exit(1);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, path);

		/* Vérifier si le fichier existe et est exécutable*/
		if (access(full_path, X_OK) == 0) {
			path = full_path;  /* Mettre à jour le chemin de la commande*/
			found = 1;
			break;
		}

		free(full_path);
		dir = strtok(NULL, ":");  /* Passer au répertoire suivant dans PATH*/
	}

	free(path_copy);

	/* Si la commande n'a pas été trouvée dans PATH*/
	if (!found) {
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return;  /* Ne pas appeler fork si la commande n'existe pas*/
	}
}

/* Si la commande existe, procéder avec le fork et execve*/

if (pid == -1) {
	perror("fork failed");
	return;
}

if (pid == 0) {
	/* Enfant */
	/* Exécuter la commande via execve avec le chemin absolu*/
	if (execve(path, args, environ) == -1) {
		if (errno == ENOENT) {
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		} else {
			perror("./hsh");
		}
		exit(1);
	}
} else {
	/* Parent */
	wait(NULL);
}
}