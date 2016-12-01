
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    extern char **environ;
    char *current;
    int i = 0;
    while ((current = environ[i]) != NULL) {
        printf("%s \n", current);
        i++;
    }


    exit(EXIT_SUCCESS);
}
