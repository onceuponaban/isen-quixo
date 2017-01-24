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
#include <math.h>

/**declaration globale*/
static Grille Plateau;
static Joueur joueur1,joueur2;
static pJoueur pJ,pjoueur1,pjoueur2;
static Coord selection;

int main(void)
{	
	/**orientation des pointeurs*/
	pJ = &joueur1;
	pjoueur1 = &joueur1;
	pjoueur2 = &joueur2;
	
	/**remplissage structure*/
	joueur1.numero = 1;
	joueur1.suivant = pjoueur2;
	joueur2.numero = 2;
	joueur2.suivant = pjoueur1;
	
	printf("\n\t\t\t BIENVENUE DANS QUIXISEN \n");
	
	printf("\n Initialisation du plateau de jeu...\n");	
	Initialisation_Grille(Plateau);
	
	printf("\n Affichage du plateau de jeu :\n");	
	Affiche_Grille(Plateau);
	printf("\n");
	
	while ( Gagne(Plateau) == 0 )
	{
		printf("\n C'est au tour du joueur %d de jouer\n" , /*Joueur_actuel()*/ pJ->numero );
		printf("\n Choix des coordonnées :\n");
		printf("\n En X :");
		scanf("%d", &(selection.x) );
		
		printf ("Valeur : %d", selection.x);
		
		Joueur_suivant();
	}
	
	return(0);
}
