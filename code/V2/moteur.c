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

// Resume : Cette fonction renvoie le numéro du joueur gagnant grâce aux fonctions gagne
// Foo : G
// Retour : Numéro du joueur gagnant
// Bugs :
int Gagne(Grille G)
{
	int gagnant;
	
	if (Gagne_colonne(G) != 0)
	{
		gagnant = Gagne_colonne(G);
		return (gagnant);
		//Si on gagne par colonne on renvoie le gagnant
	}
	else if (Gagne_ligne(G) != 0)
	{
		gagnant = Gagne_ligne(G);
		return (gagnant);
		//Sinon si on gagne par ligne on renvoie le gagnant
	}
	else if (Gagne_diagonale(G) != 0)
	{
		gagnant = Gagne_diagonale(G);
		return (gagnant);
		//Sinon si on gagne par la diagonale on renvoie le gagnant
	}
	else if (Gagne_diagonale2(G) != 0)
	{
		gagnant = Gagne_diagonale2(G);
		return (gagnant);
		//Sinon si on gagne par la diagonale inverse on renvoie le gagnant
	}
		
	return(0);
}

// Resume : Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un acolonnement sur une colonne. 
// Foo : G
// Retour : Numéro du joueur gagnant
int Gagne_colonne(Grille G)
{
	int cube, colonne,somme;
	
	for(colonne = 0; colonne < TAILLE_GRILLE; colonne++)
	{ 
	//On regarde toutes les colonnes
		for(cube = 0; cube < TAILLE_GRILLE; cube++)
		{
		//Dans la colonne, on vérifie toutes les cases
			if( (Get(G,0,colonne) == Get(G,cube,colonne)) && (Get(G,cube,colonne) != 0) )
			//Si la première case est égale à la case que l'on vérfie et est non nulle
			{
				somme = somme + 1;
				//On incrémente la somme de marqueurs identiques
			}
		}
		if (somme == TAILLE_GRILLE) 
		{
			//Si la somme de marqueurs requise pour gagner est atteinte
			//On récupère la valeur du marqueur gagnant
			return(Get(G,0,colonne)); 
			//On retourne ce marqueur
		}else
		{
			somme = 0;
		}
	}
	
	return(0);
	//Aucun gagnant
}

// Resume : Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur une ligne. 
// Foo : G
// Retour : Numéro du joueur gagnant
// Bugs :
int Gagne_ligne(Grille G)
{
	int cube, ligne, somme;
	
	for(ligne = 0; ligne < TAILLE_GRILLE; ligne++)
	{ 
	//On regarde toutes les lignes
		for(cube = 0; cube < TAILLE_GRILLE; cube++)
		{
		//Dans la ligne, on vérifie toutes les cases
			if( (Get(G,ligne,0) == Get(G,ligne,cube)) && (Get(G,ligne,cube) != 0) )
			//Si la première case est égale à la case que l'on vérfie et est non nulle
			{
				somme = somme + 1;
				//On incrémente la somme de marqueurs identiques
			}
		}
		if (somme == TAILLE_GRILLE) 
		{
			//Si la somme de marqueurs requise pour gagner est atteinte
			//On récupère la valeur du marqueur gagnant
			return(Get(G,ligne,0)); 
			//On retourne ce marqueur
		}else
		{
			somme = 0;
		}
	}
	
	return(0);
	//Aucun gagnant
}

// Resume : Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur la diagonale
// Foo : G
// Retour : Numéro du joueur gagnant
// Bugs :
int Gagne_diagonale(Grille G)
{
	int indice,somme;
	
	//On regarde la diagonale 
	for (indice = 0; indice < TAILLE_GRILLE; indice++)
	{
		if( (Get(G,indice,indice) == Get(G,0,0)) && (Get(G,indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		//Si la case en haut à gauche est égale à la case que l'on vérfie et est non nulle
		//On incrémente la somme de marqueurs identiques
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,0,0));
		//On retourne le numéro du joueur
	}
	
	return(0);
	//Aucun gagnant
}

// Resume : Cette fonction prend en paramètre un tableau et vérifie si un joueur a gagné grâce à un alignement sur la diagonale inverse
// Foo : G
// Retour : Numéro du joueur gagnant
// Bugs :
int Gagne_diagonale2(Grille G)
{
	int indice,somme;
	
	//On regarde la diagonale 
	for (indice = TAILLE_GRILLE-1 ; indice >= 0; indice--)
	{
		if( (Get(G,indice,indice) == Get(G,TAILLE_GRILLE-1,TAILLE_GRILLE-1)) && (Get(G,indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		//Si la case en bas à droite est égale à la case que l'on vérfie et est non nulle
		//On incrémente la somme de marqueurs identiques
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,TAILLE_GRILLE-1,TAILLE_GRILLE-1));
		//On retourne le numéro du joueur
	}
	
	return(0);
	//Aucun gagnant
}
