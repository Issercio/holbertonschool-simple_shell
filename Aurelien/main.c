#include "main.h"

int main(int argc, char **argv) {
	
    char input[MAX_INPUT];
	(void)argc;  /* Indiquer explicitement que 'argc' n'est pas utilisé*/
    (void)argv;  /* Indiquer explicitement que 'argv' n'est pas utilisé*/
    
    /* Si on est en mode non interactif, on lit depuis stdin*/
    if (isatty(STDIN_FILENO)) {
        /* Mode interactif*/
        while (1) {
            display_prompt();
            if (fgets(input, MAX_INPUT, stdin) == NULL) {
                perror("fgets failed");
                break;
            }
            
            /* Enlever le '\n' final*/
            input[strcspn(input, "\n")] = 0;

            /* Exécuter la commande*/
            execute_command(input);
        }
    } else {
        /* Mode non interactif (par exemple, redirection de fichier)*/
        while (fgets(input, MAX_INPUT, stdin) != NULL) {
            input[strcspn(input, "\n")] = 0;
            execute_command(input);
        }
    }

    return 0;
}