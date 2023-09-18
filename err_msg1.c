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

/**
 * err_pathenv - prints error message for path environ
 * Return: void
 */

void err_pathenv(void)
{
	char *error_msg = "Error: PATH environment variable not set.\n";

	write(STDERR_FILENO, error_msg, strlen(error_msg));
	exit(EXIT_FAILURE);
}

/**
 * err_setenv - prints custom error message
 * Return: void
 */

void err_setenv(void)
{
	char *s = "setenv: Invalid syntax. Usage: setenv VARIABLE VALUE";

	write(STDERR_FILENO, s, _strlen(s));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * err_unsetenv - prints custom error message
 * Return: void
 */

void err_unsetenv(void)
{
	char *s = "unsetenv: Invalid syntax. Usage: setenv VARIABLE VALUE";

	write(STDERR_FILENO, s, _strlen(s));
	write(STDERR_FILENO, "\n", 1);
}
