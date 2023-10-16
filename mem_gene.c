#include "shell.h"

/**
 * _reallocdp - reallocates memory for double pointers.
 * @str: double pointers to string
 * @prev_size: prev allocated size of memory to str
 * @size: new size to be allocated
 * Return: char (neW_str, str or NULL)
 */

char **_reallocdp(char **str, unsigned int prev_size, unsigned int size)
{
	char **new_str;
	unsigned int i;

	if (str == NULL)
		return (malloc(sizeof(char *) * size));

	if (size == prev_size)
		return (str);

	new_str = malloc(sizeof(char *) * size);
	if (new_str == NULL)
		return (NULL);

	i = 0;
	while (i < prev_size)
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

/**
 * _memcpy - copies memory area.
 * @dest: destination
 * @src: source
 * @num: bytes to be copied
 * Return: void
 */

void _memcpy(void *dest, const void *src, unsigned int num)
{
	char *src_dup = (char *)src;
	char *dest_dup = (char *)dest;
	unsigned int i;

	i = 0;
	while (i < num)
	{
		dest_dup[i] = src_dup[i];
		i++;
	}
}

/**
 * _realloc - reallocates memory blocks.
 * @prev_str: name of previously allocated str
 * @prev_size: mem size previously allocated
 * @size: new size to allocated
 * Return: void (new_str)
 */

void *_realloc(void *prev_str, unsigned int prev_size, unsigned int size)
{
	void *new_str;

	if (prev_str == NULL)
		return (malloc(size));

	if (size == 0)
	{
		free(prev_str);
		return (NULL);
	}
	if (size == prev_size)
		return (prev_str);

	new_str = malloc(size);
	if (new_str == NULL)
		return (NULL);

	if (size < prev_size)
		_memcpy(new_str, prev_str, size);
	else
		_memcpy(new_str, prev_str, prev_size);

	free(prev_str);
	return (new_str);
}
