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
static pCoord choix1,choix2,choix3,choix4;

int main(void)
{	
	/**orientation des pointeurs*/
	pJ = &joueur1;
	pjoueur1 = &joueur1;
	pjoueur2 = &joueur2;
	
	/**remplissage structure Joueur*/
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
		printf("\n\n C'est au tour du joueur %d de jouer\n" , Joueur_actuel(pJ));
		
		printf("\n Choix des coordonnées :\n");	
		
		/*--------------------------A mettre dans une fonction je pense------------------------------------*/	
		printf(" En X : ");
		if (scanf("%d", &(selection.x)) != 1) 
		{
			printf(" Erreur prise de valeur");
		}
		printf(" En Y : ");
		if (scanf("%d", &(selection.y)) != 1) 
		{
			printf(" Erreur prise de valeur");
		}
		while ((Cas_Extremite(selection) == true)||(Cas_Signe(Plateau,selection,Joueur_actuel(pJ))) )
		{
			printf(" Coordonnées invalides ! \n");
			printf(" Prenez une case de votre signe, ou sans signe et à l'extremité de la grille\n");
			
			printf(" En X : ");
			if (scanf("%d", &(selection.x)) != 1) 
			{
				printf(" Erreur prise de valeur");
			}
			printf(" En Y : ");
			if (scanf("%d", &(selection.y)) != 1) 
			{
				printf(" Erreur prise de valeur");
			}
		}
		/*-----------------------------------------------------------------------------------------------------*/
		
		Set(Plateau,selection.x,selection.y,3);
		Affiche_Grille(Plateau);
		printf("\n Votre sélection est la case marquée de : *\n");
		
		printf("\n Choix du décalage :\n");
		choix1 = Choix_haut(selection);
		choix2 = Choix_bas(selection);
		choix3 = Choix_gauche(selection);
		choix4 = Choix_droite(selection);
		if (choix1 != NULL)
		{
			printf(" (%d/%d)", choix1->x, choix1->y);
		}
		if (choix2 != NULL)
		{
			printf(" (%d/%d)", choix2->x, choix2->y);
		}
		if (choix3 != NULL)
		{
			printf(" (%d/%d)", choix3->x, choix3->y);
		}
		if (choix4 != NULL)
		{
			printf(" (%d/%d)", choix4->x, choix4->y);
		}
		
		/*decale*/
			
		pJ=pJ->suivant;
	}
	
	return(0);
}
