#include "../include/Moteur.h"
#include "../include/Entree_Sortie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    Point *tab_point;
    Distribution d = SOURIS;
    QuadTree quadtree;
    Cellule *tab_cell;
    int res=0;
    
    srand(time(NULL));

    /* Initialisation du tableau de points */
    tab_point = (Point*) malloc(sizeof(Point)*NB_POINT_TOTAL);
    if (NULL == tab_point) exit(EXIT_FAILURE);

    /* Initialisation et remplissage du tableau de cellules */
    tab_cell = (Cellule*) malloc(sizeof(Cellule)*NB_POINT_TOTAL);
    if (NULL == tab_cell) {
        free(tab_point);
        exit(EXIT_FAILURE);
    }


    /* Initialisation du QuadTree */
    if(init_quadtree(&quadtree) == 0) {
        free(tab_point);
        free(tab_cell);
        exit(EXIT_FAILURE);
    }

    init_fenetre();

    /* Remplissage du tableau de points */
    for (int i = 0; i < NB_POINT_TOTAL; i++) {
        switch(d) {
            case ALEATOIRE:
                tab_point[i] = generation_aleatoire();
                break;
            case SOURIS:
                tab_point[i] = recupPointClic();
                break;
            default:
                exit(EXIT_FAILURE);
        }
        /* affichage du point */
        afficherPoint(tab_point[i]);
        /* lien avec tab_cell */
        tab_cell[i].point = tab_point[i];
        /* ajout dans quadtree */
        res = ajout(quadtree.tab_noeud, &tab_cell[i]);
        if(res < 0) {
            printf("avant du coup %d\n", res);
            return 0;
        }
        if (res == 2) quadtree.dernier+=4;
        affiche_quadtree(quadtree);
    }


    fermeture_fenetre();
    free(tab_point);
    free(tab_cell);
    free(quadtree.tab_noeud);

    return 0;
}
