#include "simple_shell.h"

/**
* handle_error - Displays an error message.
* @error_message: The error message to display.
*
* This function prints the provided error message.
*/
void handle_error(const char *error_message)
{
	perror(error_message); /* Display the error */
}
