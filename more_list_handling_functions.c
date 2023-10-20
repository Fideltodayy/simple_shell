#include "main.h"

/**
 * list_len - Count the number of nodes in a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t list_len(const list_type *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * list_typeo_strings - Convert a linked list to an array of strings
 * @head: A pointer to the head of the linked list
 *
 * Return: A dynamically allocated array of strings, or NULL on failure.
 */
char **list_typeo_strings(list_type *head)
{
	list_type *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - Prints elements of a linked list
 * @head: A pointer to the head of the linked list
 *
 * Return: The number of nodes in the list
 */
size_t print_list(const list_type *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_long_to_string(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Find a node whose string starts with a prefix.
 * @node: A pointer to the head of the linked list.
 * @prefix: The prefix to search for.
 * @c: The character to match at the start of the string (use -1 to ignore).
 *
 * Return: A pointer to the found node or NULL if no match is found.
 */
list_type *node_starts_with(list_type *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list
 * @head: A pointer to the head of the linked list
 * @node: A pointer to the node to find the index of
 *
 * Return: The index of the node if found, or -1 if not found
 */
ssize_t get_node_index(list_type *head, list_type *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
