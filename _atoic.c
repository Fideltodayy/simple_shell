#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checks and sees if character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if it is true, 0 if it is false
 */
int is_delimeter(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 *_isalphabet - checks for alphabets
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: this is the string to be converted
 *Return: 0 if no numbers in string, converts the number otherwise
 */

int _atoi(char *s)
{
	int i, signvalue = 1, flagvalue = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flagvalue != 2; i++)
	{
		if (s[i] == '-')
			signvalue *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flagvalue = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flagvalue == 1)
			flagvalue = 2;
	}

	if (signvalue == -1)
		output = -result;
	else
		output = result;

	return (output);
}