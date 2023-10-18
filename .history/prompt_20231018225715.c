#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t n = 0;
	char *buf = NULL;

	printf("Enter your name:");
	getline(&buf , &n , stdin);
	printf("Your name is: %s\n", buf);

	free(buf);

	return(0);
}
