#include "shell.h"

/**
 * cd - changes currents directories
 * @data: data struct containing relevant data
 * Return: 1 on success
 */

int cd(myshell *data)
{
	char *direc;
	int cmp1, cmp2, cmp3;

	direc = data->args[1];

	if (direc != NULL)
	{
		cmp1 = _strcmp("~", direc);
		cmp2 = _strcmp("--", direc);
		cmp3 = _strcmp("$HOME", direc);
	}

	if (direc == NULL || !cmp1 || !cmp2 || !cmp3)
	{
		cd_homerun(data);
		return (1);
	}
	if (_strcmp(".", direc) == 0 || _strcmp("..", direc) == 0)
	{
		cdir_point(data);
		return (1);
	}
	if (_strcmp("-", direc) == 0)
	{
		cd_prev(data);
		return (1);
	}
	cd_next(data);
	return (1);
}

/**
 * cdir_point - changes to parent directory in shell
 * @data: data struct to extract env
 * Return: void
 */

void cdir_point(myshell *data)
{
	char *direc, *pwd2, *tok_pwd, pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd)); /*get curr working dir*/
	pwd2 = _strdup(pwd); /*duplicate*/
	_setenv("OLDPWD", pwd2, data); /*Set OLDPWD to the current directory*/
	direc = data->args[1]; /*Get the dir specified as an argument*/
	if (_strcmp(".", direc) == 0)
	{
		_setenv("PWD", pwd2, data); /* Set PWD to the current directory*/
		free(pwd2);
		return;
	}
	if (_strcmp("/", pwd2) == 0)
	{
		free(pwd2);
		return;
	}
	tok_pwd = pwd2;/*copy current directory*/
	rev_string(tok_pwd); /*reverses current dir for tokenization*/
	tok_pwd = _strtok(tok_pwd, "/");/*tokenize reverse str*/
	if (tok_pwd != NULL)
	{
		tok_pwd = _strtok(NULL, "\0"); /*get the remaining part after reversing*/
		if (tok_pwd != NULL)
			rev_string(tok_pwd); /*Reverse back to the original order*/
	}
	if (tok_pwd != NULL)
	{
		chdir(tok_pwd); /*change directory to d new directory*/
		_setenv("PWD", tok_pwd, data); /*Set PWD to the new directory*/
	}
	else
	{
		chdir("/"); /*If no specified directory, change to the root dir*/
		_setenv("PWD", "/", data); /*set PWD to root dir*/
	}
	free(pwd2); /*Free allocated memory*/
	data->stat = 0; /*set status to 0, indicating success*/
}

/**
 * cd_next - changes to a specified directory
 * @data: data struct
 * Return: void
 */

void cd_next(myshell *data)
{
	char pwd[PATH_MAX];
	char *direc, *pwd2, *direc2;

	getcwd(pwd, sizeof(pwd));

	direc = data->args[1];
	if (chdir(direc) == -1)
	{
		fetch_error(data, 2);
		return;
	}

	pwd2 = _strdup(pwd);
	_setenv("OLDPWD", pwd2, data);

	direc2 = _strdup(direc);
	_setenv("PWD", direc2, data);

	free(pwd2);
	free(direc2);

	data->stat = 0;

	chdir(direc);
}

/**
 * cd_prev - changes frm cuurent to previous dir
 * @data: data struct
 * Return: void
 */

void cd_prev(myshell *data)
{
	char pwd[PATH_MAX];
	char *pwdp, *prevpwd, *pwd2, *prevpwd2;

	getcwd(pwd, sizeof(pwd));
	pwd2 = _strdup(pwd);

	prevpwd = _getenv("OLDPWD", data->env); /*get d value of d OLDPWD env var*/

	if (prevpwd == NULL) /*If OLDPWD is not set, use the current directory*/
		prevpwd2 = pwd2;
	else
		prevpwd2 = _strdup(prevpwd); /*Duplicate the value of OLDPWD*/

	_setenv("OLDPWD", pwd2, data); /*Set the value of OLDPWD to the prev dir*/

	if (chdir(prevpwd2) == -1) /*Change d current working dir to the prev dir*/
		_setenv("PWD", pwd2, data);
	else
		_setenv("PWD", prevpwd2, data);

	/*Get the updated PWD environment variable*/
	pwdp = _getenv("PWD", data->env);

	/*Print the current working directory*/
	write(STDOUT_FILENO, pwdp, _strlen(pwdp));
	write(STDOUT_FILENO, "\n", 1);

	/*Free allocated memory*/
	free(pwd2);
	if (prevpwd)
		free(prevpwd2);

	data->stat = 0;

	chdir(pwdp); /*Change the current working dir back to the updated PWD*/
}

/**
 * cd_homerun - changes curr dir to home dir
 * @data: data struct
 * Return: void
 */

void cd_homerun(myshell *data)
{
	char pwd[PATH_MAX], *pwd2, *home_env;
	int chdir_check;

	getcwd(pwd, sizeof(pwd)); /*Gets the current working directory*/
	pwd2 = _strdup(pwd);/* duplicate for easy manipulation*/

	home_env = _getenv("HOME", data->env);/*gets the home env*/

	if (home_env == NULL) /*If HOME is not set, set OLDPWD to the current dir */
	{
		_setenv("OLDPWD", pwd2, data);
		free(pwd2);
		return;
	}
	chdir_check = chdir(home_env); /*change dir to home, store return value*/
	if (chdir_check == -1) /*if chdir fails, print error msg*/
	{
		fetch_error(data, 2);
		free(pwd2);
		return;
	}
	/*Set OLDPWD to the current dir, and PWD to the HOME dir*/
	_setenv("OLDPWD", pwd2, data);
	_setenv("PWD", home_env, data);
	free(pwd2);
	data->stat = 0; /*Set the status to 0 to indicate success*/
}
