#include "shell.h"

/**
 * _strdup - duplicates a string
 * @string: pointer to string
 * Return: the duplicated string
 */

char *_strdup(const char *string)
{
	char *dup;
	size_t str_len;

	str_len = _strlen(string); /*get string length*/

	dup = malloc(sizeof(char) * (str_len + 1)); /*alloc memory*/
	if (dup == NULL) /*check for malloc failure*/
	{
		return (NULL);
	}

	_memcpy(dup, string, str_len + 1); /*copy str into dup*/
	return (dup); /*return duplicate*/
}


/**
 * _strlen - gets lenght of string
 * @string: string
 * Return: Always 0.
 */

int _strlen(const char *string)
{
	int i;

	for (i = 0; string[i] != 0; i++) /*iterate tru string*/
	{
	}
	return (i); /*return length*/
}
/**
 * char_check - compares chars of a str
 * @s: input strings.
 * @c: chars to check (delimiters)
 * Return: 1 if the chars match, 0 otherwise.
 */

int char_check(char s[], const char *c)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; c[j]; j++)
		{
			if (s[i] == c[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
/**
 * _strtok - tokenizes strings(splitting str to dif parts)
 * @string: input strings.
 * @delimiter: delimiters used to show when to break str
 * Return: tokenized string
 */

char *_strtok(char string[], const char *delimiter)
{
	unsigned int i, bool;
	static char *tok, *eos;
	char *sos;

	if (string != NULL)
	{
		if (char_check(string, delimiter))
			return (NULL);
		tok = string; /*Store string's first address*/
		i = _strlen(string);
		eos = &string[i]; /*Store string's last address*/
	}
	sos = tok; /*sos/eos means start/end of string*/
	if (sos == eos) /*check if end of string has been reached*/
		return (NULL);
	for (bool = 0; *tok; tok++)
	{	/*Breaking loop when the finding the next token*/
		if (tok != sos)
		{
			if (*tok && *(tok - 1) == '\0')
				break;
		}
		for (i = 0; delimiter[i]; i++)/*swapping delims for null chars*/
		{
			if (*tok == delimiter[i])
			{
				*tok = '\0';
				if (tok == sos)
					sos++;
				break;
			}
		}
		if (bool == 0 && *tok) /*indicates that Str != Delimiter*/
			bool = 1;
	}
	if (bool == 0) /*indicates that Str == Delimiter*/
		return (NULL);
	return (sos);
}
/**
 * _isdigit - checks if string is a number
 * @str: input string
 * Return: 1 if number. 0 otherwise
 */

int _isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}
