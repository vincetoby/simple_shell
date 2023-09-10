#include "shell.h"

/**
 * path_search - searches a command in PATH
 * @command: command to search for
 * Return: pointer to char
 */

char *path_search(const char *command)
{
	char *path, *token;
	size_t len_fpath;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL); /* means PATH is not set*/
	token = strtok(path, ":");
	while (token != NULL)
	{
		/*"+ 2" counts for the "/" and null byte*/
		len_fpath = _strlen(token) + strlen(command) + 2;
		char full_path[len_fpath];

		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (acccess(full_path, X_OK) == 0)
		{
			return (_strdup(full_path)); /*return full path dup*/
		}
		token = strtok(NULL, ":");
	}
	return (NULL); /* command not found in PATH*/
}
