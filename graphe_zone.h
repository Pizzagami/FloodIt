#ifndef GRAPHE_ZONE_H
#define GRAPHE_ZONE_H 

#include "biblio_zone.h"

typedef struct sommet Sommet;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som{ 
    Sommet *sommet;
    struct cellule_som *suiv;
} Cellule_som;

struct sommet{
    int num; /* Numero du sommet (sert uniquement a l’affichage) */ 
    int cl; /* Couleur d’origine du sommet-zone */
    ListeCase cases; /* Listes des cases du sommet-zone */
    int nbcase_som; /* Nombre de cases de cette liste */
    Cellule_som *sommet_adj; /* Liste des are
    teses pointeurs sur les sommets adjacents */
};

typedef struct graphe_zone{
    int nbsom; /* Nombre de sommets dans le graphe */ 
    Cellule_som *som; /* Liste chainee des sommets du graphe */
    Sommet ***mat; /*Matrice de pointeurs sur les sommets indiquanta quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;

void ajoute_liste_sommet(Cellule_som* cs, Sommet *s);
void detruire_liste_somme(Cellule_som *cs);
void ajoute_voisin(Sommet *s1, Sommet *s2);
int adjacent(Sommet *s1,Sommet *s2);
void creer_graphe_zone(int **M,int dim,int nbcl);
void affichage(Graphe_zone *G);

#endif