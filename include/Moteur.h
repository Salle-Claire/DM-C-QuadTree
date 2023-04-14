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
#define TAILLE_FENETRE 1024

/**
 * @brief la taille d'une feuille,
 * autrement appelé arret de subdivision
 * @remark il s'agit d'une puissance de 4
 */
#define TAILLE_FEUILLE 8

#define NB_POINT_TOTAL 20000

/**
 * @brief le nombre maximum de points
 * que peut contenir une feuille
 */
#define NB_POINT_FEUILLE 10

typedef enum {
    HAUT_GAUCHE,
    HAUT_DROIT,
    BAS_DROIT,
    BAS_GAUCHE
} Partie_geographique;

/**
 * @brief Définit un point dans un plan à deux dimensions
 */
typedef struct {
    float x;  /**< Coordonnées réelles en x */
    float y;  /**< Coordonnées réelles en y */
} Point;

typedef struct __cellule__ {
    Point point;
    struct __cellule__ *suiv;
} Cellule, *Liste;

typedef struct __noeud__ {
    Liste lst_cell;  /**< liste chainée des cellules */
    Point haut_gauche;
    Point bas_droit;
    int nb_couvre;  /**< Le nombre de points que couvre le noeud */
    int indice;   /**< L'indice dans le tableau de noeud pour faire des fonctions récursives */
} Noeud;

typedef struct __quadtree__{
    Noeud *tab_noeud;
    int dernier;  /**< L'indice du dernier noeud rempli du tableau de noeud */
    int taille;  /**< La taille du tableau de noeud */
} QuadTree;

/**
 * @brief Initialise le QuadTree
 * @param quadtree 
 * @return int
 * @retval 0 si l'allocation a échoué
 * @retval 1 si l'initialisation a bien été faite
 */
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
 * @brief Teste si la zone dont la dimension
 * est la distance entre x1 et x2 est suffisament
 * grande pour être une feuille
 * @param x1
 * @param x2 
 * @return int
 * @retval 0 si la zone est trop petite
 * @retval 1 si la zone est suffisament grande
 */
int test_zone_couvree(int x1, int x2);

/**
 * @brief Retourne dans quelle partie se
 * trouve le point à l'intérieur du noeud
 * (partie supérieure gauche, supérieure droite,
 * inférieure droite, inférieure gauche)
 * @param noeud 
 * @param point 
 * @return Partie_geographique
 * @retval -1 si le point ne se trouve pas dans le noeud
 */
Partie_geographique test_partie_geo(Noeud noeud, Point point);

/**
 * @brief Calcule dans quel est l'indice de l'enfant
 * du noeud en fonction de quelle partie géographique
 * il s'agit
 * @param p 
 * @param indice 
 * @return int
 * @retval -1 si p est invalide
 */
int indice_enfant(Partie_geographique p, int indice);

/**
 * @brief Initialise un des fils du premier noeud
 * de tab_noeud
 * @param tab_noeud 
 * @param indice_fils 
 * @param p 
 */
void init_fils(QuadTree *quadtree, Noeud *tab_noeud, int indice_fils, Partie_geographique p);

/**
 * @brief Mets à jour le tableau de noeud
 * après l'ajout d'un point
 * @param tab_noeud 
 * @param cell Cellule dans laquelle se trouve
 * le point à ajouter
 * @return int 
 */
int ajout(QuadTree *quadtree, Noeud *tab_noeud, Cellule *cell);

/**
 * @brief Affiche le quadtree, c'est-à-dire
 * chacun de ses noeuds avec leur liste
 * chainé de cellules
 * @param quadtree 
 */
void affiche_quadtree(QuadTree quadtree);

#endif
