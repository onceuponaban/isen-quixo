/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file affichage.h
 *  \version 1.0
 *  \brief prototypes des fonctions du module affichage.c
 */

/** Inclusion des fichiers d'en-tête */
#include "moteur.h"

/**------------------------PROTOTYPE DE L'AFFICHAGE EN MODE CONSOLE--------------------------------------*/

char Convertisseur_Symbole(int);
/**Gère l’affichage des symboles sur la grille. ex : 1 est en réalité X sur la grille*/

void Affiche_Grille(Grille);
/**Affiche de manière conviviale la grille*/
