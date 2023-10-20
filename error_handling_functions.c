#include "main.h"

/**
 *_eputs - Print a string character by character to the standard error stream.
 * @str: The string to print to the standard error stream.
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Write a character to the standard error stream with buffering.
 * @character: The character to write to stderr.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * _putfd - Write a character to a file descriptor with buffering.
 * @character: The character to write.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: Always returns 1.
 */
int _putfd(char character, int file_descriptor)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 *_putsfd - Write a string to a specified file descriptor
 *          character by character.
 * @input_string: The string to write to the file descriptor.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *input_string, int fd)
{
	int characters_written = 0;

	if (!input_string)
		return (0);
	while (*input_string)
	{
		characters_written += _putfd(*input_string++, fd);
	}
	return (characters_written);
}
