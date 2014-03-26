

double PrixAchat(double VInit, int Stock, int Qte)
  /* ou VInit est la valeur initial de l'action 
     ou Stock est la quantite d'action offerte 
     ou Qte est la qte d'action dont on veut connaitre le prix d'achat
     retourne la valeur total d'achat de Qte actions dont le prix
     initial etait VInit et le stock courant est de Stock */ 
{
  int i;
  double facteur =0.0;

  // Verification de la validite des parametres
  if( (VInit <= 0) || (Stock <= 0 ) || (Qte <= 0) || (Qte > Stock) )
    return -1;

  for(i = 0; i < Qte; i++){
    facteur += 1/(double)(Stock - i);
  }
  return VInit*facteur;

}

double PrixVente(double VInit, int Stock, int Qte)
  /* ou VInit est la valeur initial de l'action
   ou Stock est la quantite d'action offerte
   ou Qte est la qte d'action dont on veut connaitre le prix
   retourne la valeur total de vente de Qte actions dont le prix
   initial etait VInit et le stock courant est de Stock */ 
{
  int i;
  double facteur =0.0;

  // Verification de la validite des parametres
  if( (VInit <= 0) || (Stock <= 0 ) || (Qte <= 0))
    return -1;
 
  for(i = 1; i < Qte+1; i++){
    facteur += 1/(double)(Stock + i);
  }
  return VInit*facteur;
}
