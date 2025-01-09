#include "simple_shell.h"
#include <sys/stat.h>

/**
 * find_executable - Searches for an executable in the PATH environment variable.
 * @command: The command to search for.
 *
 * Return: Full path to the executable if found, otherwise NULL.
 */
char *find_executable(char *command)
{
    char *path_env, *path, *token, *full_path;
    struct stat st;

    /* Check if the command is NULL or already executable with its given path */
    if (!command || access(command, X_OK) == 0)
        return (_strdup(command)); /* Duplicate the command string if accessible */

    /* Get the PATH environment variable */
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL); /* Return NULL if PATH is not set */

    /* Create a duplicate of the PATH environment variable for tokenization */
    path = _strdup(path_env);
    if (!path)
        return (NULL); /* Return NULL if memory allocation for duplication fails */

    /* Tokenize the PATH variable by splitting it on ':' (colon) */
    token = strtok(path, ":");
    while (token)
    {
        /* Allocate memory for the full path: "<token>/<command>\0" */
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
        {
            free(path); /* Free the duplicated PATH string if allocation fails */
            return (NULL);
        }

        /* Construct the full path string */
        sprintf(full_path, "%s/%s", token, command);

        /* Check if the file exists and is executable */
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path); /* Free the duplicated PATH string */
            return (full_path); /* Return the full path to the executable */
        }

        /* Free the allocated memory for the current full path and move to the next token */
        free(full_path);
        token = strtok(NULL, ":");
    }

    /* Free the duplicated PATH string before returning NULL (command not found) */
    free(path);
    return (NULL);
}
