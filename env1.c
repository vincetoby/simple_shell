#include "shell.h"

/**
 * envir_cmp - compares environ var names
 * with the name passed.
 * @env_n: environment variable name
 * @str: inputed string
 * Return: 0 if not same.
 */

int envir_cmp(const char *env_n, const char *str)
{

	int i = 0;

	while (env_n[i] != '=')
	{
		if (env_n[i] != str[i])
		{
			return (0);
		}
		i++;
	}
	return (i + 1);

}

/**
 * _getenv - fetches an environment variable
 * @str: Name of the environment variable
 * @environ: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *str, char **environ)
{

	char *envp = NULL;
	int i = 0, cp = 0;

	/* loop through environment variable*/
	while (environ[i])
	{
		/*compare str to env and store return value in cp*/
		cp = envir_cmp(environ[i], str);
		if (cp) /*if cp isnt 0, it means a match is found*/
		{
			envp = environ[i]; /*copy the found path into envp*/
			break; /*break to leave the while loop*/
		}
		i++;
	}
	return (envp + cp);
}



/**
 * _printenv - prints the env vars to stdout
 * @data: Data struct
 * Return: 1 on success.
 */

int _printenv(myshell *data)
{
	int i, j;

	/*Loop through the environment variables*/
	for (i = 0; data->env[i]; i++)
	{
		j = 0;
		while (data->env[i][j]) /*get length of current env*/
		{
			j++;
		}
		/*Write the environment variable to standard output follwd by a newline*/
		write(STDOUT_FILENO, data->env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->stat = 0;
	return (1);
}
