#include "shell.h"

/**
 * cd_col - checks if current position *index within a given path string is ":"
 * @path: the path of type char.
 * @index: pointer to index.
 * Return: 1 if path is searchable, 0 otherwise.
 */

int cd_col(char *path, int *index)
{
	if (path[*index] == ':') /*Check if the current character is a colon*/
		return (1);

	/*Loop through the chars until a ':' or the end of string is found*/
	while (path[*index] && path[*index] != ':')
	{
		*index += 1; /*Move to the next character*/
	}

	/*Move to the next character if a colon is found*/
	if (path[*index])
		*index += 1;

	return (0);
}

/**
 * cmd_lock - locates a command in the env
 * @commd: the inputed command
 * @env: the copied environment variable
 * Return: location of the command.
 */

char *cmd_lock(char *commd, char **env)
{
	int dirlen, commdlen, index = 0;
	char *path, *pathptr, *pathtoken, *direc;
	struct stat st;

	path = _getenv("PATH", env);
	if (path)
	{
		pathptr = _strdup(path);
		commdlen = _strlen(commd);
		pathtoken = _strtok(pathptr, ":");
		while (pathtoken != NULL)
		{
			if (cd_col(path, &index))
				if (stat(commd, &st) == 0)
					return (commd);
			dirlen = _strlen(pathtoken);
			direc = malloc(dirlen + commdlen + 2);
			_strcpy(direc, pathtoken);
			_strcat(direc, "/");
			_strcat(direc, commd);
			_strcat(direc, "\0");
			if (stat(direc, &st) == 0)
			{
				free(pathptr);
				return (direc);
			}
			free(direc);
			pathtoken = _strtok(NULL, ":");
		}
		free(pathptr);
		if (stat(commd, &st) == 0)
			return (commd);
		return (NULL);
	}
	if (commd[0] == '/')
		if (stat(commd, &st) == 0)
			return (commd);
	return (NULL);
}

/**
 * executable - checks if executable
 * @data: data struct
 * Return: 0 if not an exec
 */

int executable(myshell *data)
{
	struct stat st;
	int indx = 0;
	char *in;

	in = data->args[0];
	while (in[indx])
	{
		if (in[indx] == '.')
		{
			if (in[indx + 1] == '.')
				return (0);
			if (in[indx + 1] == '/')
				continue;
			else
				break;
		}
		else if (in[indx] == '/' && indx != 0)
		{
			if (in[indx + 1] == '.')
				continue;
			indx++;
			break;
		}
		else
			break;
		indx++;
	}
	if (indx == 0)
		return (0);

	if (stat(in + indx, &st) == 0)
	{
		return (indx);
	}
	fetch_error(data, 127);
	return (-1);
}

/**
 * cmd_errors - Checks if user is permitted to access
 * @direc: directory
 * @data: data struct containing relevant data
 * Return: 1 in error, 0 otherwise
 */

int cmd_errors(char *direc, myshell *data)
{
	if (direc == NULL)
	{
		fetch_error(data, 127);
		return (1);
	}
	if (_strcmp(data->args[0], direc) != 0)
	{
		if (access(direc, X_OK) == -1)
		{
			fetch_error(data, 126);
			free(direc);
			return (1);
		}
		free(direc);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			fetch_error(data, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * cmnd_execute - executes command lines
 * @data: data struct (args and input)
 * Return: 1 on success.
 */

int cmnd_execute(myshell *data)
{
	pid_t child, wait;
	int state, exe;
	char *direc;
	(void) wait;

	exe = executable(data);
	if (exe == -1)
		return (1);
	if (exe == 0)
	{
		direc = cmd_lock(data->args[0], data->env);
		if (cmd_errors(direc, data) == 1)
			return (1);
	}
	child = fork();
	if (child < 0)
	{
		perror(data->argv[0]);
		return (1);
	}
	else if (child == 0)
	{
		if (exe == 0)
			direc = cmd_lock(data->args[0], data->env);
		else
			direc = data->args[0];
		execve(direc + exe, data->args, data->env);
	}
	else
	{
		do {
			wait = waitpid(child, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->stat = state / 256;
	return (1);
}
