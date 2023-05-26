#include "shell.h"

/**
 * _myexit - A function to exits the shell
 * @inf: Structure
 * Return: exits with a given exit status
*/
int _myexit(info_t *inf)
{
	int checkExit;

	if (inf->argv[1]) /* If there is an exit arguement */
	{
		checkExit = _erratoi(inf->argv[1]);
		if (checkExit == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;

	return (-2);
}

/**
 * _mycd - A fucntion that changes the current directory
 * @inf: Structure
 * Return: Always returns 0
*/
int _mycd(info_t *inf)
{
	char *str, *directory, buffer[1024];
	int dirRet;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		directory = _getenv(inf, "HOME=");
		if (!directory)
			dirRet = chdir((directory = _getenv(inf, "PWD=")) ? directory : "/");
		else
			dirRet = chdir(directory);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		dirRet = chdir((directory = _getenv(inf, "OLDPWD=")) ? directory : "/");
	}
	else
		dirRet = chdir(inf->argv[1]);
	if (dirRet == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * _myhelp - A fucntion for help
 * @inf: Structure
 * Return: Always 0
*/
int _myhelp(info_t *inf)
{
	char **argArray;

	argArray = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray);

	return (0);
}

