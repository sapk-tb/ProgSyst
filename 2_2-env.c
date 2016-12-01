
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *current;
    if ((current = getenv(argv[1])) != NULL) {
        printf("%s\n", current);
    }
    exit(EXIT_SUCCESS);
}

