#include "Main.h"
#include <stdio.h>
#include <stdlib.h>

/* Fonction pour gérer la commande "exit"*/
void handle_exit() {
	
    printf("Sortie du shell.\n");
    exit(0);
}

void add_to_history(char *command) {
    FILE *history_file = fopen(HISTORY_FILE, "a");
    if (!history_file) {
        perror("Erreur d'ouverture du fichier historique");
        return;
    }
    fprintf(history_file, "Commande :%s\n", command);
    fclose(history_file);
}

void clear_history() {
    if (remove("history.txt") == 0) {
        printf("Historique effacé.\n");
    } else {
        perror("Erreur lors de l'effacement de l'historique");
    }
}

/* Fonction pour exécuter la commande*/
void execute_command(char *input) {
    pid_t pid;
    char *args[MAX_CMD_LENGTH / 2];  /* Tableau pour les arguments*/
    char *token = strtok(input, " ");  /* Séparer la commande en mots*/

    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  /* Terminer la liste d'arguments par NULL*/

    if (args[0] == NULL) {
        return;  /* Si la commande est vide, rien à faire*/
    }

    /* Vérifier si la commande "exit" a été entrée*/
    if (strcmp(args[0], "exit") == 0) {
        handle_exit();
        return;
    }

    /* Créer un processus pour exécuter la commande*/
    pid = fork();
    if (pid == -1) {
        perror("Erreur fork");
        return;
    }

    if (pid == 0) {
        /* Enfant : exécuter la commande*/
        if (execvp(args[0], args) == -1) {
            perror("Commande introuvable");
            exit(1);
        }
    } else {
        /* Parent : attendre la fin du processus enfant*/
        wait(NULL);
    }
}

/* Fonction pour lire l'entrée de l'utilisateur*/
void read_input(char *input) {
    printf("MonShell> ");
    if (fgets(input, MAX_CMD_LENGTH, stdin) == NULL) {
        perror("Erreur de lecture");
        exit(1);
    }
    input[strcspn(input, "\n")] = 0;  /* Enlever le saut de ligne*/
}

/* Fonction pour vérifier si une commande existe dans PATH*/
int check_command_exists(char *command) {
    char *path = getenv("PATH");
    char command_with_path[MAX_CMD_LENGTH];
    char *token = strtok(path, ":");

    while (token != NULL) {
        snprintf(command_with_path, sizeof(command_with_path), "%s/%s", token, command);
        if (access(command_with_path, X_OK) == 0) {
            return 1;  /* La commande existe*/
        }
        token = strtok(NULL, ":");
    }

    return 0;  /* La commande n'existe pas*/
}

