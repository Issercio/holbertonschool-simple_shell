#include "simple_shell.h"

/**
* _strcmp - Compares two strings.
* @s1: The first string.
* @s2: The second string.
*
* Return: 0 if strings are equal, non-zero otherwise.
*/
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2)) /* Compare each character */
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2); /* Return difference of first non-matching characters */
}

/**
* _strlen - Calculates the length of a string.
* @s: The string.
*
* Return: The length of the string.
*/
int _strlen(const char *s)
{
	int len = 0;

	while (s && *s++) /* Count the characters in the string */
		len++;
	return (len);
}
