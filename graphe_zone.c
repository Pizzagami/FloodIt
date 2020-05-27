#include "graphe_zone.h"

void ajoute_liste_sommet(Cellule_som* cs, Sommet *s)
{
    Cellule_som *nvl_cell = (Cellule_som*) malloc(sizeof(Cellule_som));
    nvl_cell->sommet = s;
    nvl_cell ->suiv = cs;
    cs = nvl_cell;
}

/*detruit une liste chaîn ́ee de Cellule som SANS d ́etruire les sommets point ́ees par cette liste*/
void detruire_liste_somme(Cellule_som *cs)
{
    Cellule_som *tmp = NULL;
    while (cs != NULL)
    {
        tmp = cs -> suiv;
        free(cs);
        cs = tmp;
    }
}
void ajoute_voisin(Sommet *s1, Sommet *s2)
{
    ajoute_liste_sommet(s1->sommet_adj,s2);
    ajoute_liste_sommet(s2->sommet_adj,s1);
}
int adjacent(Sommet *s1,Sommet *s2)
{
    Cellule_som *tmp = s1->sommet_adj;
    int s1_check = 0;
    int s2_check = 0;
    while (tmp)
    {
        if ((tmp->sommet)->num == s2->num) //je compare leur numéro car on ne peut comparer deux structures
            s1_check = 1;
        tmp = tmp ->suiv;
    }
    if (s1_check==0)
        return 0;
    Cellule_som *tmp2 = s2->sommet_adj;
    while (tmp2)
    {
        if ((tmp->sommet)->num == s1->num)
            s2_check = 1;
        tmp2 = tmp2 ->suiv;
    }
    if (s2_check == 1)
        return 1;
    return 0;
    
}
void creer_graphe_zone(int **M, int dim, int nbcl)
{
    int num = 0; //mon numéro de sommet
    int taille = 0;
    int i,j;
    Graphe_zone *G = (Graphe_zone *)malloc(sizeof(Graphe_zone));
    G -> nbsom = 0;
    G -> som = NULL;
    G -> mat = (Sommet ***)malloc(sizeof(Sommet));
    for (i=0;i<dim;i++)
        for (j=0;j<dim;j++)
            G->mat[i][j] = NULL;
    for (i=0;i<dim;i++){
        for (j=0;j<dim;j++)
        {
            if (G->mat[i][j] == NULL){
                Sommet *s = (Sommet *)malloc(sizeof(Sommet));
                num ++;
                s->num = num;
                s -> cl = M[i][j];
                init_liste(&(s->cases));
                s -> nbcase_som = 0;
                s -> sommet_adj = NULL;
                trouve_zone_rec(M,dim,i,j,&taille,&(s->cases));
                Elnt_liste *cour;
                cour = (s->cases);
                while (cour != NULL)
                {
                    G->mat[cour->i][cour->j] = s;
                    cour = cour->suiv;
                }
            }
        }
    }
    for (i=0;i<dim-1;i++){
        for (j=0;j<dim-1;j++)
        {
            if ((G->mat[i][j]->num != G->mat[i][j+1]->num) && !adjacent(G->mat[i][j],G->mat[i][j+1]))
                ajoute_voisin(G->mat[i][j],G->mat[i][j+1]);
        }
    }         
}
void affichage(Graphe_zone *G)
{
    Cellule_som *tmp = G->som;
    printf("Graphe de la zone : \n");
    while (tmp)
    {
        printf("(%d)\t",tmp->sommet->num);
        tmp = tmp->suiv;
    }
    printf("\n");
}