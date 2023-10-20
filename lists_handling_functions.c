#include "main.h"

/**
 * add_node - Add a new node at the beginning of a linked list
 * @head: A pointer to a pointer to the head of the linked list
 * @str: The string to be stored in the new node
 * @num: An integer to be stored in the new node
 *
 * Return: A pointer to the new node if successful, or NULL on failure
 */
list_type *add_node(list_type **head, const char *str, int num)
{
	list_type *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_type));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_type));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Add a new node at the end of a linked list
 * @head: A pointer to a pointer to the head of the linked list
 * @str: The string to be stored in the new node
 * @num: An integer to be stored in the new node
 *
 * Return: A pointer to the new node if successful, or NULL on failure
 */
list_type *add_node_end(list_type **head, const char *str, int num)
{
	list_type *new_node, *current_node;

	if (!head)
		return (NULL);
	current_node = *head;
	new_node = malloc(sizeof(list_type));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_type));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}


/**
 * print_environment_variables - Print a list of environment variables.
 * @head: A pointer to the head of the linked list of environment variables.
 *
 * Return: The number of environment variables printed.
 */
size_t print_environment_variables(const list_type *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - Delete a node at a specific index in a linked list.
 * @head: A pointer to a pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 *
 * Return: 1 if successful, 0 if the node was not found or an error occurred.
 */
int delete_node_at_index(list_type **head, unsigned int index)
{
	list_type *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Free the memory of a linked list.
 * @head_ptr: A pointer to a pointer to the head of the linked list.
 */
void free_list(list_type **head_ptr)
{
	list_type *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
