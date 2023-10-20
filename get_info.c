#include "main.h"

/**
 * clear_info - Clear or reset specific fields within the info structure.
 * @info: A pointer to the info_type structure to be cleared.
 */
void clear_info(info_type *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initialize fields within the info structure based on
 *            command-line arguments.
 * @info: A pointer to the info_type structure to be initialized.
 * @av: An array of command-line arguments.
 */
void set_info(info_type *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Free memory associated with fields in the info structure.
 * @info: A pointer to the info_type structure containing various fields.
 * @all: Flag indicating whether to deallocate all memory or
 *       only specific fields.
 */
void free_info(info_type *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
