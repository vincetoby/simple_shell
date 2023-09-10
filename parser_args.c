#include "shell.h"

/**
 * parser - tokenize inputs into command args
 * @std_input: users input
 * @argv: pointer to a pointer to chars, stores the commands
 * and its arguments after parsing
 * @argc: pointer to int, number of args
 * Return: void
 */

void parser(char *std_input, char **argv, int *argc)
{
	char *token = strtok(std_input, " ");

	if (token == NULL)/* if no input, nothing to return*/
		return;
	argv[0] = token;
	*argc = 1;

	for (; *argc < 10; (*argc)++)
	{
		token = strtok(NULL, " ");
		if (token == NULL)/* in the absence of more tokens to parse*/
			break;
		argv[*argc] = token;
	}
	argv[*argc] = NULL; /*null terminate args*/
}
