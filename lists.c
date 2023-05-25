#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nh;

	if (!head)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	_memset((void *)nh, 0, sizeof(list_t));
	nh->num = num;
	if (str)
	{
		nh->str = _strdup(str);
		if (!nh->str)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *head;
	*head = nh;
	return (nh);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *nd;

	if (!head)
		return (NULL);

	nd = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t size1 = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		size1++;
	}
	return (size1);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nd, *prevNode;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *head;
	while (nd)
	{
		if (x == index)
		{
			prevNode->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		x++;
		prevNode = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nd, *nextNode, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	nd = hd;
	while (nd)
	{
		nextNode = nd->next;
		free(nd->str);
		free(nd);
		nd = nextNode;
	}
	*head_ptr = NULL;
}
