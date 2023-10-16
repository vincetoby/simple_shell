#include "shell.h"

/**
 * liner - gives the line var for _getline function
 * @line_p: stores the input string
 * @buff: The string called to line
 * @s_line: line size
 * @s_buff: buffer size
 * Return: void
 */

void liner(char **line_p, size_t *s_line, char *buff, size_t s_buff) /*edited*/
{
	if (*line_p == NULL)
	{
		if  (s_buff > BUFFERSIZE)
			*s_line = s_buff;

		else
			*s_line = BUFFERSIZE;
		*line_p = buff;
	}
	else if (*s_line < s_buff)
	{
		if (s_buff > BUFFERSIZE)
			*s_line = s_buff;
		else
			*s_line = BUFFERSIZE;
		*line_p = buff;
	}
	else
	{
		_strcpy(*line_p, buff);
		free(buff);
	}
}

/**
 * _getline - Reads input from stream
 * @line_p: stores the input
 * @s_line: size of line_p
 * @stream: stream to read from
 * Return: num of bytes
 */

ssize_t _getline(char **line_p, size_t *s_line, FILE *stream)
{
	char *buff, tp = 'z';
	int i;
	static ssize_t in;
	ssize_t bytes;

	if (in != 0)
		return (-1);
	else if (in == 0) /*Check if input is zero and flush the stream*/
		fflush(stream);
	in = 0; /*Reset in for a new read operation*/
	buff = malloc(sizeof(char) * BUFFERSIZE); /*allocate memory*/
	if (buff == NULL) /*check malloc failure*/
		return (-1);
	while (tp != '\n')/*read char from the stream until \n char*/
	{
		i = read(STDIN_FILENO, &tp, 1);

		if (i == 0 && in != 0)
		{
			in++;
			break;
		}
		if (i == -1 || (i == 0 && in == 0))
		{
			free(buff);
			return (-1); /*Read error or empty input*/
		}
		if (in >= BUFFERSIZE) /*realloc mem if in > than buffsize*/
			buff = _realloc(buff, in, in + 1);
		buff[in] = tp;
		in++;
	}
	buff[in] = '\0'; /*null terminate*/
	liner(line_p, s_line, buff, in);
	bytes = in;
	if (i != 0)
		in = 0;
	return (bytes);
}
