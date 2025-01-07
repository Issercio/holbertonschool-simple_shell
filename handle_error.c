#include "simple_shell.h"

/**
* handle_error - Affiche un message d'erreur.
* @error_message: Le message d'erreur à afficher.
*
* Cette fonction affiche le message d'erreur fourni.
*/
void handle_error(const char *error_message)
{
	perror(error_message); /* Affiche l'erreur */
}
