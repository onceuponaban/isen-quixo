// Date : 06/01/2017
// Auteurs : JACQUIEZ Romain, Ouassim AKEBLI et Antoine BERENGUER
// Contenu : le module moteur.h
// Resume : les prototypes des fonctions du moteur.c

#include <stdbool.h>
#define TAILLE_GRILLE 5
typedef int Grille[TAILLE_GRILLE][TAILLE_GRILLE];

//------------------------PROTOTYPE DU MOTEUR EN MODE CONSOLE--------------------------------------

bool Cas_Erreur (int);
//Cette fonction gère le cas d’erreur où la coordonnée (passée en paramètre) n’est pas dans la grille.

int Set(Grille,int,int,int);
//Cette fonction met la valeur dans la grille aux coordonnées données.

int Get(Grille,int,int);
//Cette fonction récupère la valeur de la grille aux coordonnées données.

void Initialisation_Grille (Grille);
//Cette fonction initialise la grille



