#include "shell.h"

/**
 * go_exit - function to exit the shell
 * @data: Data relevant (stat and args)
 * Return: 0 on success.
 */

int go_exit(myshell *data) /*edited*/
{
	unsigned int stat;
	int digits, len, num;

	/*Check if an argument is provided to the exit command*/
	if (data->args[1] != NULL)
	{
		len = _strlen(data->args[1]);/*get length of the arg*/
		stat = _atoi(data->args[1]); /*Convert the argument to an unsigned int*/
		digits = _isdigit(data->args[1]); /*Check if the arg contains only digits*/
		/*Check if the converted value exceeds the maximum value for an int*/
		num = stat > (unsigned int)INT_MAX;

		if (len > 10 || num || !digits) /*check errors related to the argument*/
		{
			fetch_error(data, 2); /*if error, print err msg*/
			data->stat = 2;
			return (1);
		}
		/*Set exit status to the arg modulo 256*/
		data->stat = (stat % 256);
	}
	return (0);
}
