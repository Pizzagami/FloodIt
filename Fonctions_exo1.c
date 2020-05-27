#include "Entete_Fonctions.h"

/* Fonction récursive pour trouve zone */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L)
{
    if (test_liste_vide(L))
        ajoute_en_tete(L,i,j);
    
    /* Parcours des cases du haut */
    if (i+1 <= dim-1 && M[i][j] == M[i+1][j] && !case_dans_liste(i+1, j, L))
	{
        ajoute_en_tete(L, i+1, j);
		(*taille) = (*taille) + 1;
        trouve_zone_rec(M,dim,i+1,j,taille,L);
	}
    /* Parcours des cases du bas */
    if (i-1 >= 0 && M[i][j]== M[i-1][j] && !case_dans_liste(i-1, j, L))
	{
		ajoute_en_tete(L, i-1, j);
        (*taille) = (*taille) + 1;
		trouve_zone_rec(M,dim,i-1,j,taille,L);
	}
    /* Parcours des cases de droite */
    if (j+1 <= dim-1 && M[i][j] == M[i][j+1] && !case_dans_liste(i, j+1, L))
	{
		ajoute_en_tete(L, i, j+1);
		(*taille) = (*taille) + 1;
		trouve_zone_rec(M,dim,i,j+1,taille,L);
	}
    /* Parcours des cases de gauche */
    else if (j-1 >= 0 && M[i][j] == M[i][j-1] && !case_dans_liste(i, j-1, L))
	{
		ajoute_en_tete(L, i, j-1);
		(*taille) = (*taille) + 1;
		trouve_zone_rec(M,dim,i,j-1,taille,L);
	}
}

/* Fonction impérative pour trouve_zone */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, ListeCase *L)
{
    /* Nous allons utiliser une pile d'appels pour dérécursifier notre fonction précédente  */
    ListeCase *p = (ListeCase *)malloc(sizeof(ListeCase)); 
    init_liste(p);
    ajoute_en_tete(L,i,j);
    ajoute_en_tete(p,i,j);

    while (!test_liste_vide(p)){
        enleve_en_tete(p,&i,&j); /* On dépile */
        if (i+1 <= dim-1 && M[i][j] == M[i+1][j] && !case_dans_liste(i+1, j, L))
        {
            ajoute_en_tete(L, i+1, j);
            (*taille) = (*taille) + 1;
            ajoute_en_tete(p,i+1,j); /* On empile */
        }
        if (i-1 >= 0 && M[i][j]== M[i-1][j] && !case_dans_liste(i-1, j, L))
        {
            ajoute_en_tete(L, i-1, j);
            (*taille) = (*taille) + 1;
            ajoute_en_tete(p,i-1,j);
        }
        if (j+1 <= dim-1 && M[i][j] == M[i][j+1] && !case_dans_liste(i, j+1, L))
        {
            ajoute_en_tete(L, i, j+1);
            (*taille) = (*taille) + 1;
            ajoute_en_tete(p,i,j+1);
        }
        else if (j-1 >= 0 && M[i][j] == M[i][j-1] && !case_dans_liste(i, j-1, L))
        {
            ajoute_en_tete(L, i, j-1);
            (*taille) = (*taille) + 1;
            ajoute_en_tete(p,i,j-1);
        }
    }
}

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
    int cpt = 0;
    ListeCase* L = (ListeCase*)malloc(sizeof(ListeCase));
    init_liste(L);
    int taille = 1;
    int i,j;
    trouve_zone_rec(M,dim,0,0,&taille,L);
    srand(time(NULL));
    while (taille != (dim*dim)){
        /* La zone n'occupe pas toute la grille */
        int c_alea = rand()%nbcl; /* On tire aléatoirement */
        int c = M[0][0];
        if (c_alea != c) /* Si ce n'est pas la couleur de la zone, j'incrémente le compteur */
        {
            cpt ++;
            Elnt_liste *cour;
            cour = (*L);
            /* Pour déterminer la nouvelle zone, je mets les couleurs de ma zone précédente à la couleur tirée aléatoirement */
            while (cour != NULL)
            {
                M[cour->i][cour->j] = c_alea; 
                cour = cour->suiv;
            }
            detruit_liste(L);
            taille = 1;
            trouve_zone_rec(M,dim,0,0,&taille,L);
            Elnt_liste *tmp;
            tmp = (*L);
            /* On met à jour la zone finale */
            while (tmp != NULL)
            {
                M[tmp->i][tmp->j] = c_alea;
                tmp = tmp->suiv;
            }
            /* Procédé d'affichage */
            if (aff == 1) {
                for (i=0;i<dim;i++){
                    for (j=0;j<dim;j++)
                        Grille_attribue_couleur_case(G,i,j,M[i][j]);
                }
                Grille_redessine_Grille(G);
            }
        }
    }
    return cpt;    
}

