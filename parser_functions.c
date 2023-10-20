#include "main.h"

/**
 * is_command - Check if a file at the given path is a valid command.
 * @info: A pointer to the info_type structure (not used in this function).
 * @path: The path to the file to be checked.
 *
 * Return: 1 if the file is a valid command, 0 otherwise.
 */
int is_command(info_type *info, char *path)
{
	struct stat file_stat;

	(void)info; /* Not used in this function. */

	if (!path || stat(path, &file_stat))
		return (0); /* Failed to stat the file. */

	if (S_ISREG(file_stat.st_mode))
	{
		return (1); /* The file is a regular file, indicating a valid command. */
	}

	return (0); /* The file is not a regular file (not a valid command). */
}

/**
 * dup_chars - Duplicate characters from a source string within
 *             a specified range.
 * @pathstr: The source string to duplicate characters from.
 * @start_idx: The starting index (inclusive) for character duplication.
 * @end_idx: The ending index (exclusive) for character duplication.
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start_idx, int end_idx)
{
	static char duplicated_buf[1024];
	int source_idx = 0, duplicated_idx = 0;

	for (source_idx = start_idx; source_idx < end_idx; source_idx++)
	{
		if (pathstr[source_idx] != ':')
		{
			duplicated_buf[duplicated_idx++] = pathstr[source_idx];
		}
	}
	/* Null-terminate the	duplicated string. */
	duplicated_buf[duplicated_idx] = '\0';
	return (duplicated_buf);
}

/**
 * find_path - Find the full path to a command in a given
 *             PATH environment string.
 * @info:  A pointer to the information struct.
 * @pathstr: The PATH environment string to search for the command.
 * @cmd: The command to search for.
 *
 * Return: A pointer to the full path of the command, or NULL if not found.
 */
char *find_path(info_type *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
