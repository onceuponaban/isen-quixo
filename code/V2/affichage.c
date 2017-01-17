/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file affichage.c
 *  \version 1.0
 *  \brief les fonctions qui gerent les affichages du programme
 */

/** Inclusion des fichiers d'en-tête */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "affichage.h"
#include "GfxLib.h"

/**
 * \brief       Convertie des entiers en char
 * \details     Gère l’affichage des symboles sur la grille
 * 				Ex : 1 est en réalité X sur la grille
 * \param    	symbole        symbole (entier) a convertir en char
 * \return    	Un \e char représentant le vrai symbole du joueur (croix ou rond).
 */
char Convertisseur_Symbole(int symbole)
{
	char symboleconverti;

	if ((symbole < 0)||(symbole > 2))
	{
		return('?');
	}

	switch (symbole)
	{
		case 0:

			symboleconverti = ' ';

		break;

		case 1:

			symboleconverti = 'X';

		break;

		case 2:

			symboleconverti = 'O';

		break;
	}

	return(symboleconverti);
}

/**
 * \brief       Affiche le plateau du jeu
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	\e vide
 */
void Affiche_Grille(Grille G)
{
	int indiceligne;
	int indicecol;

	printf("\n");
	for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol++)
	{
		printf("\t %d",indicecol);
     }

	printf("\n \n");
	indiceligne = 0;
	printf("\t\b\b\b|-------|-------|-------|-------|-------|\n");

	for (indiceligne = 0; indiceligne < TAILLE_GRILLE; indiceligne = indiceligne + 1)
	{
		printf("     |       |       |       |       |       |\n");
		printf("%d",indiceligne);
		printf("    |     ");
		for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol = indicecol + 1)
		{
			printf("\b\b%c",Convertisseur_Symbole( Get(G,indiceligne,indicecol) ) );
			printf("   |     ");

		}
		printf("\n");
		printf("     |       |       |       |       |       |\n");
		printf("\t\b\b\b|-------|-------|-------|-------|-------|\n");
     }

}
