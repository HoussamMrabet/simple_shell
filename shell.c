#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
*/

int main(int argc, char **argv)
{
	info_t inf[] = {INFO_INIT};
	int folder = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(folder)
		: "r"(folder));

	if (argc == 2)
	{
		folder = open(argv[1], O_RDONLY);
		if (folder == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = folder;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, argv);
	return (EXIT_SUCCESS);
}
