#include "main.h"

/**
 * _myexit - Handle the shell exit behavior.
 * @info: A pointer to the info_type structure containing shell information.
 *          constant function prototype.
 *  Return: -2 to indicate the shell should exit, or 1 if there is an error.
 */
int _myexit(info_type *info)
{
	int exit_status;

	/* Check if an exit argument is provided */
	if (info->argv[1])
	{
		/* Convert the exit argument to an integer */
		exit_status = _erratoi(info->argv[1]);

		/* If the conversion failed (resulting in -1) */
		if (exit_status == -1)
		{
			info->status = 2;

			/* Print an error message */
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');

			/* Return an error code */
			return (1);
		}

		/* Set the error number and return a custom error code */
		info->err_num = exit_status;
		return (-2);
	}

	/* If no exit argument is provided */
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Change the current working directory.
 * @info: A pointer to the info_type structure containing shell information.
 *
 *  Return: 0 if the current directory is successfully changed, 1 on error.
 */
int _mycd(info_type *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Display help or information.
 * @info: A pointer to the info_type structure containing shell information.
 *
 *  Return: Always returns 0 to indicate success.
 */
int _myhelp(info_type *info)
{
	char **arguments;

	/* Store the command-line arguments array in 'arguments' */
	arguments = info->argv;

	_puts("help call works. Function not yet implemented \n");

	/* Temporary unused workaround; prints the first argument */
	if (0)
		_puts(*arguments); /* temp att_unused workaround */
	return (0);
}
