#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buf[100]; // Set a reasonable initial buffer size

    printf("$");

    if (scanf("%99[^\n]", buf) == 1) {
        printf("Your name is: %s\n", buf);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
