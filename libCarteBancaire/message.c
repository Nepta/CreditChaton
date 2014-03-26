#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Decoupe du message 
 * Retourne 1 si il n'y a pas eu de probl�me
 * Retourne 0 si il y a eu un probl�me
 * ATTENTION:
 *   Les variables emeteur, destinataire, commande, identifiant
 *   et sms doivent �tre allou�es avant l'appel � decoupe
 */
int decoupe(char *message,      /* Source a d�couper */
	    char *cb,           /* no de carte concernee */
	    char *type,         /* Type du message */
	    char *valeur        /* Valeur associ�e au message */
	    )
{
  int nb=sscanf(message, "|%[^|]|%[^|]|%[^|]|\n", 
	 cb, type, valeur);
  if (nb == 3)
    return 1;
  else 
    return 0;
}

/** 
 * Construction du message
 * Retourne le message construit suivant le protocole
 * a partir des arguments
 * Le message est allou� dans la fonction
 */
char* message(char *cb, char *type, char * valeur)
{
  int longueur = strlen(cb) + strlen(type) + strlen(valeur) + 1 + 5 + 1;
  char *mess = calloc(longueur,sizeof(char));

  if (mess == NULL)
    return NULL;
  
  sprintf(mess, "|%s|%s|%s|\n", cb, type, valeur);

  return mess;
}
