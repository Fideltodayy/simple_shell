#include "main.h"

/**
 * hsh - Main loop for a shell-like program.
 * @info: A pointer to the program's information structure.
 * @av: An array of strings containing command-line arguments.
 *
 * Return: The return status of the program or built-in command
 */
int hsh(info_type *info, char **av)
{
	ssize_t read_status = 0;
	int built_in_result = 0;

	while (read_status != -1 && built_in_result != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts(PROMPT);
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, av);
			built_in_result = find_builtin(info);
			if (built_in_result == -1)
				find_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (built_in_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_result);
}

/**
 * find_builtin - Find and execute a built-in command
 * @info: A pointer to the program's information structure
 *
 * Return: The return status of the built-in command, or -1 if not found
 */
int find_builtin(info_type *info)
{
	int index, built_in_ret = -1;
	builtin_table built_in_commands[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; built_in_commands[index].type; index++)
		if (_strcmp(info->argv[0], built_in_commands[index].type) == 0)
		{
			info->line_count++;
			built_in_ret = built_in_commands[index].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Find and execute an external command.
 * @info: A pointer to the info_type structure containing program information.
 */
void find_cmd(info_type *info)
{
	char *command_path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	command_path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (command_path)
	{
		info->path = command_path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Create a child process to execute a command.
 * @info: A pointer to the info_type structure containing program information.
 */
void fork_cmd(info_type *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* This code is not reached if the execution is successful */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
