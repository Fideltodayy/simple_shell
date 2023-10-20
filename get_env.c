#include "main.h"

/**
 * get_environ - Retrieve environment variables as an array.
 * @info: A pointer to the info_type structure containing environment information.
 *
 * Return: An array of environment variable strings.
 */
char **get_environ(info_type *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_typeo_strings(info->env);

		/* Reset the 'env_changed' flag */
		info->env_changed = 0;
	}

	/* Return the array of environment variables */
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable from the info structure.
 * @info: A pointer to the info_type structure containing environment information.
 * @var: The name of the environment variable to remove.
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_type *info, char *var)
{
	list_type *node = info->env;
	size_t index = 0;
	char *p;

	/* Check for NULL pointers */
	if (!node || !var)
		return (0);

	/* Loop through the environment list */
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* Update the 'env_changed' flag and reset the index */
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}

		/* Move to the next node in the list and update the index */
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set an environment variable in the info structure.
 * @info: SA pointer to the info_type structure containing
 *        environment information.
 * @var: The name of the environment variable to set.
 * @value: The value to associate with the environment variable.
 *
 * Return: 0 on success, 1 if memory allocation fails.
 */
int _setenv(info_type *info, char *var, char *value)
{
	char *buf = NULL;
	list_type *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
