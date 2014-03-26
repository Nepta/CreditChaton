#include <stdlib.h>
#include <stdio.h>
#include "PrixAchatVente.h"

int main(int argc, char ** argv){
  int mode;
  double VI;
  int Stock,Qte;
  if(argc < 5){
    printf("usage: %s mode ValeurIntrinseque Stock QuantiteDemandee\n" , argv[0]);
    printf("\t ou mode=0 correspond a un prix d'achat\n");
    printf("\t et mode = 1 a un prix de vente\n");
    exit(0);
  }
  mode = atoi(argv[1]);
  VI = atoi(argv[2]);
  Stock = atoi(argv[3]);
  Qte = atoi(argv[4]);
  
  if(mode == 0){
    printf("Prix d'achat de %d actions pour un stock de %d et une valeur intrinseque de %lg:\n ", Qte, Stock, VI);
    printf("%lg\n", PrixAchat(VI, Stock, Qte)); 
  } else if (mode == 1){
    printf("Prix de vente de %d actions pour un stock de %d et une valeur intrinseque de %lg:\n ", Qte, Stock, VI);
    printf("%lg\n", PrixVente(VI, Stock, Qte));
  } else 
    printf("Mauvaise valeur de mode\n");
}
