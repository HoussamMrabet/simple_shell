#include "shell.h"

/**
 * _myenv - A function to print the current environment
 * @inf: Structure
 * Return: Always returns 0
*/
int _myenv(info_t *inf)
{
	print_list_str(inf->env);

	return (0);
}

/**
 * _getenv - A function to get the value of an env variable
 * @inf: Structure
 * @name: Const charactere
 * Return: Returns the value
*/
char *_getenv(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}

	return (NULL);
}

/**
 * _mysetenv - Initialize or modify an environment variable
 * @inf: Structure
 * Return: Always returns 0
*/
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @inf: Structure
 * Return: Always returns 0
*/
int _myunsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @inf: Structure
 * Return: Always returns 0
*/
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t size;

	for (size = 0; environ[size]; size++)
		add_node_end(&node, environ[size], 0);
	inf->env = node;

	return (0);
}

