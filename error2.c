#include "shell.h"

/**
 * env_error - error mssg for the env builtin
 * @data: myshell data struct
 * Return: the created error msg
 */

char *env_error(myshell *data)
{
	int len;
	char *err, *str, *mssg;

	str = _itoa(data->count);
	mssg = ": Unable to add/remove from environment\n";
	len = _strlen(data->argv[0]) + _strlen(str);
	len = len + _strlen(data->args[0]) + _strlen(mssg) + 4;
	err = malloc(sizeof(char) * (len + 1)); /*allocate memory for err mssg*/
	if (err == NULL) /*check malloc failure*/
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, data->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, mssg);
	_strcat(err, "\0"); /*null terminate the string */
	free(str);

	return (err);
}

/**
 * path_error - error mssg for path.
 * @data: var containing relevant data needed
 * Return: The err mssg
 */

char *path_error(myshell *data)
{
	int len;
	char *str, *err;

	str = _itoa(data->count);
	len = _strlen(data->argv[0]) + _strlen(str);
	len = len + _strlen(data->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL) /*check malloc failure*/
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, data->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0"); /*null terminate the string*/
	free(str); /*free str*/
	return (err); /*return err message*/
}
