#include "simple_shell.h"

/**
* _strdup - Duplicates a string.
* @str: The string to duplicate.
*
* Return: A pointer to the duplicated string, or NULL on failure.
*/
char *_strdup(const char *str)
{
	char *dup;

	int len = _strlen(str);

	dup = malloc(len + 1); /* Allocate memory for the duplicated string */
	if (!dup) /* Check memory allocation failure */
		return (NULL);

	_strcpy(dup, str); /* Copy the string */
	return (dup);
}

/**
* _strcpy - Copies a string.
* @dest: The destination for the copy.
* @src: The source string to copy.
*
* Return: A pointer to the destination (dest).
*/
char *_strcpy(char *dest, const char *src)
{
	char *d = dest;

	while
	((*d++ = *src++));
	return (dest);
}

/**
* _sprintf - Formats and stores a string.
* @str: The destination buffer.
* @format: The format string.
* @...: Additional arguments.
*
* Return: The number of characters written.
*/
int _sprintf(char *str, const char *format, ...)
{
	va_list args;
	int count;

	va_start(args, format);
	count = vsnprintf(str, 1024, format, args);  /* Use a safe buffer size */
	va_end(args);

	return (count);
}
