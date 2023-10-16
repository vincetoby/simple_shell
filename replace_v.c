#include "shell.h"

/**
 * envir_checker - Checking if the typed variable is an env variable
 * @head: head of a singly linked list
 * @str: input string
 * @data: Data structure
 * Return: void
 */

void envir_checker(varl **head, char *str, myshell *data) /*edited*/
{
	int i = 0, j, c, len;
	char **envir;

	envir = data->env;
	while (envir[i] != NULL)
	{
		for (j = 1, c = 0; envir[i][c]; c++)
		{
			if (str[j] == envir[i][c])
				j++;

			if (envir[i][c] == '=')
			{
				len = _strlen(envir[i] + c + 1);
				add_node1(head, j, envir[i] + c + 1, len);
				return;
			}
			else
				break;
		}
		i++;
	}

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\t' || str[j] == '\n' || str[j] == ';' || str[j] == ' ')
			break;
		j++;
	}
	add_node1(head, j, NULL, 0);
}

/**
 * var_checker - Checks if inputed char is $$ or $?
 * @head: Head of singly linked list
 * @str: the input string
 * @stat: status of my Shell
 * @mydata: myData structure
 * Return: num of chars processed
 */

int var_checker(varl **head, char *str, char *stat, myshell *mydata) /*edited*/
{
	int i, lenstat, lenpid;

	/*Calculate the lengths of 'stat' and 'mydata->pid'*/
	lenstat = _strlen(stat);
	lenpid =  _strlen(mydata->pid);

	/*Iterate through the characters in the 'str' string*/
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '$') /*Check if the current character is a '$' symbol*/
		{
			switch (str[i + 1]) /*checks the char following '$'*/
			{
				case '?': /*If it's '?', add 'stat' as a variable*/
					add_node1(head, 2, stat, lenstat);
					i++;
					break;
				case '$': /*If it's '$', add 'mydata->pid' as a variable*/
					add_node1(head, 2, mydata->pid, lenpid);
					i++;
					break;
				case '\n':
				case '\0':
				case ' ':
				case '\t':
				case ';': /*If it's one of these characters, add NULL as a variable*/
					add_node1(head, 0, NULL, 0);
					break;
				default: /*For other characters, check if it matches an environment*/
					envir_checker(head, str + i, mydata);
			}
		}
	}
	return (i); /*Return the number of characters processed*/
}

/**
 * input_replace - replaces str into vars
 * @head: linked list head
 * @in: input str
 * @new_in: new input str (the replaced string)
 * @length: the new length
 * Return: the replaced string
 */

char *input_replace(varl **head, char *in, char *new_in, int length) /*edited*/
{
	varl *ptr;
	int i = 0, j = 0, k;

	ptr = *head;/*Initialize a pointer to the linked list of variables*/
	for (; i < length; i++) /*Loop through the chars in the new_in string*/
	{
		if (in[j] != '$')
		{
			new_in[i] = in[j]; /*If the current char isnt '$', copy to new_in str*/
			j++;
		}
		else if (in[j] == '$') /*Check if the current character is a '$'*/
		{
			if (ptr->var_len == 0 && ptr->value_len == 0)
			{
				new_in[i] = in[j]; /*If the variable is empty, copy the '$' symbol*/
				j++;
			}
			else if (ptr->var_len != 0 && ptr->value_len == 0)
			{
				for (k = 0; k < ptr->var_len; k++) /*If the var has no value, skip it*/
					j++;
				i--; /*Decrement 'i' to compensate for the skipped variable*/
			}
			else
			{
				for (k = 0; k < ptr->value_len; k++)/*Copy value of var to new_in str*/
				{
					new_in[i] = ptr->value[k];
					i++;
				}
				j = j + (ptr->var_len); /*Skip the variable in the input string*/
				i--; /*Decrement 'i' to avoid overwriting the next character*/
			}
			ptr = ptr->next; /*Move to the next variable in the linked list*/
		}
	}
	return (new_in); /*return modified new string*/
}

/**
 * var_replace - replaces string into variables
 * @in: input string
 * @data: struct
 * Return: replaced string
 */

char *var_replace(char *in, myshell *data) /*edited*/
{
	varl *head, *ptr;
	char *stat, *new_in;
	int len1, len2;

	head = NULL; /*init head to null*/
	stat = _itoa(data->stat); /*convert the stat integer to a string*/
	/*Calculate the original length of the input string with variables*/
	len1 = var_checker(&head, in, stat, data);

	if (head == NULL) /*If no vars to replace, return the original input*/
	{
		free(stat);
		return (in);
	}
	/*Initialize variables for the new input length calculation*/
	ptr = head;
	len2 = 0;
	while (ptr != NULL) /*get new_in length by iterating tru linked list*/
	{
		len2 = len2 + (ptr->value_len - ptr->var_len);
		ptr = ptr->next;
	}
	len2 = len2 + len1;
	new_in = malloc(sizeof(char) * (len2 + 1));/*Allocate mem for new_in*/
	if (new_in == NULL) /*check for malloc failure*/
		return (NULL);

	new_in[len2] = '\0'; /*null-terminate new_in*/
	/*Replace variables in the input and store the result in new_input*/
	new_in = input_replace(&head, in, new_in, len2);
	free(in);
	free(stat);
	free_varl(&head);
	return (new_in);
}
