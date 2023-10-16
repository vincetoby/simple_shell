#include "shell.h"

/**
 * _strspn - gets the length of a prefix substring.
 * @str: string to check
 * @accept: substring of chars
 * Return: number of bytes in the initial segment of s
 * which consist only of bytes from accept
 */

unsigned int _strspn(char *str, char *accept)
{
	int i;
	int count = 0;
	int prev;

	while (*str)
	{
		prev = count;
		i = 0;
		while (accept[i] != '\0')
		{
			if (accept[i] == *str)
				count++;
			i++;
		}
		if (prev == count)
			break;
		str++;
	}
	return (count);
}

/**
 * _strchr -  a function that locates a char in a string.
 * @str: string to be checked
 * @c: character to check for
 * Return: a pointer to the first occurrence of the character c
 */

char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
	str++;
	}
	if (*str == c)
		return (str);
	else
		return ('\0');
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: 0, -1, 1 depending on the result
 */

int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] && str1[i] == str2[i])
	{
		i++;
	}
	if (str1[i] < str2[i])
		return (-1);
	else if (str1[i] > str2[i])
		return (1);
	else
		return (0);
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
 * _strcat - concatenates two strings.
 * @dest: destination to concatenate into
 * @src: source for concatenation
 * Return: concatenated string
 */

char *_strcat(char *dest, const char *src)
{
	int i;
	int dest_count = 0;
	int src_count = 0;

	for (i = 0; dest[i] != '\0'; i++)
		dest_count++; /*gets count of dest string*/
	for (i = 0; src[i] != '\0'; i++)
		src_count++; /*gets count of src string*/

	for (i = 0; i <= src_count; i++)
	{
		dest[dest_count + i] = src[i]; /*concatenation*/
	}
	return (dest); /*return concatenated dest*/
}
