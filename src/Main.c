#include "../include/Moteur.h"
#include "../include/Entree_Sortie.h"
#include <stdlib.h>
#include <time.h>

int main() {
    Point *tab_point;
    Distribution d = SOURIS;
    QuadTree quadtree;
    Cellule *tab_cell; 
    
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
    remplissage_tab_cell(tab_cell, tab_point);


    /* Initialisation du QuadTree */
    if(init_quadtree(&quadtree) == 0) {
        free(tab_point);
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
        }
        /* affichage du point */
        afficherPoint(tab_point[i]);
    }


    fermeture_fenetre();

    return 0;
}
