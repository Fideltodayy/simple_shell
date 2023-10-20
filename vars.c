#include "main.h"

/**
 * is_chain - Check for command chaining symbols and update command buffer type
 * @info: A pointer to the information structure
 * @input: The input string to be checked for chaining symbols
 * @position: A pointer to the current position in the input string
 *
 * Return: 1 if a command chaining symbol is found, 0 otherwise
 */
int is_chain(info_type *info, char *input, size_t *position)
{
	size_t current_pos = *position;

	if (input[current_pos] == '|' && input[current_pos + 1] == '|')
	{
		input[current_pos] = 0;
		current_pos++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (input[current_pos] == '&' && input[current_pos + 1] == '&')
	{
		input[current_pos] = 0;
		current_pos++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (input[current_pos] == ';') /*  Found end of this command */
	{
		input[current_pos] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = current_pos;
	return (1);
}

/**
 * check_chain - Check command chaining conditions and update
 *               buffer and position.
 * @info: A pointer to the information structure.
 * @buf: The input buffer to be checked.
 * @pos: A pointer to the current position in the buffer.
 * @i: The current position in the buffer.
 * @len: The length of the buffer.
 */
void check_chain(info_type *info, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t new_pos = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			new_pos = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			new_pos = len;
		}
	}

	*pos = new_pos;
}

/**
 * replace_alias - Replace an alias with its value in the command arguments
 * @info: A pointer to the information structure
 *
 * Return: 1 if alias replacement is successful, 0 otherwise
 */
int replace_alias(info_type *info)
{
	int attempt;
	list_type *aliasEntry;
	char *alias_value;

	for (attempt = 0; attempt < 10; attempt++)
	{
		aliasEntry = node_starts_with(info->alias, info->argv[0], '=');
		if (!aliasEntry)
			return (0);
		free(info->argv[0]);
		alias_value = _strchr(aliasEntry->str, '=');
		if (!alias_value)
			return (0);
		alias_value = _strdup(alias_value + 1);
		if (!alias_value)
			return (0);
		info->argv[0] = alias_value;
	}
	return (1);
}

/**
 * replace_vars - Replace specific variables in the command arguments
 * @info: A pointer to the information structure
 *
 * Return: Always returns 0
 */
int replace_vars(info_type *info)
{
	int i = 0;
	list_type *env_entry;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_long_to_string(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_long_to_string(getpid(), 10, 0)));
			continue;
		}
		env_entry = node_starts_with(info->env, &info->argv[i][1], '=');
		if (env_entry)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(env_entry->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replace the content of a string with a new string
 * @original_string: A pointer to the old string
 * @new_string: The new string to replace the old content
 *
 * Return: 1 if the replacement is successful, 0 otherwise
 */
int replace_string(char **original_string, char *new_string)
{
	free(*original_string);
	*original_string = new_string;
	return (1);
}
