#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int x, y, a, b, nmw = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			nmw++;

	if (nmw == 0)
		return (NULL);
	c = malloc((1 + nmw) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < nmw; y++)
	{
		while (is_delim(str[x], d))
			x++;
		a = 0;
		while (!is_delim(str[x + a], d) && str[x + a])
			a++;
		c[y] = malloc((a + 1) * sizeof(char));
		if (!c[y])
		{
			for (a = 0; a < y; a++)
				free(c[a]);
			free(c);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			c[y][b] = str[x++];
		c[y][b] = 0;
	}
	c[y] = NULL;
	return (c);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int x, y, a, b, nmw = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			nmw++;
	if (nmw == 0)
		return (NULL);
	c = malloc((1 + nmw) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < nmw; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		a = 0;
		while (str[x + a] != d && str[x + a] && str[x + a] != d)
			a++;
		s[y] = malloc((a + 1) * sizeof(char));
		if (!c[y])
		{
			for (a = 0; a < y; a++)
				free(c[a]);
			free(c);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			c[y][b] = str[x++];
		c[y][b] = 0;
	}
	c[y] = NULL;
	return (c);
}
