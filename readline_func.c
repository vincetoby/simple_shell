#include "shell.h"

/**
 * _readline - reads the input string.
 * @ret_i_eof: the Return val of the getline func
 * Return: char input string
 */

char *_readline(int *ret_i_eof)
{
	char *in = NULL;
	size_t size = 0;

	/*Call the custom _getline function to read a line of input from stdin*/
	/*passing the address of 'in' and 'size' as arguments, and store the*/
	/*return value in 'ret_i_eof'.*/
	*ret_i_eof = getline(&in, &size, stdin); /*change the getline to _getline*/

	return (in);

}
