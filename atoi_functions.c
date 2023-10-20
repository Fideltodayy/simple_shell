#include "main.h"

/**
 * is_interactive - Check if the program is running interactively.
 * @info: A pointer to the info_type structure that holds file
 *        descriptor information.
 *
 * Return: 1 if ruuning interactively mode, 0 otherwise
 */
int is_interactive(info_type *info)
{
	/*
     * Check if stdin is associated with a terminal (TTY).
     * This ensures that the program is running interactively.
     */
	int is_stdin_tty = isatty(STDIN_FILENO);

	/*
     * Check if readfd is one of the standard file descriptors (0, 1, 2).
     * This indicates whether input is redirected
     * from a file or another source.
     */
	int is_read_fd_standard = (info->readfd >= 0 && info->readfd <= 2);


	return (is_stdin_tty && is_read_fd_standard);
}

/**
 * is_delim - checks if a character is a delimeter
 * @c: The character to check.
 * @delim: A string of delimiter characters.
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	/* Iterate through the 'delim' string. */
	while (*delim)
	{
		/* Check if the current character matches 'c'. */
		if (*delim == c)
		{
			return (1); /* 'c' is a delimiter. */
		}
		delim++; /* Move to the next character in 'delim'. */
	}
	return (0); /* 'c' is not a delimiter. */
}

/**
 *_isalpha - checks if the character 'c' is a letter (alphabetic character).
 *@c: The character to check.
 *Return: 1 if 'c' is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer.
 *@s: the string to be converted.
 *Return: 0 if no numbers in string, converted number otherwise.
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	/* Loop through the characters in the string */
	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		/* Check for a minus sign to determine the sign of the integer */
		if (s[i] == '-')
			sign *= -1;

		/* Check if the character is a digit (0-9) */
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	/* Calculate the final output by applying the sign to the result */
	output = sign * result;
	return (output);
}

