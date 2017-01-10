// Date : 06/01/2017
// Auteurs : JACQUIEZ Romain, Ouassim AKEBLI et Antoine BERENGUER
// Contenu : le module affichage.c
// Resume : les fonctions qui gerent les affichages du programme

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "affichage.h"
#include "GfxLib.h"

// Resume : Gère l’affichage des pions sur la grille. ex : 1 est en réalité X sur la grille
// Foo : entree definissant le retour
// Retour : X si 1, O si 2
// Bugs :
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

// Resume : Affiche de manière conviviale la grille
// Foo : G
// Retour :
// Bugs :
void Affiche_Grille(Grille G)
{
	int indiceligne;
	int indicecol;
	int i;

	printf("\n");

	for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol++)
	{
		printf("\t\t%d",indicecol);
     }

	printf("\n \n");
	indiceligne = 0;
	printf("\t\b|----------------|---------------|---------------|---------------|---------------|\n");
	printf("       |                |               |               |               |               |\n");
	printf("       |                |               |               |               |               |\n");

	for (indiceligne = 0; indiceligne < TAILLE_GRILLE; indiceligne = indiceligne + 1)
	{
		printf("%d",indiceligne);
		printf("      |      ");
		for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol = indicecol + 1)
		{


			printf("  %c",Convertisseur_Symbole( Get(G,indiceligne,indicecol) ) );
			printf("       |     ");

		}
		printf("\n");
		
		for ( i = 0 ; i < 2 ; i ++ ){
		printf("       |                |               |               |               |               |\n");
		}
		printf("\t\b|----------------|---------------|---------------|---------------|---------------|\n");
		for( i=0 ; i<2 ; i++){
		printf("       |                |               |               |               |               |\n");
		}
     }

}
