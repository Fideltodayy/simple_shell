#include "main.h"

/**
 * _strlen - Calculate the length of a string
 * @s: The input string
 *
 * Return: The length of the string, or 0 if the string is NULL
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * _strcmp - Compare two strings lexicographically
 * @str1: The first string to be compared
 * @str2: The second string to be compared
 *
 * Return:
 * - 0 if the strings are equal
 * - A positive value if str1 is greater than str2
 * - A negative value if str1 is less than str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Check if a string starts with a specified substring
 * @haystack: The string to check
 * @needle: The substring to check for
 *
 * Return:
 * - A pointer to the character following the substring if found
 * - NULL if the string does not start with the substring
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenate (append) one string to another
 * @destination: The destination string to which src is appended
 * @source: The source string to be appended to dest
 *
 * Return: A pointer to the destination string (dest)
 */
char *_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (result);
}
