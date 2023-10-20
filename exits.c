#include "main.h"

/**
 **_strncpy - Copy up to 'n' characters from 'source' to 'destination'.
 *@destination: The destination string where characters are copied to.
 *@source: The source string from which characters are copied.
 *@n: The maximum number of characters to copy.
 *Return: A pointer to the 'destination' string.
 */
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenate up to 'n' characters from 'source' to
 *            the end of 'destination'.
 * @destination: The destination string to which characters are appended.
 * @source: The source string from which characters are appended.
 * @n: The maximum number of characters to append.
 *Return: A pointer to the 'destination' string.
 */
char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 * _strchr - Locate the first occurrence of a character in a string.
 * @string: The string to search for the character.
 * @character: The character to find in the string.
 *
 * Return: A pointer to the first occurrence of 'character'
 *         in 'string' or NULL if not found.
 */
char *_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
