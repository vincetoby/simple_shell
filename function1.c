#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src
 * @dest: destination
 * @src: source
 * Return: destination
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings.
 * @dest: destination
 * @src: source.
 * Return: destination
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int count1 = 0;
	int count2 = 0;

	for (i = 0; dest[i] != '\0'; i++)
		count1++;
	for (i = 0; src[i] != '\0'; i++)
		count2++;

	for (i = 0; i <= count2; i++)
	{
		dest[count1 + i] = src[i];
	}
	return (dest);
}

/**
  * _strlen - this returns the length of a string
  * @s: String to count
  * Return: String length (count)
  */

int _strlen(char *s)
{
	int i, count = 0;

	for (i = 0; s[i] != '\0'; i++)
		count++;
	return (count);
}
/**
 * _strdup -  returns a pointer to a newly allocated space in memory
 * which contains a copy of the string given as a parameter.
 * @str: string to copy
 * Return: pointer to a string, or NULL
 * if insufficient memory, OR str = NULL
 */

char *_strdup(char *str)
{
	char *str2;
	int i, count;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		count++;
	}
	str2 = malloc(sizeof(char) * (count + 1));
	if (str2 == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		str2[i] = str[i];
	}
	str2[i] = '\0'; /*add a null byte to end of string*/
	return (str2);
}
