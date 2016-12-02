/* 
 * Auteur(s):
 */

#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void travail() {
    /* Je travaille tres intensement !    */
    /* Ne cherchez pas a comprendre ;-) */
    /* Il n'y a rien a modifier ici     */
    for (;;) {
        printf("%s", random() > RAND_MAX >> 1 ? "." : "\b \b");
        fflush(stdout);
        usleep(100000);
    }
}
void travail() __attribute__((noreturn));

/* Petit raffinement pour le compilateur: cette fonction ne termine pas */

void fin(int n) {
    printf("Catch signal %d\n",n);
    wait(NULL);
    printf("The end !\n");
    exit(EXIT_SUCCESS);
}

int main() {
    int pid, longueur;
    char tab[256];

    int r;
    pid = fork();

    if (pid != 0) { /* Processus Pere */
        signal(SIGCHLD, fin);
        travail();
    } else { /* Processus Fils */
        sleep(3);
        printf("Ahrg!!! je suis le fils et je meurs\n");
        //raise(SIGINT);
        //killpg(getpgrp(), SIGINT);
        exit(EXIT_SUCCESS);
    }
}
