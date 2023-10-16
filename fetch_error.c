#include "shell.h"

/**
 * fetch_error - handles errors based on the exit status value
 * @data: Data structure containing needed args
 * @err_value: error value
 * Return: err_value
 */

int fetch_error(myshell *data, int err_value)
{
	char *err = NULL;

	if (err_value == -1)
		err = env_error(data);
	else if (err_value == 126)
		err = path_error(data);
	else if (err_value == 127)
		err = cmd_not_found(data);
	else if (err_value == 2)
	{
		if (_strcmp("exit", data->args[0]) == 0)
			err = exit_error(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			err = cd_error(data);
	}
	if (err != NULL)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}
	data->stat = err_value;
	return (err_value);
}
