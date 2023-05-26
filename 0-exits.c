#include "shell.h"

/**
 * _strncpy - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
*/
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
*/
char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';

	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @ch: the character to look for
 * Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char ch)
{
	do {
		if (*s == ch)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
