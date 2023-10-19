#include "shell.h"

/**
 * _strcat - concatenates two strings.
 * @dest: destination to concatenate into
 * @src: source for concatenation
 * Return: concatenated string
 */

char *_strcat(char *dest, const char *src)
{
	int indx;
	int j;

	for (indx = 0; dest[indx] != '\0'; indx++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[indx] = src[j];
		indx++;
	}

	dest[indx] = '\0';
	return (dest);
}
/**
 * _strcpy - copies the string into another
 * @dest: destination
 * @src: source
 * Return: copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i]; /*copy src into dest*/
		i++;
	}
	dest[i] = '\0'; /*null terminate*/
	return (dest); /* return destination string*/
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: 0, -1, 1 depending on the result
 */

int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - finds chars in string,
 * @str: the string.
 * @c: characters to look for
 * Return: the pointers to the first occurrence of the characters c.
 */

char *_strchr(char *str, char c)
{
	unsigned int i = 0;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		if (*(str + i) == c)
			return (str + i);
	}
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring.
 * @str: string to check
 * @accept: substring of chars
 * Return: number of bytes in the initial segment of s
 * which consist only of bytes from accept
 */

int _strspn(char *str, char *accept)
{
	int indx, j, bool;

	for (indx = 0; *(str + indx) != '\0'; indx++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(str + indx) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (indx);
}
