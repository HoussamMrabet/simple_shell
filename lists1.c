#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t size1 = 0;

	while (h)
	{
		h = h->next;
		size1++;
	}
	return (size1);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t size1 = list_len(head), size2;
	char **sts;
	char *strin;

	if (!head || !size1)
		return (NULL);
	sts = malloc(sizeof(char *) * (size1 + 1));
	if (!sts)
		return (NULL);
	for (size1 = 0; nd; nd = nd->next, size1++)
	{
		strin = malloc(_strlen(nd->strin) + 1);
		if (!strin)
		{
			for (size2 = 0; size2 < size1; size2++)
				free(sts[size2]);
			free(sts);
			return (NULL);
		}

		strin = _strcpy(strin, nd->strin);
		sts[size1] = strin;
	}
	sts[size1] = NULL;
	return (sts);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t size1 = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		size1++;
	}
	return (size1);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ch = NULL;

	while (node)
	{
		ch = starts_with(node->str, prefix);
		if (ch && ((c == -1) || (*ch == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t size1 = 0;

	while (head)
	{
		if (head == node)
			return (size1);
		head = head->next;
		size1++;
	}
	return (-1);
}
