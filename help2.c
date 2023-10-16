#include "shell.h"

/**
 * get_help - Provide help info for the help builtin
 * Return: bvoid
 */

void get_help(void)
{
	char *msg = "help: help [-dms] [pattern ...]\n";
	char *msg2 = "\tDisplay information about builtin commands.\n ";
	char *msg3 = "Displays brief summaries of builtin commands.\n";
	int len1, len2, len3;

	len1 = _strlen(msg);
	len2 = _strlen(msg2);
	len3 = _strlen(msg3);

	write(STDOUT_FILENO, msg, len1);
	write(STDOUT_FILENO, msg2, len2);
	write(STDOUT_FILENO, msg3, len3);
}

/**
 * help_alias - provides help info for the alias builtin
 * Return: void
 */

void help_alias(void)
{
	char *msg = "alias: alias [-p] [name[=value]...]\n";
	char *msg1 = "\tDefine or display aliases.\n ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	write(STDOUT_FILENO, msg1, _strlen(msg1));
}

/**
 * help_cd - Provide help info for the alias builtin.
 * Return: void
 */

void help_cd(void)
{
	char *msg = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
	char *msg1 = "\tChange the shell working directory.\n ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	write(STDOUT_FILENO, msg1, _strlen(msg1));
}
