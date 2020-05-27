#ifndef BIBLIO_ZONE_H
# define BIBLIO_ZONE_H 

#include "Liste_case.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "API_Gene_instance.h"
#include "API_Grille_txt.h"
#include "Liste_case.h"

typedef struct {
    int dim;
    int nbcl;
    
    ListeCase Lzsg;
    ListeCase *B;
    int **App;
} S_Zsg;

#include "graphe_zone.h"
#include "Entete_Fonctions.h"

void init_Zsg(S_Zsg *Zsg,int dim, int nbcl);

void ajoute_Zsg(S_Zsg *Zsg, int i, int j);

void ajoute_Bordure(S_Zsg *Zsg,int i, int j, int cl);

int appartient_Zsg(S_Zsg *Zsg,int i,int j);

int appartient_Bordure(S_Zsg *Zsg,int i, int j, int cl);

int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

int case_dans_liste(int i, int j, ListeCase *L);

void affiche_liste(ListeCase *L);
void affiche_Zsg(S_Zsg *Z);
void affiche_Bordure(S_Zsg *Z,int cl);

#endif