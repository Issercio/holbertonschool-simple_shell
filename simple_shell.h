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

extern char **environ;

/* Function prototypes */
void handle_error(const char *error_message);
void execute_command(char **argv);
int handle_input(char **command, size_t *len);
char *_strdup(const char *str);
char *find_executable(char *command);
int _strcmp(const char *s1, const char *s2);
int _strlen(const char *s);
void print_env(void);
char *search_path(char *command, char *full_path);
int _sprintf(char *str, const char *format, ...);
char *_strcpy(char *dest, const char *src);

#endif /* SIMPLE_SHELL_H */
