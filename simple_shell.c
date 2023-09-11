#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0
 */

int main(void)
{
	char buffer[MAX_BUFFER_SIZE], *argv[11];
	int status, argc = 0;
	const char *str = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";

	if (setenv("PATH", str, 1) != 0)
	{
		perror("setenv");
		exit(EXIT_FAILURE);
	}
	printf("PATH: %s\n", getenv("PATH"));/*debugging*/
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2); /* Creates a prompt */
		ssize_t read_bytes = read(STDIN_FILENO, buffer, sizeof(buffer));

		if (read_bytes <= 0) /*checks end-of-file (ctrl-D)*/
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		buffer[read_bytes - 1] = '\0'; /*removes newline character*/
		if (_strcmp(buffer, "exit") == 0) /*exit built-in*/
			handle_exit();
		if (_strcmp(buffer, "env") == 0) /*env built-in*/
			handle_env();
		parser(buffer, argv, &argc);
		printf("Command to execute: %s\n", argv[0]);  /*debbugging*/

		char *full_path = path_search(argv[0]);

		if (full_path != NULL) /*If cmd exist in PATH and its executable*/
		{
			/*call execute command to execute*/
			int exit_status = execute_cmd(full_path, argv);
			free(full_path);
		}
		else
			command_not_found(argv[0]); /*calls customized error message*/
	}
	return (0);
}
