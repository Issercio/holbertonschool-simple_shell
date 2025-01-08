#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>

/* External environment variable */
extern char **environ;

/* Function prototypes */
int handle_command(char *command);
void print_env(void);
char *search_path(char *command, char *full_path);
void handle_error(const char *error_message);

/* Utility functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _sprintf(char *str, const char *format, ...);

#endif /* SHELL_H */
