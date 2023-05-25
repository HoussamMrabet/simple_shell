#include "shell.h"

/**
 * is_interactive - returns true if shell is is_interactive mode
 * @info: struct address
 *
 * Return: 1 if is_interactive mode, 0 otherwise
*/
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_character_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
*/
int is_character_delimiter(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return 1;
		delim++;
	}
	return 0;
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
*/
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * convert_to_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
*/
int convert_to_integer(char *s)
{
	int sign = 1;
	unsigned int result = 0;
	int flag = 0;
	int output = 0;

	for (int i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return output;
}
