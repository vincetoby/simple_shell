#include "shell.h"

/**
 * help_env - provides help info for env builtin
 * Return: void
 */

void help_env(void)
{
	char *msg = "env: env [option] [name=value] [command [args]]\n\t";
	char *msg2 = "Print the enviroment of the shell.\n";
	int len, len2;

	len = _strlen(msg);
	len2 = _strlen(msg2);

	write(STDOUT_FILENO, msg, len);
	write(STDOUT_FILENO, msg2, len2);
}

/**
 * help_set - provides help info for the setenv builtin
 * Return: void
 */
void help_set(void)
{

	char *msg = "setenv: setenv (const char *name, const char *value,";
	char *msg2 = "int replace)\n\t";
	char *msg3 = "Add a new definition to the environment\n";
	int len1, len2, len3;

	len1 = _strlen(msg);
	len2 = _strlen(msg2);
	len3 = _strlen(msg3);

	write(STDOUT_FILENO, msg, len1);
	write(STDOUT_FILENO, msg2, len2);
	write(STDOUT_FILENO, msg3, len3);
}
/**
 * help_unset - provides help info for the unsetenv builtin
 * Return: void
 */

void help_unset(void)
{
	char *msg = "unsetenv: unsetenv (const char *name)\n\t";
	char *msg2 = "Remove an entry completely from the environment\n";
	int len1, len2;

	len1 = _strlen(msg);
	len2 = _strlen(msg2);

	write(STDOUT_FILENO, msg, len1);
	write(STDOUT_FILENO, msg2, len2);
}

/**
 * help_main - provides help info for the help builtin
 * Return: void
 */

void help_main(void)
{
	char *msg = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "unsetenv [variable]\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_exit - provides help info for the exit built-in
 * Return: void
 */

void help_exit(void)
{
	char *msg = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "status is that of the last command executed\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
