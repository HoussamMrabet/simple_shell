#include "shell.h"

/**
 * get_history_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
*/
char *get_history_file(info_t *inf)
{
	char *buffer, *directory;

	directory = _getenv(inf, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
*/
int write_history(info_t *inf)
{
	ssize_t folder;
	char *filename = get_history_file(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	folder = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (folder == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, folder);
		_putfd('\n', folder);
	}
	_putfd(BUF_FLUSH, folder);
	close(folder);

	return (1);
}

/**
 * read_history - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
*/
int read_history(info_t *inf)
{
	int i, last = 0, lineCount = 0;
	ssize_t folder, readLength, folderSize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	folder = open(filename, O_RDONLY);
	free(filename);
	if (folder == -1)
		return (0);
	if (!fstat(folder, &st))
		folderSize = st.st_size;
	if (folderSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (folderSize + 1));
	if (!buffer)
		return (0);
	readLength = read(folder, buffer, folderSize);
	buffer[folderSize] = 0;
	if (readLength <= 0)
		return (free(buffer), 0);
	close(folder);
	for (i = 0; i < folderSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(inf, buffer + last, lineCount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(inf, buffer + last, lineCount++);
	free(buffer);
	inf->histcount = lineCount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);

	return (inf->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lineCount: the history lineCount, histcount
 *
 * Return: Always 0
*/
int build_history_list(info_t *inf, char *buffer, int lineCount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buffer, lineCount);

	if (!inf->history)
		inf->history = node;

	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
*/
int renumber_history(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (inf->histcount = i);
}