/* Même fonction que la précédente mais en version impérative pour trouve zone rec */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
    int cpt = 0;
    ListeCase* L = (ListeCase*)malloc(sizeof(ListeCase));
    init_liste(L);
    int taille = 1;
    int i,j;
    trouve_zone_imp(M,dim,0,0,&taille,L);
    srand(time(NULL));
    while (taille != (dim*dim)){
        int c_alea = rand()%nbcl;
        int c = M[0][0];
        if (c_alea != c)
        {
            cpt ++;
            Elnt_liste *cour;
            cour = (*L);
            while (cour != NULL)
            {
                M[cour->i][cour->j] = c_alea;
                cour = cour->suiv;
            }
            detruit_liste(L);
            taille = 1;
            trouve_zone_imp(M,dim,0,0,&taille,L);
            Elnt_liste *tmp;
            tmp = (*L);
            while (tmp != NULL)
            {
                M[tmp->i][tmp->j] = c_alea;
                tmp = tmp->suiv;
            }
            if (aff == 1) {
                for (i=0;i<dim;i++){
                    for (j=0;j<dim;j++)
                        Grille_attribue_couleur_case(G,i,j,M[i][j]);
                }
                Grille_redessine_Grille(G);
            }
        }
    }
    return cpt;    
}

/* La fonction de jeu améliorer */
int strequence_aleatoire_rapide(int **M,Grille *G, int dim,int nbcl, S_Zsg *Z, int aff)
{
    init_Zsg(Z,dim,nbcl);
    int taille = agrandit_Zsg(M,Z,M[0][0],0,0);
    int cpt = 0;
    int i,j;
    int fin = 0;
    while (fin == 0)
    {
        int cl = rand()%nbcl;
        int c = M[0][0];
        if (c != cl)
        {
            cpt ++;
            Elnt_liste *cour;
            cour = (Z->Lzsg);
            while (cour != NULL) /* Comme pour les deux autres fonctions, on met à jour la matrice pour agrandir la zone */
            {
                M[cour->i][cour->j] = cl;
                cour = cour->suiv;
            }
            Elnt_liste *tmp;
            tmp = (Z->B)[cl];
            /* Le reste de la fonction, correspond à ce qui était indiqué dans le poly */
            while (tmp != NULL)
            {
                taille = agrandit_Zsg(M,Z,cl,tmp->i,tmp->j);
                tmp = tmp->suiv;
            }
            ListeCase *B = Z ->B;
            detruit_liste(B+cl);
            /* Procesus d'affichage */
            if (aff == 1) {
                for (i=0;i<dim;i++){
                    for (j=0;j<dim;j++)
                        Grille_attribue_couleur_case(G,i,j,M[i][j]);
                }
                Grille_redessine_Grille(G);
            }
            fin = 1;
            for (i=0;i<dim;i++)
            {
                for (j=0;j<dim;j++)
                {
                    if (!appartient_Zsg(Z,i,j))
                        fin = 0;
                }
            }
        }
    }

    return cpt;
}



