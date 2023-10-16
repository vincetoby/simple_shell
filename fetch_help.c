#include "shell.h"

/**
 * help_msg - retrieves help messages for each builtin cmd
 * @data: Data structure, uses args and stat
 * Return: an integer
*/

int help_msg(myshell *data)
{
	int len;

	if (data->args[1] == 0)
	{
		help_main();
	}
	else if (_strcmp(data->args[1], "setenv") == 0)
		help_set();
	else if (_strcmp(data->args[1], "unsetenv") == 0)
		help_unset();
	else if (_strcmp(data->args[1], "env") == 0)
		help_env();
	else if (_strcmp(data->args[1], "help") == 0)
		get_help();
	else if (_strcmp(data->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(data->args[1], "alias") == 0)
		help_alias();
	else if (_strcmp(data->args[1], "cd") == 0)
		help_cd();
	else
	{
		len = _strlen(data->args[0]);
		write(STDERR_FILENO, data->args[0], len);
	}
	data->stat = 0;
	return (1);
}
