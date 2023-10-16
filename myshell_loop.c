#include "shell.h"

/**
 * comment_del - function that deletes comments from the input
 * @str: the input string
 * Return: str
 */

char *comment_del(char *str)
{
	int i, stop;

	stop = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			if (i == 0)
			{
				free(str);
				return (NULL);
			}

			if (str[i - 1] == '\t' || str[i - 1] == ' ' || str[i - 1]
			    == ';')
				stop = i;
		}
		i++;
	}
	if (stop != 0)
	{
		str = _realloc(str, i, stop + 1);
		str[stop] = '\0';
	}
	return (str);
}

/**
 * myshell_loop -  Loop for shell
 * @data: struct containng relevant data
 * Return: void
 */

void myshell_loop(myshell *data)
{
	int start = 1, i_eof;
	char *input;

	while (start == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = _readline(&i_eof);

		if (i_eof == -1)
		{
			start = 0;
			free(input);
		}
		else
		{
			input = comment_del(input);
			if (input == NULL)
				continue;

			if (syntax_err(data, input) == 1)
			{
				data->stat = 2;
				free(input);
				continue;
			}
			input = var_replace(input, data);
			start = splitter(data, input);
			data->count =  data->count + 1;
			free(input);
		}

	}
}
