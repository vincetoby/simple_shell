#include "shell.h"

/**
 * command_not_found - write a customized error message to stderr
 * @command: command that wasnt found
 * Return: void
 */

void command_not_found(const char *command)
{
	char err_msg[100];

	_strcpy1(err_msg, command);
	_strcat(err_msg, ": Command not found\n");
	write(STDERR_FILENO, err_msg, _strlen(err_msg));
}
