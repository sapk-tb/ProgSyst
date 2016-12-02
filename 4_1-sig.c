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

void (*sig_avant)(int);		/* pour la question 4.3 */

void message1(int n) {
  printf("message numéro 1\n");
}
void message2(int n) {
  printf("message numéro 2\n");
}
void swMessageTo1(int n);
void swMessageTo2(int n);

void swMessageTo1(int n) {
  signal(SIGINT,message1);
  printf("Switching to numéro 1\n");
  signal(SIGQUIT,swMessageTo2);
}
void swMessageTo2(int n) {
  signal(SIGINT,message2);
  printf("Switching to numéro 2\n");
  signal(SIGQUIT,swMessageTo1);
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
  
  signal(SIGILL,hdl_sys1);
  signal(SIGQUIT,swMessageTo2);
  signal(SIGINT,message1);
  
  travail();
}
