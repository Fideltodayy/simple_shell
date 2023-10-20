#include "main.h"

/**
 * bfree - Free memory associated with a pointer and set it to NULL
 * @ptr: A pointer to a pointer to the memory to be freed
 *
 * Return: 1 if successful, 0 if the pointer is NULL
 */
int bfree(void **ptr)
{
	/* Check if 'ptr' and '*ptr' is not NULL (valid pointer) */
	if (ptr && *ptr)
	{
		/* Free the memory pointed to by '*ptr' */
		free(*ptr);

		/* Set '*ptr' to NULL to avoid a dangling pointer */
		*ptr = NULL;

		/* Return 1 to indicate success (memory was freed) */
		return (1);
	}

	/* Return 0 to indicate failure (no memory was freed) */
	return (0);
}
