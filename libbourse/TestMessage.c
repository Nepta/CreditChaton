#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "message.h"
#include "alea.h"

/**
 * Programme de test des fonctions messages
 */
int main(int argc, char **argv)
{
  char emeteur[255], type[255], action[255], 
    valeur[255];
  int erreur;

  aleainit();
  // Creation d'un ordre demandant l'achat d'un nombre aléatoire
  // d'actions
  
  sprintf(valeur,"%d",alea(1,50));
  printf("L'ordre porte sur %s actions\n",valeur);
  
  char *msg = message("0033125218", "Achat", "0001000012", valeur);
  printf("Le message est : *%s*\n", msg);

  erreur = decoupe(msg, emeteur, type, action, valeur);
  if (erreur) {
    printf("Erreur de découpage!!\n");
    exit(0);
  }

  printf("L'emeteur est : %s\n", emeteur);
  printf("Le type est : %s\n", type);
  printf("L'action est : %s\n", action);
  printf("La valeur est : %s\n", valeur);
  return 0;
}

