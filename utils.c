#include "simple_shell.h"

/**
 * _strlen - Computes the length of a string.
 * @s: The string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int len = 0;

	while (s && *s++)
		len++;
	return (len);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if equal, non-zero otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcpy - Copies a string to a destination buffer.
 * @dest: Destination buffer.
 * @src: Source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	char *d = dest;

	while ((*d++ = *src++))
		;
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(char *str)
{
	char *dup;
	int len = _strlen(str);

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	_strcpy(dup, str);
	return (dup);
}

/**
 * _sprintf - Formats and stores a string.
 * @str: Destination buffer.
 * @format: Format string.
 * @...: Additional arguments.
 *
 * Return: Number of characters written.
 */
int _sprintf(char *str, const char *format, ...)
{
	va_list args;
	int count;

	va_start(args, format);
	count = vsprintf(str, format, args);
	va_end(args);

	return (count);
}
