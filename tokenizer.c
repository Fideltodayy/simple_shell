#include "main.h"

/**
 * strtow - Split a string into an array of substrings.
 * @str: The string to split.
 * @delim: The delimiter string for splitting.
 *
 * Return: A dynamically allocated array of substrings,
 *         or NULL on failure.
 */
char **strtow(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **word_array;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	word_array = malloc((1 + numwords) * sizeof(char *));
	if (!word_array)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		word_array[j] = malloc((k + 1) * sizeof(char));
		if (!word_array[j])
		{
			for (k = 0; k < j; k++)
				free(word_array[k]);
			free(word_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			word_array[j][m] = str[i++];
		word_array[j][m] = 0;
	}
	word_array[j] = NULL;
	return (word_array);
}

/**
 * strtow_2 - Split a string into words based on a delimiter character
 * @str: The input string to be split
 * @d: The delimiter character used to split the string
 *
 * Return: An array of strings containing the split words, or NULL on failure
 */
char **strtow_2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **word_array;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	word_array = malloc((1 + numwords) * sizeof(char *));
	if (!word_array)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		word_array[j] = malloc((k + 1) * sizeof(char));
		if (!word_array[j])
		{
			for (k = 0; k < j; k++)
				free(word_array[k]);
			free(word_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			word_array[j][m] = str[i++];
		word_array[j][m] = 0;
	}
	word_array[j] = NULL;
	return (word_array);
}
