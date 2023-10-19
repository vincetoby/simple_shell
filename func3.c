#include "shell.h"
/**
 * rev_string - reverses a string.
 * @string: the string to be reversed
 * Return: void.
 */

void rev_string(char *string)
{
	int c = 0, i, j;
	char *str_cpy, tempo;

	for (c = 0; c >= 0; c++)
	{
		if (string[c] == '\0')
			break;
	}
	str_cpy = string;

	for (i = 0; i < (c - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			tempo = *(str_cpy + j);
			*(str_cpy + j) = *(str_cpy + (j - 1));
			*(str_cpy + (j - 1)) = tempo;
		}
	}
}
