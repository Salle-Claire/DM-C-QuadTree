/**
* @file Moteur.c
* Fichier du moteur du quadtree
* @author Claire SALLE
* @author Rayane NASSIB
* @date 16/04/2023
*/

#include "../include/Moteur.h"

int init_quadtree(QuadTree *quadtree) {
    quadtree->tab_noeud = (Noeud*) malloc(sizeof(Noeud)*(TAILLE_FENETRE/TAILLE_FEUILLE)*(TAILLE_FENETRE/TAILLE_FEUILLE));
    if (NULL == quadtree->tab_noeud) return 0;
    quadtree->tab_noeud[0].haut_gauche.x = 0;
    quadtree->tab_noeud[0].haut_gauche.y = 0;
    quadtree->tab_noeud[0].bas_droit.x = TAILLE_FENETRE;
    quadtree->tab_noeud[0].bas_droit.y = TAILLE_FENETRE;
    quadtree->tab_noeud[0].indice = 0;
    quadtree->tab_noeud[0].lst_cell = NULL;
    quadtree->tab_noeud[0].nb_couvre = 0;
    quadtree->taille = TAILLE_FENETRE/TAILLE_FEUILLE;
    quadtree->dernier = 0;
    return 1;
}

Point generation_aleatoire(){
    Point point;
    point.x = rand() % TAILLE_FENETRE;
    point.y = rand() % TAILLE_FENETRE;
    point.x += (rand() % 9999999) / 10000000.0;
    point.y += (rand() % 9999099) / 10000000.0;
    return(point);
}

int test_zone_couvree(int x1, int x2) {
    if ((x2 - x1) < TAILLE_FEUILLE) return 0;
    return 1;
}

Partie_geographique test_partie_geo(Noeud noeud, Point point) {
    Point milieu;
    if(point.x < noeud.haut_gauche.x ||
        point.x > noeud.bas_droit.x ||
        point.y < noeud.haut_gauche.y ||
        point.y > noeud.bas_droit.y) return -1;
    milieu.x =(noeud.haut_gauche.x + noeud.bas_droit.x) / 2;
    milieu.y = (noeud.haut_gauche.y + noeud.bas_droit.y) / 2;
    if(point.x < milieu.x) {
        if (point.y < milieu.y) {
            return HAUT_GAUCHE;
        }
        else return BAS_GAUCHE;
    } else {
        if (point.y < milieu.y) return HAUT_DROIT;
        else return BAS_DROIT;
    }
}

int indice_enfant(Partie_geographique p, int indice) {
    switch (p) {
        case HAUT_GAUCHE:
            return (indice * 4) + 1;
        case HAUT_DROIT:
            return (indice * 4) + 2;
        case BAS_DROIT:
            return (indice * 4) + 3;
        case BAS_GAUCHE:
            return (indice * 4) + 4;
    }
    return -1;
}

void init_fils(QuadTree *quadtree, Noeud *tab_noeud, int indice_fils, Partie_geographique p) {
    Point milieu;
    printf("indice fils : %d\n", indice_fils);
    if(tab_noeud == NULL) {
        printf("Erreur : tab_noeud == NULL\n");
        return;
    }
    if (indice_fils > (TAILLE_FENETRE/TAILLE_FEUILLE)*(TAILLE_FENETRE/TAILLE_FEUILLE)) {
        printf("Erreur : indice_fils > TAILLE_FENETRE/TAILLE_FEUILLE\n");
        return;
    }
    milieu.x = (tab_noeud[0].haut_gauche.x + tab_noeud[0].bas_droit.x) / 2;
    milieu.y = (tab_noeud[0].haut_gauche.y + tab_noeud[0].bas_droit.y) / 2;
    switch(p) {
        case HAUT_GAUCHE:
            tab_noeud[indice_fils].haut_gauche.x = tab_noeud[0].haut_gauche.x;
            tab_noeud[indice_fils].haut_gauche.y = tab_noeud[0].haut_gauche.y;
            tab_noeud[indice_fils].bas_droit.x = milieu.x;
            tab_noeud[indice_fils].bas_droit.y = milieu.y;
            break;
        case HAUT_DROIT:
            tab_noeud[indice_fils].haut_gauche.x = milieu.x;
            tab_noeud[indice_fils].haut_gauche.y = tab_noeud[0].haut_gauche.y;
            tab_noeud[indice_fils].bas_droit.x = tab_noeud[0].bas_droit.x;
            tab_noeud[indice_fils].bas_droit.y = milieu.y;
            break;
        case BAS_DROIT:
            tab_noeud[indice_fils].haut_gauche.x = milieu.x;
            tab_noeud[indice_fils].haut_gauche.y = milieu.y;
            tab_noeud[indice_fils].bas_droit.x = tab_noeud[0].bas_droit.x;
            tab_noeud[indice_fils].bas_droit.y = tab_noeud[0].bas_droit.y;
            break;
        case BAS_GAUCHE:
            tab_noeud[indice_fils].haut_gauche.x = tab_noeud[0].haut_gauche.x;
            tab_noeud[indice_fils].haut_gauche.y = milieu.y;
            tab_noeud[indice_fils].bas_droit.x = milieu.x;
            tab_noeud[indice_fils].bas_droit.y = tab_noeud[0].bas_droit.y;
            break;
    }
    tab_noeud[indice_fils].indice = indice_fils + tab_noeud[0].indice;
    tab_noeud[indice_fils].nb_couvre = 0;
    tab_noeud[indice_fils].lst_cell = NULL;
}


