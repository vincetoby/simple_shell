#include "shell.h"

/**
 * path_search - searches a command in PATH
 * @command: command to search for
 * Return: pointer to char
 */

char *path_search(const char *command)
{
	char *dup = NULL, *path, *token, *full_path;
	size_t len_fpath, acc;

	path = _getenv("PATH");
	if (path == NULL)
	{
		err_pathenv(); /*a function that writes an error msg*/
	}
	/*printf("PATH: %s\n", path); debugging*/
		/*return (NULL); / means PATH is not set*/
	token = _strtok(path, ":");
	while (token != NULL)
	{
		dup = NULL; /*RESETS dup to null*/
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

		acc = access(full_path, X_OK);
		if (acc == 0)
		{
			/*printf("Found executable: %s\n", full_path); /debugging*/
			dup = _strdup(full_path); /*duplicate fullpath, then free it*/
			free(full_path);
			break; /*exit while loop*/
		}
		free(full_path); /*free malloc*/
		token = _strtok(NULL, ":");
	}
	return (dup); /* Return the duplicated path or NULL if not found*/
}
