#include "shell.h"

/**
 * catcd - concatenates the message
 * @data: data struct
 * @mssg: message in
 * @err: created error message
 * @str: str
 * Return: concatenated error message
 */

char *catcd(myshell *data, char *mssg, char *err, char *str)
{
	char *fg;

	_strcpy(err, data->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, mssg);
	if (data->args[1][0] == '-')
	{
		fg = malloc(3);
		fg[0] = '-';
		fg[1] = data->args[1][1];
		fg[2] = '\0';
		_strcat(err, fg);
		free(fg);
	}
	else
	{
		_strcat(err, data->args[1]);
	}
	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * cd_error - error message for cd
 * @data: data struct
 * Return: Error messages
 */

char *cd_error(myshell *data)
{
	int len, len1;
	char *err, *str, *mssg;

	str = _itoa(data->count);
	if (data->args[1][0] == '-')
	{
		mssg = ": Illegal option ";
		len1 = 2;
	}
	else
	{
		mssg = ": can't cd to ";
		len1 = _strlen(data->args[1]);
	}

	len = _strlen(data->argv[0]) + _strlen(data->args[0]);
	len = len + _strlen(str) + _strlen(mssg) + len1 + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == NULL)
	{
		free(str);
		return (NULL);
	}
	err = catcd(data, mssg, err, str);
	free(str);
	return (err);
}

/**
 * cmd_not_found - error mssg for command not found
 * @data: data struct
 * Return: Err msg
 */

char *cmd_not_found(myshell *data)
{
	int len;
	char *err, *str;

	/*Convert the execution count (data->count) to a string using itoa*/
	str = _itoa(data->count);
	len = _strlen(data->argv[0]) + _strlen(str);
	len = len + _strlen(data->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(err); /*free allocated mem*/
		free(str);
		return (NULL);
	}
	_strcpy(err, data->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0"); /*NULL terminate*/
	free(str);
	return (err);
}

/**
 * exit_error - generate error mssg for exit builtin
 * @data: data struct
 * Return: generated error mssg
 */

char *exit_error(myshell *data)
{
	int len;
	char *err;
	char *str;

	str = _itoa(data->count);/*convert count to string*/
	len = _strlen(data->argv[0]) + _strlen(str);
	len = len + _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(str);
		return (NULL);
	}
	_strcpy(err, data->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data->args[1]);
	_strcat(err, "\n\0");
	free(str);

	return (err);
}
