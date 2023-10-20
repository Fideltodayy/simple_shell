#include "main.h"

/**
 * _myhistory - displays the history list, one command by line,
 *              preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_type *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias for a shell command.
 * @info: A pointer to the info_type structure containing alias data.
 * @unset: The alias to unset.
 *
 * Return: 1 if the unset operation fails, 0 otherwise.
 */
int unset_alias(info_type *info, char *unset)
{
	char *equalSignPos, saved_char;
	int unset_result;

	equalSignPos = _strchr(unset, '=');
	if (!equalSignPos)
		return (1);
	saved_char = *equalSignPos;
	*equalSignPos = 0;
	unset_result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, unset, -1)));
	*equalSignPos = saved_char;
	return (unset_result);
}

/**
 * set_alias - Set an alias for a shell command.
 * @info: A pointer to the info_type structure containing alias data.
 * @alias_string: The alias string to set or unset.
 *
 * Return: 1 if the operation fails, 0 otherwise.
 */
int set_alias(info_type *info, char *alias_string)
{
	char *equalSignPos;

	equalSignPos = _strchr(alias_string, '=');
	if (!equalSignPos)
		return (1);
	if (!*++equalSignPos)
		return (unset_alias(info, alias_string));

	unset_alias(info, alias_string);
	return (add_node_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * print_alias - Print an alias string in a specific format.
 * @node: A pointer to a node containing the alias string.
 *
 * Return: 0 if the alias is printed successfully, 1 otherwise.
 */
int print_alias(list_type *node)
{
	char *equalSignPos = NULL, *alias_name  = NULL;

	if (node)
	{
		equalSignPos = _strchr(node->str, '=');
		for (alias_name  = node->str; alias_name  <= equalSignPos; alias_name++)
			_putchar(*alias_name);
		_putchar('\'');
		_puts(equalSignPos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Manage shell aliases: print, set, or match and print.
 * @info: A pointer to the info_type structure containing alias data.
 *
 *  Return: Always returns 0 to indicate success.
 */
int _myalias(info_type *info)
{
	int i = 0;
	char *equalSignPos  = NULL;
	list_type *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equalSignPos  = _strchr(info->argv[i], '=');
		if (equalSignPos)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
