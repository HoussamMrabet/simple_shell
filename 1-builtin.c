#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *	with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
*/
int _myhistory(info_t *inf)
{
	print_list(inf->history);

	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *inf, char *str)
{
	char *p, ch;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	ch = *p;
	*p = 0;
	ret = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*p = ch;

	return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *inf, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, str));

	unset_alias(inf, str);

	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
*/
int _myalias(info_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}

