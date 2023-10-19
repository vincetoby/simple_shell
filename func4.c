#include "shell.h"

/**
 * fetch_length - fetches length of  numbers
 * @num: number
 * Return: Length of num
 */

int fetch_length(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1; /*assigns a negative value*/
	}
	else
		num1 = num; /*copies the positive num*/
	while (num1 > 9)
	{
		len++;
		num1 = num1 / 10;
	}

	return (len);
}

/**
 * _itoa - converts int to str
 * @numb: number to convert
 * Return: converted Strings.
 */

char *_itoa(int numb)
{
	unsigned int numb1;
	int len;
	char *buf;

	len = fetch_length(numb);
	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);

	*(buf + len) = '\0';
	if (numb < 0)
	{
		numb1 = numb * -1;
		buf[0] = '-';
	}
	else
		numb1 = numb;
	len--;
	do {
		*(buf + len) = (numb1 % 10) + '0';
		numb1 = numb1 / 10;
		len--;
	}
	while (numb1 > 0)
		;
	return (buf);
}

/**
 * _atoi - converts strings to an integer.
 * @s: input strings.
 * Return: integers.
 */

int _atoi(char *s)
{
	unsigned int i, c = 0, size = 0, pi = 0, p = 1, m = 1;

	for (c = 0; *(s + c) != '\0'; c++)
	{
		if (size > 0 && (*(s + c) < '0' || *(s + c) > '9'))
			break;

		if (*(s + c) == '-')
			p *= -1;

		if ((*(s + c) >= '0') && (*(s + c) <= '9'))
		{
			if (size > 0)
				m = m * 10;
			size++;
		}
	}

	for (i = c - size; i < c; i++)
	{
		pi = pi + ((*(s + i) - 48) * m);
		m = m / 10;
	}
	return (pi * p);
}
