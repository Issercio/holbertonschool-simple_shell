#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdarg.h>

extern char **environ; /* External variable for the environment */

/* Function prototypes */

/* Handles error messages and exits the program */
void handle_error(const char *error_message);

/* Executes the specified command */
void execute_command(char **argv);

/* Handles user input and prepares the command */
int handle_input(char **command, size_t *len);

/* Duplicates a string and returns the copy */
char *_strdup(const char *str);

/* Finds the executable path for a given command */
char *find_executable(char *command);

/* Compares two strings and returns the result */
int _strcmp(const char *s1, const char *s2);

/* Calculates and returns the length of a string */
int _strlen(const char *s);

/* Prints environment variables */
void print_env(void);

/* Searches for a command in the directories listed in PATH */
char *search_path(char *command, char *full_path);

/* Custom implementation of sprintf for formatted strings */
int _sprintf(char *str, const char *format, ...);

/* Copies the source string to the destination buffer */
char *_strcpy(char *dest, const char *src);

#endif /* SIMPLE_SHELL_H */
