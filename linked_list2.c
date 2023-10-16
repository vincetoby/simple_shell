#include "shell.h"
/**
 * add_node1 - add var at end of varl list
 * @h: the head of linked lists
 * @lenvar: the length of var
 * @val: the value of variable
 * @lenval: the length of value
 * Return: pointer to head
 */

varl *add_node1(varl **h, int lenvar, char *val, int lenval)
{
	varl *nw, *tp;

	nw = malloc(sizeof(varl));
	if (nw == NULL)
		return (NULL);

	nw->var_len = lenvar;
	nw->value = val;
	nw->value_len = lenval;

	nw->next = NULL;
	tp = *h;

	if (tp == NULL)
	{
		*h = nw;
	}
	else
	{
		while (tp->next != NULL)
		{
			tp = tp->next;
		}
		tp->next = nw;
	}
	return (*h);
}

/**
 * free_varl -frees varl list
 * @h: the head of linked lists
 * Return: void
 */

void free_varl(varl **h)
{
	varl *tp;
	varl *nw;

	if (h != NULL)
	{
		nw = *h;
		while ((tp = nw) != NULL)
		{
			nw = nw->next;
			free(tp);
		}
		*h = NULL;
	}
}
