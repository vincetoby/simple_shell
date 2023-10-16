#include "shell.h"

/**
 * swapper - swaps | and & for non-printed chars
 * @in: the input string
 * @bool: boolean value
 * Return: the swapped string
 */

char *swapper(char *in, int bool)
{
	int i = 0;

	if (bool == 0)
	{
		while (in[i]) /*iterate through string*/
		{ /*swap to non-printed chars*/
			if (in[i] == '|')
			{
				if (in[i + 1] == '|')
					i++; /*skip next char*/
				else
					in[i] = 16; /*ascii code (for non-printed chars)*/
			}
			if (in[i] == '&')
			{
				if (in[i + 1] == '&')
					i++; /*skip next char*/
				else
					in[i] = 12; /*ascii code (for non-printed chars)*/
			}
			i++;
		}
	}
	else /*when bool= 1*/
	{
		i = 0;
		while (in[i])
		{
			/*swap back to | and &*/
			in[i] = (in[i] == 16 ? '|' : in[i]);
			in[i] = (in[i] == 12 ? '&' : in[i]);
			i++;
		}
	}
	return (in);
}

/**
 * node_adder - Adds separators and command lines in the lists
 * @head_sep: the head of sep list
 * @head_line: the head of command lines list
 * @in: the input string
 * Return: void
 */

void node_adder(sep_t **head_sep, line_t **head_line, char *in)
{
	int i = 0;
	char *lane;

	in = swapper(in, 0);

	while (in[i])
	{
		if (in[i] == ';')
			add_node_sep(head_sep, in[i]);

		if (in[i] == '&' || in[i] == '|')
		{
			add_node_sep(head_sep, in[i]);
			i++;
		}
		i++;
	}

	lane = _strtok(in, ";&|"); /*tokenize with ";|&" as delimiters*/
	while (lane != NULL)
	{
		lane = swapper(lane, 1);
		add_node_line(head_line, lane);
		lane =  _strtok(NULL, ";&|"); /*tokenize*/
	}
}

/**
 * next_cmd - moves to the next command line stored
 * @separator: separator list
 * @line: command line list
 * @data: Data struct
 * Return: void
 */

void next_cmd(sep_t **separator, line_t **line, myshell *data)
{
	int loop_ctrl; /*loop control*/
	sep_t *sepl; /*pointer to seperator linked list*/
	line_t *linel; /*pointer to cmd line linked list*/

	loop_ctrl = 1; /*initialize with 1*/
	sepl = *separator; /*initialize sepl and linel*/
	linel = *line;

	/*Iterate through the separator list and line list*/
	while (sepl != NULL && loop_ctrl)
	{
		if (data->stat == 0)
		{ /*If the exit status is 0 (success)*/
			if (sepl->sep == '&' || sepl->sep == ';')
				loop_ctrl = 0;
			if (sepl->sep == '|')
				linel = linel->next, sepl = sepl->next;
		}
		else /*If the exit status isnt 0 (failure)*/
		{
			if (sepl->sep == '|' || sepl->sep == ';')
				loop_ctrl = 0;
			if (sepl->sep == '&')
				linel = linel->next, sepl = sepl->next;
		}
		if (sepl != NULL && !loop_ctrl)
			sepl = sepl->next; /*If there's another separator and*/
						/*loop_ctrl is not set, advance the separator pointer*/
	}
	/*update the original sep nd line*/
	*separator = sepl;
	*line = linel;
}

/**
 * splitter - Splits command with delim ;|&, and executes each command
 * @data: data struct
 * @in: input string
 * Return: 0 to exit, 1 to continue
 */

int splitter(myshell *data, char *in)
{

	sep_t *head_sep, *sep;
	line_t *head_line, *line;
	int loop_ctrl;

	head_sep = NULL;
	head_line = NULL;

	/*add nodes to separator and line lists based on the input string*/
	node_adder(&head_sep, &head_line, in);

	sep = head_sep;
	line = head_line;

	while (line != NULL)/*Loop through the lines in the line list*/
	{
		data->cmd_input = line->line;/*Set the current command input to the line*/
		/*Split the line into args and exec the command*/
		data->args = linesplitter(data->cmd_input);
		loop_ctrl = execute(data);
		free(data->args);

		if (loop_ctrl == 0)
			break;

		next_cmd(&sep, &line, data);/*Move to the next command*/

		if (line != NULL) /* Move to the next line if available*/
			line = line->next;
	}

	free_separator(&head_sep);
	free_line(&head_line);

	if (loop_ctrl == 0)
		return (0);
	return (1);
}

/**
 * linesplitter - Tokenizes the input
 * @in: the input string.
 * Return: char (tokenized/splitted strng)
 */

char **linesplitter(char *in)
{
	size_t size, i;
	char **toks, *tok;

	size = TOKEN_BUFFSIZE;
	toks = malloc(sizeof(char *) * (size));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	tok = _strtok(in, TOKEN_DELIM);
	toks[0] = tok;

	i = 1;
	while (tok != NULL)
	{
		if (i == size)
		{
			size = size + TOKEN_BUFFSIZE;
			toks = _reallocdp(toks, i, sizeof(char *) * size);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = _strtok(NULL, TOKEN_DELIM);
		toks[i] = tok;
		i++;
	}
	return (toks);
}
