/**
* @file Moteur.c
* Fichier du moteur du quadtree
* @author Claire SALLE
* @author Rayane NASSIB
* @date 16/04/2023
*/

#include "../include/Moteur.h"

void remplissage_tab_cell(Cellule *tab_cell, Point* tab_point) {
    for (int i = 0; i < NB_POINT_TOTAL; i++) tab_cell[i].point = &(tab_point[i]);
}

int init_quadtree(QuadTree *quadtree) {
    quadtree->tab_noeud = (Noeud*) malloc(sizeof(Noeud)*(TAILLE_FENETRE/TAILLE_FEUILLE));
    if (NULL == quadtree->tab_noeud) return 0;
    quadtree->taille = TAILLE_FENETRE/TAILLE_FEUILLE;
    quadtree->dernier = -1;
    return 1;
}

Point generation_aleatoire(){
    Point point;
    point.x = rand() % TAILLE_FENETRE;
    point.y = rand() % TAILLE_FENETRE;
    point.x += (rand() % 9999999) / 10000000.0;
    point.y += (rand() % 9999999) / 10000000.0;
    return(point);
}

void ajout_premier_noeud_quadtree(QuadTree *quadtree, Point *p) {
    quadtree->tab_noeud[0].nb_couvre = 1;
    
    quadtree->tab_noeud[0].bas_droit.x = TAILLE_FENETRE;
    quadtree->tab_noeud[0].bas_droit.y = TAILLE_FENETRE;
    quadtree->tab_noeud[0].lst_cell_noeud->point = p;
    quadtree->tab_noeud[0].lst_cell_noeud->suiv = NULL;
    quadtree->dernier++;
}

void ajout_liste_chaine_point(Noeud* noeud, Cellule *tab_cell, int num_point) {
    Cellule *cur;
    assert(NULL != noeud);
    assert(noeud->nb_couvre < NB_POINT_FEUILLE);
    cur = noeud->lst_cell_noeud;
    for (int i = 0; i < noeud->nb_couvre; i++) {
        if (NULL == cur) {
            cur = &(tab_cell[num_point]);
            return;
        }
        cur = cur->suiv;
    }
}


