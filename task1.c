#include "shell.h"

/**
 * builtins - Checks and executes the builtins
 * @info: Info about the shell
 * @arguments: The Commands and arguments
 * Return: _TRUE if not return _FALSE
 */

int builtins(general_t *info, char **arguments)
{
	int st;

	st = check_builtin(info, arguments);
	if (st == _FALSE)
	{
		return (_FALSE);
	}
	return (_TRUE);
}

/**
 * bin_env - Implementation for
 * @info: General info about the shell
 * @command: Command
 */

void bin_env(general_t *info, char **command)
{
	(void) info;
	(void) command;

	get_full_env();
}

/**
 * get_full_env - Gets all the environments
 * Return: void
 */

void get_full_env(void)
{
	char **t;
	int x;

	for (x = 0, t = environ; t[x] != NULL; x++)
	{
		print(t[x]);
		_putchar('\n');
	}
}

/**
 * is_current_path - Checks the order of the path
 * @path: PATH to check
 * @info: General information about the shell
 */

void is_current_path(char *path, general_t *info)
{
	info->is_current_path = _FALSE;

	if (path == NULL)
	{
		return;
	}
	if (path[0] == ':')
	{
		info->is_current_path = _TRUE;
	}
}
