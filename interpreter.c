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
		parser(buffer, argv, &argc);

		char *full_path = path_search(argv[0];

		if (full_path != NULL) /*If cmd exist in PATH and its executable*/
		{
			pid_t child_pid = fork();/*creates child process*/

			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0)
			{
				if (execve(full_path, argv, NULL) == -1)
				{
					perror(argv[0]);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				free(full_path);
				wait(&status);
			}
		else
		{
			char err_msg[100];

			_strcpy(err_msg, argv[0]);
			_strcat(err_msg, ":Command not found");
			write(STDERR_FILENO, err_msg, _strlen(err_msg));
		}
	return (0);
}
