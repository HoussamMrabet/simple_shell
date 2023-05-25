#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *bf, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	bf = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_strcpy(bf, dr);
	_strcat(bf, "/");
	_strcat(bf, HIST_FILE);
	return (bf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *fn = get_history_file(info);
	list_t *nd = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int x, last = 0, lct = 0;
	ssize_t fd, rn, fs = 0;
	struct stat st;
	char *bf = NULL, *fn = get_history_file(info);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	bf = malloc(sizeof(char) * (fs + 1));
	if (!bf)
		return (0);
	rn = read(fd, bf, fs);
	bf[fs] = 0;
	if (rn <= 0)
		return (free(bf), 0);
	close(fd);
	for (x = 0; x < fs; x++)
		if (bf[x] == '\n')
		{
			bf[x] = 0;
			build_history_list(info, bf + last, lct++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(info, bf + last, lct++);
	free(bf);
	info->histcount = lct;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;
	add_node_end(&nd, buf, linecount);

	if (!info->history)
		info->history = nd;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int x = 0;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (info->histcount = x);
}
