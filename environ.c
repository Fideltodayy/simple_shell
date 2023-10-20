#include "main.h"

/**
 * _myenv - Print environment variables.
 * @info: A pointer to the info_type structure containing environment variables.
 *
 * Return: Always returns 0 to indicate success.
 */
int _myenv(info_type *info)
{
	print_environment_variables(info->env);
	return (0);
}

/**
 * _getenv - Retrieve the value of an environment variable.
 * @info: A pointer to the info_type structure containing environment variables.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: A pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *_getenv(info_type *info, const char *name)
{
	list_type *node = info->env;
	char *variable_value;

	while (node)
	{
		variable_value = starts_with(node->str, name);
		if (variable_value && *variable_value)
			return (variable_value);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Set or modify an environment variable.
 * @info: A pointer to the info_type structure containing environment variables.
 *
 *  Return: 0 on success, 1 on failure.
 */
int _mysetenv(info_type *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Unset one or more environment variables.
 * @info: A pointer to the info_type structure containing environment variables.
 *
 *  Return: 0 on success, 1 on failure.
 */
int _myunsetenv(info_type *info)
{
	int arg_index;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (arg_index = 1; arg_index <= info->argc; arg_index++)
		_unsetenv(info, info->argv[arg_index]);

	return (0);
}

/**
 * populate_env_list - Populate the environment variables list.
 * @info: A pointer to the info_type structure containing environment variables.
 *
 * Return: Always returns 0 to indicate success.
 */
int populate_env_list(info_type *info)
{
	list_type *env_list = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&env_list, environ[index], 0);
	info->env = env_list;
	return (0);
}
