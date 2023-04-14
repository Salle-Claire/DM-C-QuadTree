/**
* @file Entree_Sortie.h
* Fichier d'en-tête de Entree_Sortie.c
* contenant les définitions
* des fonctions, structure (et leur
* documentation) de l'interphace
* graphique du quadtree à l'aide
* de la librairie libMLV
* @author Claire SALLE
* @author Rayane NASSIB
* @date 16/04/2023
*/

#ifndef __ENTREE_SORTIE__
#define __ENTREE_SORTIE__

#include "../include/Moteur.h"
#include <MLV/MLV_all.h>

/**
 * @brief Enumère les différent mode de
 * distribution des points sur la fenêtre
 */
typedef enum{
    SOURIS,
    ALEATOIRE
} Distribution;

/**
 * @brief Initialise la fenêtre
 * du quadtree
 */
void init_fenetre();

/**
 * @brief Récupère les coordonnées
 * du clic de l'utilisateur
 * @remark Après avoir récupéré les
 * coordonnées entière on lui
 * ajoute des décimales aléatoires 
 * afin qu'il soit un point réel
 * @return Point 
 */
Point recupPointClic();

/**
 * @brief Dessine le points donné
 * en arguement dans la fenêtre
 * @param point
 */
void afficherPoint(Point point);

void afficherQuadTree(QuadTree *quadtree, int indice);

/**
 * @brief Ferme la fenêtre
 */
void fermeture_fenetre();

#endif
