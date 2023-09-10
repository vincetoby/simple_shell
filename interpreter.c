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
		pid_t child_pid = fork();/*creates child process*/

		parser(buffer, argv, &argc);

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	return (0);
}
