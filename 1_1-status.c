/*
 * Auteur(s):
 *
 * Cet programme refait ce que fait la commande "ls". Il donne des
 * informnations sur les caracteristiques de fichiers dont le nom est passe
 * en parametre.
 *
 * Utilisation de la primitive stat(2) et de la fonction getpwuid(3).
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>


/* Petite fonction qui se charge d'envoyer les messages d'erreur
   et qui ensuite "suicide" le processus. */

void erreur_grave(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

/* Fonction principale (fournie avec erreur(s?)) */

int main(int argc, char **argv) {
  struct stat *buffer;
  int r;

  buffer = malloc(sizeof (struct stat));
  r = stat(argv[1], buffer);
  if (r < 0)
    erreur_grave("Stat");

  printf("Fichier %s:  mode: %X  Taille: %ld  Proprietaire: %u\n", argv[1], buffer->st_mode, buffer->st_size, buffer->st_uid);
  //*
  struct passwd *user, *user2;
  //user = malloc(sizeof (struct passwd));
  user = getpwuid(buffer->st_uid);
  printf("Fichier %s:  mode: %X  Taille: %ld  Proprietaire: %s %d\n", argv[1], buffer->st_mode, buffer->st_size, user->pw_name, user);
  
  user2 = getpwuid(0);
  printf("Proprietaire 1 : %s, Proprietaire 2 : %s %d %d\n", user->pw_name, user2->pw_name, user, user2);
  
  exit(EXIT_SUCCESS);
}
