#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t n = 0;
    char *buf = (char *)malloc(n * sizeof(char)); // Allocate memory for the buffer

    if (buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    printf("Enter your name:");

    if (fgets(buf, n, stdin) != NULL) {
        printf("Your name is: %s\n", buf);
    } else {
        printf("Error reading input.\n");
    }

    free(buf);

    return 0;
}
