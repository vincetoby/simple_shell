#include "shell.h"

/**
 * execute_cmd - executes the process in main
 * @cmd: command used
 * @argv: arguments
 * Return: 0 on success, else status
 */

int execute_cmd(const char *cmd, char *const argv[])
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		 /* Child process */
        	if (execve(cmd, argv, NULL) == -1)
		{
            		perror("execve");
            		exit(EXIT_FAILURE);
        	}
	}
	else
	{
        	/* Parent process */
		int status;
		wait(&status);
		return (status);
	}
	return (0);
}
