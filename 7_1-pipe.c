/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   7_1-pipe.c
 * Author: sapk
 *
 * Created on 2 décembre 2016, 11:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define IN 1
#define OUT 0

/*
 * 
 */
int main(int argc, char** argv) {
    int pid, p[2];
    pid = fork();
    pipe(p);
    if (pid != 0) { /* Processus Pere */
        /* Parent process closes up output side of pipe */
        //close(p[OUT]);
        //dup(p[0]);
        //dup2(STDOUT_FILENO, p[0]); //Send stdout to pipe
        //close(STDOUT_FILENO); //Close stdout
        //dup(p[IN]);
        dup2(p[IN],STDOUT_FILENO);
        printf("Ceci est un test !\n");
        printf("Ceci est un test 2 !\n");
        //close(p[IN]);
        wait(NULL);
    } else { /* Processus Fils */
        /* Child process closes up input side of pipe */
        char buf[100];
        //close(p[IN]);
        close(STDIN_FILENO);
        dup2(STDIN_FILENO,p[OUT]); //Pipe to stdin
        dup2(STDOUT_FILENO,p[OUT]); //Pipe to stdout
        //close(p[OUT]);
        /*
        for (;;) {
            int n = read(STDIN_FILENO, buf, sizeof (buf));
            printf("Received %s", buf);
            //sleep(1);
        }
        */
        exit(EXIT_SUCCESS);
    }
    return (EXIT_SUCCESS);
}

