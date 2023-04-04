/**
* @file Entree_Sortie.c
* Fichier de l'interface graphique
* du quadtree
* @author Claire SALLE
* @author Rayane NASSIB
* @date 16/04/2023
*/

#include "../include/Entree_Sortie.h"


void init_fenetre(){
    MLV_create_window("QuadTree", "", TAILLE_FENETRE, TAILLE_FENETRE);
}

Point recupPointClic(){
    Point S;
    int x,y;
    float x_nouv, y_nouv;

    /* Récuperer les coordonnées */
    MLV_wait_mouse(&x, &y);

    /* En faire des float */
    x_nouv = x + (rand() % 9999999) / 10000000.0;
    y_nouv = y + (rand() % 9999999) / 10000000.0;
    
    /* Remplissage du point */
    S.x = x_nouv;
    S.y = y_nouv;

    return S;
}

void afficherPoint(Point point) {
    MLV_draw_filled_circle(point.x, point.y, 2, MLV_COLOR_WHITE);
    MLV_update_window();
    return;
}

void fermeture_fenetre() {
    MLV_wait_seconds(5);
    MLV_free_window();
}
