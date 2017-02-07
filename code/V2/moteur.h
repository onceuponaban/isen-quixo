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

/**  \typedef  Joueur: une structure qui regroupe les infos du joueur */
typedef struct Joueur{
	int numero;
	struct Joueur *suivant;
}Joueur;

/**  \typedef  pJoueur: un pointeur vers une structure de type Joueur */
typedef struct Joueur *pJoueur;

/**  \typedef  Coord: une structure qui regroupe les coordonnées du choix du cube a déplacer et aussi du choix où il va le mettre */
typedef struct Coord{
	int x;
	int y;
}Coord;

/**  \typedef  pCoord: un pointeur vers une structure de type Coord */
typedef struct Coord *pCoord;

/**------------------------PROTOTYPE DU MOTEUR EN MODE CONSOLE--------------------------------------*/

bool Cas_Erreur (int);
/**Cette fonction gère le cas d’erreur où la coordonnée (passée en paramètre) n’est pas dans la grille.*/

bool Cas_Extremite(Coord);
/**Cette fonction gère le cas d’erreur où les coordonnées (passées en paramètre) ne corrsepondent pas à une case de l'extremité de la grille.*/

int Set(Grille,int,int,int);
/**Cette fonction met la valeur dans la grille aux coordonnées données.*/

int Get(Grille,int,int);
/**Cette fonction récupère la valeur de la grille aux coordonnées données.*/

bool Cas_Signe(Grille,Coord,int);
/**Permet de savoir si la valeur de la case est celle du joueur qui joue*/

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

void Joueur_suivant(pJoueur);
/**Cette fonction permet de changer de joueur après la fin du tour.*/

int Joueur_actuel(pJoueur);
/**Cette fonction retourne l'ID du joueur actuel.*/

pCoord Choix_haut(Coord);
/**Cette fonction renvoie la case se situant le plus possible en haut de la grille par rapport à la case sélectionnée.*/

pCoord Choix_bas(Coord);
/**Cette fonction renvoie la case se situant le plus possible en bas de la grille par rapport à la case sélectionnée.*/

pCoord Choix_gauche(Coord);
/**Cette fonction renvoie la case se situant le plus possible à gauche de la grille par rapport à la case sélectionnée.*/

pCoord Choix_droite(Coord);
/**Cette fonction renvoie la case se situant le plus possible à droite de la grille par rapport à la case sélectionnée.*/








