#include <stdio.h>
#include <stdlib.h>

/*
 * Hello World respectant strictement la norme ANSI C (C89 / C90).
 * Date : 21 septembre 2026
 */
int main(int argc, char *argv[])
{
    int i;
    int iterations = 5;

    if (argc > 1) {
        iterations = atoi(argv[1]);
    }

    for (i = 0; i < iterations; i++) {
        printf("Hello World\n");
    }
    return 0;
}
