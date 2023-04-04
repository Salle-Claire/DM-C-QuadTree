/**
* @file Moteur.h
* Fichier d'en-tête de Moteur.c
* contenant les définitions
* des fonctions, structure (et leur
* documentation) du moteur 
* du quadtree
* @author Claire SALLE
* @author Rayane NASSIB
* @date 16/04/2023
*/
#ifndef __MOTEUR__
#define __MOTEUR__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief la dimension entière et carrée 
 * de la fenêtre
 * @remark il s'agit d'une puisse de 4
 */
#define TAILLE_FENETRE 512

/**
 * @brief la taille d'une feuille,
 * autrement appelé arret de subdivision
 * @remark il s'agit d'une puisse de 4
 */
#define TAILLE_FEUILLE 1

#define NB_POINT_TOTAL 20

/**
 * @brief le nombre maximum de points
 * que peut contenir une feuille
 */
#define NB_POINT_FEUILLE 3

/**
 * @brief Définit un point dans un plan à deux dimensions
 */
typedef struct {
    float x;  /**< Coordonnées réelles en x */
    float y;  /**< Coordonnées réelles en y */
} Point;

typedef struct __cellule__ {
    Point *point;
    struct __cellule__ *suiv;
} Cellule, *Liste;

typedef struct __noeud__ {
    Liste lst_cell_noeud;
    Point haut_gauche;
    Point bas_droit;
    int nb_couvre;
} Noeud;

typedef struct __quadtree__{
    Noeud *tab_noeud;
    int dernier;
    int taille;
} QuadTree;

void remplissage_tab_cell(Cellule *tab_cell, Point* tab_point);

int init_quadtree(QuadTree *quadtree);

/**
 * @brief Génère un point aléatoirement
 * inscrit dans la fenêtre
 * @remark Après avoir généré le point aléatoire on lui
 * ajoute des décimales aléatoires afin qu'il soit
 * un point réel
 * @return Le point généré
 */
Point generation_aleatoire();

/**
 * @brief ajoute au chainage de points
 * un point, dans le cas où il n'y a pas
 * de saturage
 * @param noeud 
 * @param tab_cell 
 * @param num_point 
 */
void ajout_liste_chaine_point(Noeud* noeud, Cellule *tab_cell, int num_point);

void afficher_tab(Point* tab);

#endif
