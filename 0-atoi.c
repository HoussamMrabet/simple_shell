#include "shell.h"

/**
 * interactive - A function to check interactive mode
 * @inf: Pointer of type info_t
 * Return: Returns Returns 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - A function to checks delimeter
 * @ch: Char
 * @del: String
 * Return: Returns Returns 1 if true, 0 if false
*/
int is_delim(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);

	return (0);
}

/**
 * _isalpha - A function to checks for alphabetic character
 * @ch: The character to input
 * Return: Returns 1 if ch is alphabetic, 0 otherwise
*/
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - A function that converts a string to an integer
 * @str: String
 * Return: Returns 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, val;
	unsigned int res = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		val = -res;
	else
		val = res;

	return (val);
}

