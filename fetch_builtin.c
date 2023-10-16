#include "shell.h"

/**
 * fetch_builtin - for pairing the command in the arg
 * @cmnd: command from user
 * Return: returns the funct pointer of builtin cmd
 */

int (*fetch_builtin(char *cmnd))(myshell *)
{
	shell_builtin build[] = {
		{ "setenv", cmp_setenv },
		{ "unsetenv", _unsetenv },
		{ "env",  _printenv },
		{ "cd", cd },
		{ "help", help_msg },
		{ "exit", go_exit },
		{ NULL, NULL }
	};

	int index = 0;

	for (; build[index].string; index++)
	{
		if (_strcmp(build[index].string, cmnd) == 0)
			break;
	}
	return (build[index].d);
}
