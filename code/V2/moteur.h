/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file moteur.h
 *  \version 1.0
 *  \brief les prototypes des fonctions du moteur.c
 */

/** Inclusion des fichiers d'en-tête */
#include <stdbool.h>

/**  \def TAILLE_GRILLE*/
#define TAILLE_GRILLE 5

/**  \typedef  Grille: le plateau de jeu */
typedef int Grille[TAILLE_GRILLE][TAILLE_GRILLE];

/**------------------------PROTOTYPE DU MOTEUR EN MODE CONSOLE--------------------------------------*/

bool Cas_Erreur (int);
/**Cette fonction gère le cas d’erreur où la coordonnée (passée en paramètre) n’est pas dans la grille.*/

int Set(Grille,int,int,int);
/**Cette fonction met la valeur dans la grille aux coordonnées données.*/

int Get(Grille,int,int);
/**Cette fonction récupère la valeur de la grille aux coordonnées données.*/

void Initialisation_Grille (Grille);
/**Cette fonction initialise la grille.*/

int Gagne(Grille);
/**Cette fonction renvoie le numéro du joueur gagnant grâce aux fonctions ci-dessous.*/

int Gagne_colonne(Grille);
/**Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur une colonne. */

int Gagne_ligne(Grille);
/**Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur une ligne.*/

int Gagne_diagonale(Grille);
/**Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur la diagonale.*/

int Gagne_diagonale2(Grille);
/**Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur la diagonale inverse.*/ 

