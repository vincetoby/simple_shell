#include "shell.h"

/**
 * handle_exit - exits the shell
 * Return: void
 */

void handle_exit()
{
	exit(0); /* exit the shell*/
}

/**
 * handle_env - print current environment
 * Return: void
 */

void handle_env()
{
	extern char **environ; /* to access and print all env variables*/
	char **env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

