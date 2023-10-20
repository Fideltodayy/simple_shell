#include "main.h"

/**
 * construct_history_file_path - Construct the full path to the history file.
 * @info: A pointer to the info_type structure.
 *
 * Return: The full path to the history file, or NULL on failure.
 */
char *construct_history_file_path(info_type *info)
{
	char *history_file_path, *home_directory;
	unsigned int temp;

	home_directory = _getenv(info, "HOME=");
	if (!home_directory)
		return (NULL);
	temp = _strlen(home_directory) + _strlen(HIST_FILE) + 2;
	history_file_path = malloc(sizeof(char) * temp);
	if (!history_file_path)
		return (NULL);
	history_file_path[0] = 0;
	_strcpy(history_file_path, home_directory);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);
	return (history_file_path);
}

/**
 * write_history - Write the command history to a history file.
 * @info: A pointer to the info_type structure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_type *info)
{
	ssize_t file_descriptor;
	char *history_file = construct_history_file_path(info);
	list_type *node = NULL;

	if (!history_file)
		return (-1);

	file_descriptor = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file);
	if (file_descriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_type *info)
{
	int index, last_delim = 0, linecount = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buf = NULL, *filename = construct_history_file_path(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	read_length = read(file_descriptor, buf, file_size);
	buf[file_size] = 0;
	if (read_length <= 0)
		return (free(buf), 0);
	close(file_descriptor);
	for (index = 0; index < file_size; index++)
		if (buf[index] == '\n')
		{
			buf[index] = 0;
			build_history_list(info, buf + last_delim, linecount++);
			last_delim = index + 1;
		}
	if (last_delim != index)
		build_history_list(info, buf + last_delim, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Build a history list of commands.
 * @info: A pointer to the information struct.
 * @buffer: The command to add to the history list.
 * @line_count: The line count for the command.
 *
 * Return: 0 on success.
 */
int build_history_list(info_type *info, char *buffer, int line_count)
{
	list_type *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history list.
 * @info: A pointer to the information struct.
 *
 * Return: The total number of history entries.
 */
int renumber_history(info_type *info)
{
	list_type *entry = info->history;
	int entryCount = 0;

	while (entry)
	{
		entry->num = entryCount++;
		entry = entry->next;
	}

	info->histcount = entryCount;
	return (entryCount);
}