int ajout(QuadTree *quadtree, Noeud *tab_noeud, Cellule *cell) {
    int geo = 0, indice = 0;
    Cellule *temp;
    tab_noeud[0].nb_couvre++;
    /* Vérifier que le point se trouve bien dans le plus grand noeud */
    if (!test_zone_couvree(tab_noeud[0].haut_gauche.x, tab_noeud[0].bas_droit.x)) return -9;
    if (tab_noeud[0].nb_couvre > NB_POINT_FEUILLE) {
        if (tab_noeud[0].lst_cell == NULL) {
            /* l'ajout doit se faire dans l'un des fils */
            geo = test_partie_geo(tab_noeud[0], (cell->point));
            if (geo == -1) return -2;
            indice = indice_enfant(geo, tab_noeud[0].indice);
            printf("indice %d\n", indice);
            return ajout(quadtree, &tab_noeud[indice - tab_noeud[0].indice], cell);
        }
        /* Cas où on vient juste de surcharger un noeud 
        On descend petit a petit les point dans les fils adaptés */
        else {
            if (!test_zone_couvree(tab_noeud[0].haut_gauche.x / 4, tab_noeud[0].bas_droit.x / 4)) return -9;
            /* Initialisation des fils */
            if (quadtree->dernier == 0) quadtree->dernier = 4;
            else if (quadtree->dernier == quadtree->taille) return -1;
            else quadtree->dernier += 4*quadtree->dernier;
            for (Partie_geographique p = HAUT_GAUCHE; p < 4; p++) init_fils(quadtree, tab_noeud, (tab_noeud[0].indice * 4) + p + 1  - tab_noeud[0].indice, p);
            for (int i = 0; i < NB_POINT_FEUILLE; i++) {
                temp = tab_noeud[0].lst_cell;
                tab_noeud[0].lst_cell = tab_noeud[0].lst_cell->suiv;
                geo = test_partie_geo(tab_noeud[0], temp->point);
                if (geo == -1) return -2;
                indice = indice_enfant(geo, tab_noeud[0].indice);
                printf("indice %d\n", indice);
                ajout(quadtree, &tab_noeud[indice - tab_noeud[0].indice], temp);
            }
            geo = test_partie_geo(tab_noeud[0], cell->point);
            if (geo == -1) return -2;
            indice = indice_enfant(geo, tab_noeud[0].indice);
            printf("indice %d\n", indice);
            return ajout(quadtree, &tab_noeud[indice - tab_noeud[0].indice], cell);
        }
    } else {
        cell->suiv = tab_noeud[0].lst_cell;
        tab_noeud[0].lst_cell = cell;
        if(tab_noeud[0].indice == 0) return 0;
        else return (tab_noeud[0].indice - 1) / 4;
    }
    return -8;
}

void affiche_quadtree(QuadTree quadtree) {
    int i;
    Cellule *cur;
    for (i = 0; i <= quadtree.dernier; i++) {
        printf("Noeud %d : %d\nDimension : %f %f\n %f %f\n", i, quadtree.tab_noeud[i].nb_couvre, quadtree.tab_noeud[i].haut_gauche.x, quadtree.tab_noeud[i].haut_gauche.y, quadtree.tab_noeud[i].bas_droit.x, quadtree.tab_noeud[i].bas_droit.y);
        for (cur = quadtree.tab_noeud[i].lst_cell; cur != NULL; cur = cur->suiv) {
            printf("Point : %f %f\n", cur->point.x, cur->point.y);
        }
        printf("NULL\n\n");
    }
}


