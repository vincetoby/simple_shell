#include "shell.h"

/**
 * char_rep_count - counts the repeat of a char
 * @in: input string
 * @indx: index
 * Return: indx
 */

int char_rep_count(char *in, int indx)
{
	if (*(in - 1) == *in)
		return (char_rep_count(in - 1, indx + 1));

	return (indx);
}

/**
 * find_errsyn - finds the syntax errors
 * @in: input string
 * @indx: index
 * @charr: the last read character
 * Return: index of error. 0 when there are no
 * errors
 */

int find_errsyn(char *in, int indx, char charr)
{
	int c; /*the count*/

	c = 0;
	if (*in == '\0')
		return (0);
	if (*in == '\t' || *in == ' ')
		return (find_errsyn(in + 1, indx + 1, charr));
	if (*in == '|')
	{
		if (charr == '&' || charr == ';')
			return (indx);
		if (charr == '|')
		{
			c = char_rep_count(in, 0);
			if (c > 1 || c == 0)
				return (indx);
		}
	}
	if (*in == ';')
		if (charr == '&' || charr == '|' || charr == ';')
			return (indx);
	if (*in == '&')
	{
		if (charr == ';' || charr == '|')
			return (indx);

		if (charr == '&')
		{
			c = char_rep_count(in, 0);
			if (c == 0 || c > 1)
				return (indx);
		}
	}
	return (find_errsyn(in + 1, indx + 1, *in));
}

/**
 * indx1 - Fetches the index of the first char
 * @in: the input string
 * @indx: the index
 * Return: 0, -1  depending on outcome
 */

int indx1(char *in, int *indx)
{

	for (*indx = 0; in[*indx]; *indx += 1)
	{
		if (in[*indx] == '\t' || in[*indx] == ' ')
			continue;

		if (in[*indx] == '|' || in[*indx] == ';' || in[*indx] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * synerr_print - Prints syntax error message
 * @data: my shell's data structure
 * @in: the input string
 * @indx: index of the error
 * @bool: boolean value
 * Return: void
 */

void synerr_print(myshell *data, char *in, int indx, int bool)
{
	char *err_msg, *c, *mssg, *mssg2, *mssg3;
	int len;

	if (in[indx] == '|')
		mssg = (in[indx + 1] == '|' ? "||" : "|");
	if (in[indx] == ';')
	{
		if (bool != 0)
			mssg = (in[indx - 1] == ';' ? ";;" : ";");
		else
			mssg = (in[indx + 1] == ';' ? ";;" : ";");
	}
	if (in[indx] == '&')
		mssg = (in[indx + 1] == '&' ? "&&" : "&");

	mssg2 = ": Syntax error: \"";
	mssg3 = "\" unexpected\n";
	c = _itoa(data->count);
	len = _strlen(data->argv[0]) + _strlen(c);
	len = len + _strlen(mssg) + _strlen(mssg2) + _strlen(mssg3) + 2;

	err_msg = malloc(sizeof(char) * (len + 1));
	if (err_msg == 0)
	{
		free(c);
		return;
	}
	_strcpy(err_msg, data->argv[0]);
	_strcat(err_msg, ": ");
	_strcat(err_msg, c);
	_strcat(err_msg, mssg2);
	_strcat(err_msg, mssg);
	_strcat(err_msg, mssg3);
	_strcat(err_msg, "\0"); /*null terminate string*/

	write(STDERR_FILENO, err_msg, len);
	free(err_msg);
	free(c);
}

/**
 * syntax_err - main func to find and print error in syntax
 * @data: myshell's data structure
 * @in: the input string
 * Return: 1 if there is an error. 0 in other case
 */

int syntax_err(myshell *data, char *in)
{
	int start = 0, char1 = 0, indx = 0;

	char1 = indx1(in, &start);
	if (char1 == -1)
	{
		synerr_print(data, in, start, 0);
		return (1);
	}

	indx = find_errsyn(in + start, 0, *(in + start));
	if (indx != 0)
	{
		synerr_print(data, in, start + indx, 1);
		return (1);
	}
	return (0);
}
