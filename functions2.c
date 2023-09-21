#include "shell.h"

/**
 * check_builtin - Checks if the actual command is a builtin_t
 * or not
 * @info: General info about the shell
 * @argus: Arguments for the command
 * Return: _TRUE if not _FALSE
 */

int check_builtin(general_t *info, char **argus)
{
	int x, size;
	builtin_t builtins[] = {
		{"exit", bin_exit},
		{"env", bin_env}
	};

	size = sizeof(builtins) / sizeof(builtins[0]);
	for (x = 0; x < size; x++)
	{
		if (_strcmp(info->command, builtins[x].command) == 0)
		{
			builtins[x].func(info, argus);
			return (_TRUE);
		}
	}

	return (_FALSE);
}

/**
 * analyze - Analyzes the arguments
 * @argus: The Commands and arguments to execute
 * @info: General info about the shell
 * @yes: Line readed
 */

void analyze(char **argus, general_t *info, char *yes)
{
	char *cmd;
	int status;

	if (*argus == NULL || argus == NULL)
		return;
	cmd = argus[0];
	info->command = cmd;
	if (check_builtin(info, argus) == _TRUE)
		return;
	status = is_file(cmd);
	if (status == NON_PERMISSIONS)
	{
		info->status_code = 126;
		info->error_code = _CODE_EACCES;
		error(info);
		return;
	}
	if (status == 1)
	{
		execute(cmd, argus, info, yes);
		return;
	}
	if (current_directory(cmd, argus, yes, info) == _TRUE)
		return;
	info->value_path = which(cmd, info);
	if (info->value_path != NULL)
	{
		execute(info->value_path, argus, info, yes);
		free_memory_p((void *) info->value_path);
		return;
	}
	info->status_code = 127;
	info->error_code = _CODE_CMD_NOT_EXISTS;
	error(info);
}

/**
 * split_words - Splits a line ints
 * @line: Line to split
 * @sep: Delimiplit to the words
 * Return: Sets of words
 */

char **split_words(char *line, const char *sep)
{
	char **words, **tmp, *token;
	size_t new_size, old_size;

	old_size = sizeof(char *);
	words = malloc(old_size);
	if (words != NULL)
	{
		new_size = 1;
		token = strtok(line, sep);
		while (token)
		{
			if (token[0] == '#')
				break;
			tmp = _realloc(words, old_size, (new_size + 1) * sizeof(char *));
			old_size = (new_size + 1) * sizeof(char *);
			if (tmp == NULL)
				break;

			words = tmp;
			++new_size;

			words[new_size - 2] = malloc(_strlen(token) + 1);
			if (words == NULL)
			{
				free(tmp);
				free(words);
			}

			if (words[new_size - 2] != NULL)
				_strcpy(words[new_size - 2], token);

			token = strtok(NULL, sep);

			tmp = NULL;
		}

		words[new_size - 1] = NULL;
	}

	return (words);
}
