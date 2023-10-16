#include "shell.h"

/**
 * free_mydata - frees the struct
 * @data: struct
 * Return: void
 */

void free_mydata(myshell *data)
{
	unsigned int i = 0;

	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	free(data->pid);
}

/**
 * set_myshell_data - Initializes my data structure
 * @data: the data structure to be initialized
 * @argv: argument vector
 * Return: void
 */

void set_myshell_data(myshell *data, char **argv)
{
	unsigned int i = 0;

	data->argv = argv;
	data->cmd_input = NULL;
	data->args = NULL;
	data->stat = 0;
	data->count = 1;

	/*counts the number of environment variables*/
	for (; environ[i]; i++)
		;

	/*Allocate memory for env and copy environment variables*/
	data->env = malloc(sizeof(char *) * (i + 1));

	i = 0; /*reset i to 0*/
	while (environ[i])
	{
		data->env[i] = _strdup(environ[i]);
		i++;
	}

	data->env[i] = NULL; /*null terminate the copied env */
	data->pid = _itoa(getpid());
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success.
 */

int main(int argc, char **argv)
{
	myshell data;
	(void) argc; /*signify that i wont use the argc*/

	signal(SIGINT, signalc); /*hand the ctrlc*/
	set_myshell_data(&data, argv);
	myshell_loop(&data);
	free_mydata(&data);

	if (data.stat < 0) /*checking status of my shell*/
	{
		return (255);
	}
	return (data.stat);
}
