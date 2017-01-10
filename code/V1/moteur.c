// Date : 06/01/2017
// Auteurs : JACQUIEZ Romain, Ouassim AKEBLI et Antoine BERENGUER
// Contenu : le module moteur.c
// Resume : les fonctions qui gerent le moteur du programme

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "moteur.h"
#include "affichage.h"
#include "GfxLib.h"

// Resume : Cette fonction gère le cas d’erreur où la valeur n’est pas une coordonnée de la grille.
// Foo : valeur
// Retour : Vrai si erreur, faux si pas erreur
// Bugs :
bool Cas_Erreur(int valeur)
{
	//test du cas d'erreur
	if ((valeur < 0)||(valeur >= TAILLE_GRILLE ))
	{
		return(true);
	}
	else return(false);
}

// Resume : Cette fonction met la valeur dans la grille aux coordonnées données.
// Foo : G, coordligne, coordcol, valeur
// Retour : -1 si erreur ou 0
// Bugs :
int Set(Grille G, int coordligne, int coordcol, int valeur)
{
	//vérification de la validité de la case
	if ((Cas_Erreur(coordligne) == true)||(Cas_Erreur(coordcol) == true))
	{
		return(-1);
	}
	else

	//on affecte la valeur a la case de la grille
	G[coordligne][coordcol] = valeur;

	return(0);
}

// Resume : Cette fonction récupère la valeur de la grille aux coordonnées données.
// Foo : G, coordligne, coordligne
// Retour : -1 si erreur ou la valeur de la case
// Bugs :
int Get(Grille G, int coordligne, int coordcol)
{
	int valeur;
	//vérification de la validité de la case
	if ((Cas_Erreur(coordligne) == true)||(Cas_Erreur(coordcol) == true))
	{
		return(-1);
	}
	else

	//on recupere la valeur de la case de la grille
	valeur = G[coordligne][coordcol];

	return(valeur);
}

// Resume : Cette fonction initialise la grille
// Foo : G
// Retour :
// Bugs :
void Initialisation_Grille(Grille G)
{
	int indiceligne;
	int indicecol;

	//parcours la grille et la remplie de 0
	for (indiceligne = 0; indiceligne < TAILLE_GRILLE; indiceligne = indiceligne + 1)
	{
		for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol = indicecol + 1)
		{
			Set(G,indiceligne,indicecol,0);
		}
	}
}
