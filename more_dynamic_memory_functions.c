#include "main.h"

/**
 * _memset - Fill a memory block with a specific byte value
 * @s: A pointer to the memory area to be filled
 * @byte_value: The byte value to be set in the memory area
 * @num_bytes: The number of bytes to be set to the byte value
 *
 * Return: A pointer to the filled memory area 's'
 */
char *_memset(char *s, char byte_value, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
	s[i] = byte_value;

	return (s);
}

/**
 * ffree - Free an array of pointers and the array itself
 * @pp: A pointer to an array of pointers to be freed
 */
void ffree(char **pp)
{
	char **array = pp;

	if (!pp)
	return;

	while (*pp)
		free(*pp++);

	free(array);
}

/**
 * _realloc - Reallocate a block of memory with a new size
 * @old_block: A pointer to the old block of memory
 * @old_size: The current size of the block
 * @new_size: The new size for the block
 *
 * Return: A pointer to the reallocated block of memory
 */
void *_realloc(void *old_block, unsigned int old_size, unsigned int new_size)
{
	char *new_block;

	if (!old_block)
		return (malloc(new_size));
	if (!new_size)
	{
		free(old_block);
		return (NULL);
	}
	if (new_size == old_size)
		return (old_block);

	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_block[old_size] = ((char *)old_block)[old_size];

	free(old_block);
	return (new_block);
}

