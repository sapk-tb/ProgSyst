/* 
 * Auteur(s):
 */

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//#define SIGILL 4
//#define SIGQUIT 4
//#define SIGINT 2

void (*sig_avant)(int); /* pour la question 4.3 */

void message1(int n) {
    printf("message numéro 1\n");
}

void message2(int n) {
    printf("message numéro 2\n");
}

void swMessage(int n) {
    sig_avant = signal(SIGINT, sig_avant);
}

void hdl_sys1(int n) {
    printf("hdl_sys1: Signal recu: %d\n", n);
}

void travail() {
    /* Je travaille tres intensement !    */
    /* Ne cherchez pas a comprendre ;-) */
    /* Il n'y a rien a modifier ici     */
    const char msg[] = "-\\|/";
    const int sz = strlen(msg);
    int i = 0;

    for (;;) {
        write(STDOUT_FILENO, "\r", 1);
        usleep(100000);
        write(STDOUT_FILENO, " => ", 4);
        write(STDOUT_FILENO, &msg[i++], 1);
        if (i == sz) i = 0;
    }
}
void travail() __attribute__((noreturn));

/* Petit raffinement pour le compilateur: cette fonction ne termine pas */

int main() {
    printf("PID: %d\n", getpid());


    signal(SIGILL, hdl_sys1);
    signal(SIGQUIT, swMessage);
    //signal(SIGINT,message1);
    sig_avant = message2;
    struct sigaction sa;

    sa.sa_handler = message1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("Some error occur");
    }

    travail();
}
