#include "main.h"

/**
 * _erratoi - Convert a string to an integer with error handling.
 * @s: The input string to convert to an integer.
 *
 * Return: The converted integer, or -1 on error.
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (index = 0;  s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Print an error message with additional information.
 * @info: A pointer to the info_type structure containing shell information.
 * @estr: The error message to print.
 */
void print_error(info_type *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_integer(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_integer - Print an integer to the specified file descriptor
 *           with error handling.
 * @input: The integer to print.
 * @fd: The file descriptor (STDOUT_FILENO or STDERR_FILENO) to
 *      which to print.
 *
 * Return: The number of characters printed.
 */
int print_integer(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int digit, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		output_char('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (digit = 1000000000; digit > 1; digit /= 10)
	{
		if (absolute_value / digit)
		{
			output_char('0' + current / digit);
			count++;
		}
		current %= digit;
	}
	output_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_long_to_string - Convert a long integer to a string
 *                          representation with options.
 * @num: The long integer to convert.
 * @base: The base for the conversion (e.g., 2 for binary,
 *        10 for decimal, 16 for hexadecimal).
 * @cFlag: argument flags
 *
 * Return: A pointer to the resulting string.
 */
char *convert_long_to_string(long int num, int base, int cFlag)
{
	static char *cChar;
	static char buffer[50];
	char sign_character = 0;
	char *result_ptr;
	unsigned long absolute_value = num;

	if (!(cFlag & CONVERT_UNSIGNED) && num < 0)
	{
		absolute_value = -num;
		sign_character = '-';

	}
	cChar = cFlag & CNVRT_L_CASE ? "0123456789abcdef" : "0123456789ABCDEF";
	result_ptr = &buffer[49];
	*result_ptr = '\0';

	do {
		*--result_ptr = cChar[absolute_value % base];
		absolute_value /= base;
	} while (absolute_value != 0);

	if (sign_character)
		*--result_ptr = sign_character;
	return (result_ptr);
}

/**
 * remove_comments - Remove comments from a string by truncating
 *                   it at the '#' character.
 * @input_string: address of the string to modify
 */
void remove_comments(char *input_string)
{
	int index;

	for (index = 0; input_string[index] != '\0'; index++)
		if (input_string[index] == '#' && (!index || input_string[index - 1] == ' '))
		{
			input_string[index] = '\0';
			break;
		}
}
