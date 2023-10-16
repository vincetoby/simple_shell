#include "shell.h"

/**
 * add_node_sep - It adds separator to the endof linked list
 * @h: the head of linked lists.
 * @sept: separators which include ; | &.
 * Return: address of the heads.
 */
sep_t *add_node_sep(sep_t **h, char sept) /*edited*/
{
	sep_t *sept_n, *tempor;

	sept_n = malloc(sizeof(sep_t));
	if (sept_n == NULL)
		return (NULL);

	sept_n->sep = sept;
	sept_n->next = NULL;
	tempor = *h;

	if (tempor == NULL)
	{
		*h = sept_n;
	}
	else
	{
		while (tempor->next != NULL)
			tempor = tempor->next;
		tempor->next = sept_n;
	}

	return (*h);
}

/**
 * free_separator - frees a sep_t
 * @h: head of singly linked lists.
 * Return: void
 */

void free_separator(sep_t **h) /*edited*/
{
	sep_t *tp, *nw;

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

/**
 * add_node_line - adds a command line to line_t's end
 * @h: reps the head of linked lists.
 * @lane: command line
 * Return: pointer to head
 */

line_t *add_node_line(line_t **h, char *lane)
{
	line_t *nw, *tp;

	nw = malloc(sizeof(line_t));
	if (nw == NULL)
		return (NULL);

	nw->line = lane;
	nw->next = NULL;
	tp = *h;

	if (tp == NULL)
	{
		*h = nw;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = nw;
	}
	return (*h);
}

/**
 * free_line - frees line_t
 * @h: heads of singly linked list
 * Return: void
 */

void free_line(line_t **h)
{
	line_t *tp;
	line_t *nw;

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
