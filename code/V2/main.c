/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file main.c
 *  \version 1.0
 *  \brief le module qui reprend toutes les fonctons pour créer le programme
 */

/** Inclusion des fichiers d'en-tête */
#include <stdlib.h>
#include "GfxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "affichage.h"

/**  \typedef  Joueur: une structure qui regroupe les infos du joueur */
typedef struct Joueur{
	int numero;
	struct Joueur *suivant;
}Joueur;

/**  \typedef  pJoueur: un pointeur vers une structure de type Joueur */
typedef struct Joueur *pJoueur;

int main(void)
{
	int i =0;
	
	/**declaration*/
	static Grille Plateau;
	static Joueur j1,j2;
	static pJoueur pJ,pj1,pj2;
	
	pj1 = &j1;
	pJ = pj1;
	pj2 = &j2;
	
	/**remplissage structure*/
	j1.numero = 1;
	j1.suivant = pj2;
	j2.numero = 2;
	j2.suivant = pj1;
	
	printf("\n\t\t\t BIENVENUE DANS QUIXISEN \n");
	
	printf("\n Initialisation du plateau de jeu...\n");	
	Initialisation_Grille(Plateau);
	
	printf("\n Affichage du plateau de jeu :\n");	
	Affiche_Grille(Plateau);
	printf("\n");
	
	for ( i = 0; i < 6 ; i++ )
	{
		printf(" C'est au joueur %d de jouer\n", pJ->numero);
		pJ = pJ->suivant;
		
	}		
	
	return(0);
}
