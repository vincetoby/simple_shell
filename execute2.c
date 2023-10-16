#include "shell.h"

/**
 * execute - this func finds builtins and commands
 * @data: Data struct
 * Return: 1 on success.
 */

int execute(myshell *data)
{
	int (*build)(myshell *data);
	/*Declare a function pointer 'build' and assign it the function*/
	/*associated with the first argument (if it's a built-in command)*/


	/*Check if the first argument is NULL*/
	/*return 1 if no arg*/
	if (data->args[0] == NULL)
		return (1);

	build = fetch_builtin(data->args[0]);
	/*Check if a built-in command function was found*/
	/*execute cmd if found and return its data*/
	if (build != NULL)
		return (build(data));


	/*If it's not a built-in command, execute the 'cmnd_execute' function*/
	/*and return its result*/
	return (cmnd_execute(data));
}
