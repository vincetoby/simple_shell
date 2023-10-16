#include "shell.h"

/**
 * rev_string - reverses a string.
 * @string: the string to be reversed
 * Return: void.
 */

void rev_string(char *string)
{
	int i, counter = 0;
	char j;

	i = 0;
	while (string[i] != '\0')
	{
		counter++;
		i++;
	}
	for (i = 0; i < counter / 2; i++)
	{
		j = string[i];
		string[i] = string[counter - 1 - i];
		string[counter - i - 1] = j;
	}
}

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
	if (buf == NULL)
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
	while (numb1 > 0)
	{
		*(buf + len) = (numb1 % 10) + '0';
		numb1 = numb1 / 10;
		len--;
	}
	return (buf);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to str to convert
 * Return: converted string
 */

int _atoi(char *s)
{
	int indx = 0, min = 1, check = 0;
	unsigned int ni = 0;

	while (s[indx])
	{
		if (s[indx] == 45)
		{
			min = min * -1;
		}
		while (s[indx] >= 48 && s[indx] <= 57)
		{
			check = 1;
			ni = (ni * 10) + (s[indx] - '0');
			indx++;
		}
		if (check == 1)
		{
			break;
		}
		indx++;
	}
	ni = ni * min;
	return (ni);
}
