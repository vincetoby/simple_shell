#include "shell.h"

/**
 * path_search - searches a command in PATH
 * @command: command to search for
 * Return: pointer to char
 */

char *path_search(const char *command)
{
	char *path, *token, *full_path;
	size_t len_fpath;

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set.\n");
		exit(EXIT_FAILURE);
	}
	printf("PATH: %s\n", path);
		/*return (NULL); /* means PATH is not set*/
	token = strtok(path, ":");
	while (token != NULL)
	{
		/*"+ 2" counts for the "/" and null byte*/
		len_fpath = _strlen(token) + _strlen1(command) + 2;
		full_path = malloc(len_fpath);
		if (full_path == NULL)/* FOR memory allocation failure*/
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			printf("Found executable: %s\n", full_path);/*debugging*/
			return (_strdup(full_path)); /*return full path dup*/
		}
		free(full_path); /*free malloc*/
		token = strtok(NULL, ":");
	}
	return (NULL); /* command not found in PATH*/
}
