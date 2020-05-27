#include "biblio_zone.h"


void affiche_liste(ListeCase *L)
{
    printf("Liste = [");
    Elnt_liste *cour;
    cour = (*L);
    while (cour != NULL)
    {
        printf("(%d,%d), ",cour->i,cour->j);
        cour = cour->suiv;
    }
    printf("]\n");
}
void init_Zsg(S_Zsg* Zsg,int dim, int nbcl)
{
    Zsg -> dim = dim;
    Zsg -> nbcl = nbcl;
    ListeCase *L = (ListeCase *)malloc(sizeof(ListeCase));
    init_liste(L);
    Zsg -> Lzsg = *L;
    ListeCase *B = (ListeCase *)malloc(nbcl*sizeof(ListeCase));
    Zsg -> B = B;
    (Zsg->App)=(int **) malloc(sizeof(int*)*dim);
    int i;
    for (i=0;i<dim;i++){
        (Zsg->App)[i]=(int*) malloc(sizeof(int)*dim);
        if ((Zsg->App)[i]==0) printf("Pas assez d'espace mémoire disponible\n");
    }
}
void ajoute_Zsg(S_Zsg *Zsg, int i, int j)
{
    ajoute_en_tete(&(Zsg->Lzsg),i,j);
}
void ajoute_Bordure(S_Zsg *Zsg,int i, int j, int cl)
{
    ListeCase *B = Zsg ->B;
    ajoute_en_tete(B+cl,i,j);
}
int appartient_Zsg(S_Zsg *Zsg,int i,int j)
{
    Elnt_liste *cour;
    cour = Zsg->Lzsg;
    while (cour != NULL)
    {
        if (cour->i == i && cour->j == j)
        {
            return 1;
        }
        cour = cour->suiv;
    }
    return 0;
}
int appartient_Bordure(S_Zsg *Zsg,int i, int j, int cl)
{
    Elnt_liste *cour;
    cour = (Zsg->B)[cl];
    while (cour != NULL)
    {
        if (cour->i == i && cour->j == j)
        {
            return 1;
        }
        cour = cour->suiv;
    }
    return 0;
}
void affiche_Zsg(S_Zsg *Z)  
{
    affiche_liste(&(Z->Lzsg));
}
void affiche_Bordure(S_Zsg *Z,int cl)
{
    ListeCase L = (Z->B)[cl];
    affiche_liste(&L);
}
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l)
{
    /*Cette fonction reprend les principes du trouve zone version impérative */
    int dim = Z->dim;
    int taille = 1;
    ListeCase *p = (ListeCase *)malloc(sizeof(ListeCase)); /*Ceci est ma pile */
    init_liste(p);
    ajoute_Zsg(Z,k,l);
    ajoute_en_tete(p,k,l);
    int cl2;
    while (!test_liste_vide(p)){
        enleve_en_tete(p,&k,&l);
        if (k+1 <= dim-1 && !appartient_Zsg(Z,k+1,l))
        {
            if (M[k+1][l] == cl){
                ajoute_Zsg(Z, k+1, l);
                taille ++;
                ajoute_en_tete(p,k+1,l);
            }
            else { 
                cl2 = M[k+1][l];
                if (!appartient_Bordure(Z,k+1,l,cl2))
                    ajoute_Bordure(Z,k+1,l,cl2);
            }
        }
        if (k-1 >= 0 && !appartient_Zsg(Z,k-1,l))
        {
            if (M[k-1][l] == cl){
                ajoute_Zsg(Z, k-1, l);
                taille ++;
                ajoute_en_tete(p,k-1,l);
            }
            else { 
                cl2 = M[k-1][l];
                if (!appartient_Bordure(Z,k-1,l,cl2))
                    ajoute_Bordure(Z,k-1,l,cl2);
            }
        }
        if (l+1 <= dim-1 && !appartient_Zsg(Z,k,l+1))
        {
            if (M[k][l+1] == cl){
                ajoute_Zsg(Z, k, l+1);
                taille ++;
                ajoute_en_tete(p,k,l+1);
            }
            else { 
                cl2 = M[k][l+1];
                if (!appartient_Bordure(Z,k,l+1,cl2))
                    ajoute_Bordure(Z,k,l+1,cl2);
            }
        }
        else if (l-1 >= 0 && !appartient_Zsg(Z,k,l-1))
        {
            if (M[k][l-1] == cl){
                ajoute_Zsg(Z,k,l-1);
                taille ++;
                ajoute_en_tete(p,k,l-1);
            }
            else { 
                cl2 = M[k][l-1];
                if (!appartient_Bordure(Z,k,l-1,cl2))
                    ajoute_Bordure(Z,k,l-1,cl2);
            }
        }
    }
    return taille;
}