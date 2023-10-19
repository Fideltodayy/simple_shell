#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @ol_sz: byte size of previous block
 * @nw_siz: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int ol_sz, unsigned int nw_siz)
{
	char *p;

	if (!ptr)
		return (malloc(nw_siz));
	if (!nw_siz)
		return (free(ptr), NULL);
	if (nw_siz == ol_sz)
		return (ptr);

	p = malloc(nw_siz);
	if (!p)
		return (NULL);

	ol_sz = ol_sz < nw_siz ? ol_sz : nw_siz;
	while (ol_sz--)
		p[ol_sz] = ((char *)ptr)[ol_sz];
	free(ptr);
	return (p);
}