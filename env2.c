
#include "shell.h"

/**
 * cpy_data - copies data to create a new envir or alias
 * a new env or alias
 * @str: the envir or alias
 * @val: the value of the envir or alias
 * Return: the copied envir or alias.
 */

char *cpy_data(char *str, char *val)
{
	char *buff;
	int len1, len2, len_t;

	len1 = _strlen(str);
	len2 = _strlen(val);
	len_t = len1 + len2 + 2;
	buff = malloc(sizeof(char) * (len_t));
	if (buff == NULL) /*check for malloc failure*/
		return (NULL);
	_strcpy(buff, str);
	_strcat(buff, "=");
	_strcat(buff, val);
	_strcat(buff, "\0");

	return (buff);
}

/**
 * _setenv - sets an environment variable
 * @str: the environment variable to set
 * @val: Value to set it with
 * @data: Data struct to use the vopied environment var
 * Return: void
 */

void _setenv(char *str, char *val, myshell *data)
{
	char *envvar, *envstr;
	int i = 0;

	while (data->env[i])
	{
		envvar = _strdup(data->env[i]);
		envstr = _strtok(envvar, "=");
		if (_strcmp(envstr, str) == 0)
		{
			free(data->env[i]);
			data->env[i] = cpy_data(envstr, val);
			free(envvar);
			return;
		}
		free(envvar);
		i++;
	}
	data->env = _reallocdp(data->env, i, sizeof(char *) * (i + 2));
	data->env[i] = cpy_data(str, val);
	data->env[i + 1] = NULL;
}

/**
 * cmp_setenv - compares envir variables with input str
 * @data: data struct containing needed data
 * Return: 1 on success.
 */

int cmp_setenv(myshell *data)
{

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		fetch_error(data, -1);
		return (1);
	}
	_setenv(data->args[1], data->args[2], data);
	return (1);
}

/**
 * _unsetenv - unsets an environment variable
 * @data: data struct
 * Return: 1 on success.
 */

int _unsetenv(myshell *data)
{
	char **envir_new, *envvar, *envstr;
	int i = 0, j = 0, check;

	if (data->args[1] == NULL) /*Check if the arg for unsetting is provided*/
	{
		fetch_error(data, -1);
		return (1);
	}
	check = -1; /*initialize check to -1 to show it hasnt been set*/
	for (; data->env[i]; i++)/*Iterate through the current environment variables*/
	{
		envvar = _strdup(data->env[i]);/*Dup the curr env for safe manipulation*/
		envstr = _strtok(envvar, "="); /*tokenize the curr env*/
		if (_strcmp(envstr, data->args[1]) == 0) /*Compare 'envstr' with the arg*/
			check = i; /*if there is a match, set check to current index*/
		free(envvar); /*free dup*/
	}
	if (check == -1) /*if still -1, meaning the env var to unset wasnt found.*/
	{
		fetch_error(data, -1); /*fetch appropriate err msg*/
		return (1);
	}
	envir_new = malloc(sizeof(char *) * (i)); /*allocate mem for new env var */
	for (i = 0; data->env[i]; i++) /*Iterate through the curr env vars again.*/
	{
		if (i != check) /*copy the env var to the new env at index 'j'*/
		{
			envir_new[j] = data->env[i];
			j++;
		}
	}
	envir_new[j] = NULL; /*null terminate*/
	free(data->env[check]);/*Free mem alloc for env var at indx 'k' in data->env*/
	free(data->env); /*Free data->env*/
	data->env = envir_new; /*Update data->env to point to the new env*/
	return (1);
}
