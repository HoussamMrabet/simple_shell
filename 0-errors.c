#include "shell.h"

/**
 * _eputs - Prints an input string
 * @str: String
 * Return: void function
*/
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes the character ch to stderr
 * @ch: Character
 * Return: Returns 1 if success, otherwise returns -1
*/
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;

	return (1);
}

/**
 * _putfd - writes the character ch to given folder
 * @ch: Character
 * @folder: Integer
 * Return: Returns 1 if success, otherwise returns -1
*/
int _putfd(char ch, int folder)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(folder, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;

	return (1);
}

/**
 * _putsfd - Prints an input string
 * @str: String
 * @folder: Integer
 * Return: Returns the number of chars put
*/
int _putsfd(char *str, int folder)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, folder);
	}

	return (i);
}

