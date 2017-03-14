/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file affichage.c
 *  \version 1.0
 *  \brief les fonctions qui gerent les affichages du programme
 */

// Inclusion des fichiers d'en-tête
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

	if ((symbole < 0)||(symbole > 3))
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
		
		case 3:
		
			symboleconverti = '*';
		
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

/**
 * \brief       Dessine les cubes en mode graphique
 * \details     Utilise le tableau 2D de structs dont le pointeur est passé en paramètre
 * \param    	ptC		le pointeur vers le tableau 2D de structs
 * \return    	\e vide
 */
void Dessine_cube_grille(ptabCase ptC)
{
	int i;
	int j;
	
	couleurCourante(185,105,28);
	
	for (i = 0; i < TAILLE_GRILLE; i++)
	{
		for (j = 0; j < TAILLE_GRILLE; j++)
		{
			rectangle((*ptC)[i][j].x1+2,(*ptC)[i][j].y1+2,(*ptC)[i][j].x3-2,(*ptC)[i][j].y3-2);
		}
	}		
}

/**
 * \brief       Dessine une croix dans la case dont les coordonnées sont passés en paramètres
 * \details     Ces coordonnées ne sont pas des coordonnées graphiques mais celui d'un tableau
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * 				iligne		coordonnée de la ligne sur un tableau
 * 				icolonne	coordonnée de la colonne sur un tableau
 * \return    	\e vide
 */
void croix(ptabCase ptC, int iligne, int icolonne)
{
	int X1,Y1,X2,Y2;
	int X3,Y3,X4,Y4;
	
	X1 = (*ptC)[iligne][icolonne].x4+(largeurFenetre()/15)/4;
	Y1 = (*ptC)[iligne][icolonne].y4-(largeurFenetre()/15)/4;
	X2 = (*ptC)[iligne][icolonne].x2-(largeurFenetre()/15)/4;
	Y2 = (*ptC)[iligne][icolonne].y2+(largeurFenetre()/15)/4;
	
	X3 = (*ptC)[iligne][icolonne].x1+(largeurFenetre()/15)/4;
	Y3 = (*ptC)[iligne][icolonne].y1+(largeurFenetre()/15)/4;
	X4 = (*ptC)[iligne][icolonne].x3-(largeurFenetre()/15)/4;
	Y4 = (*ptC)[iligne][icolonne].y4-(largeurFenetre()/15)/4;
	
	epaisseurDeTrait(8);
	couleurCourante(255,255,255);
	ligne(X1,Y1,X2,Y2);
	
	epaisseurDeTrait(8);
	couleurCourante(255,255,255);
	ligne(X3,Y3,X4,Y4);
	
	epaisseurDeTrait(5);
	couleurCourante(0,0,0);
	ligne(X1+1,Y1-1,X2-1,Y2+1);
	
	epaisseurDeTrait(5);
	couleurCourante(0,0,0);
	ligne(X3+1,Y3+1,X4-1,Y4-1);
}

/**
 * \brief       Permet de determiner sur quelle case l'utilisateur a cliqué en le mode graphique
 * \details     Ces coordonnées ne sont pas des coordonnées graphiques mais celui d'un tableau
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * 				abscisse	abscisse de la souris au moment du clic
 * 				ordonnee	ordonnée de la souris au moment du clic
 * \return    	Un pointeur \e pCoord vers une structure qui contient les coordonnées (X;Y) de la case où l'utilisateur a cliqué
 * 				en mode graphique
 */
pCoord Detecte_case_clic(ptabCase ptC, int abscisse, int ordonnee)
{
	int i;
	pCoord pCaseClic;
	pCaseClic = malloc(sizeof(Coord));
	
	//On commence par obtenir les extrémités de la grille
	//Choix assez arbitraire, plusieurs coordonnées pourraient correspondre. Pareil pour les autres extrémités.
	int extGrilleHaute = (*ptC)[0][0].y4;
	int extGrilleBasse = (*ptC)[TAILLE_GRILLE-1][0].y1;
	int extGrilleDroite = (*ptC)[0][TAILLE_GRILLE-1].x2;
	int extGrilleGauche = (*ptC)[0][0].x1;
	
	//Si on le clic n'est pas dans la grille, on renvoie le pointeur vers null
	if (abscisse < extGrilleGauche || abscisse > extGrilleDroite || ordonnee < extGrilleBasse || ordonnee > extGrilleHaute)
	{
		return NULL;
	}
	
	for (i = 0; i < TAILLE_GRILLE; i = i + 1)
	{
		if ((*ptC)[0][i].x4 <= abscisse)
		{
			pCaseClic->y = i;
		}
		if ((*ptC)[TAILLE_GRILLE-i-1][0].y1 <= ordonnee)
		{
			pCaseClic->x = TAILLE_GRILLE-i-1;
		}
	}
	
	return (pCaseClic);
}

/**
 * \brief       Fonction qui trace fait une surbrillance sur une case
 * \details     aucun
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * 				pc_case		qui est un pointeur vers une structure qui contient les coordonnées (X;Y)
 * 							de la case où l'on doit faire la surbrillance	
 * \return    	\e vide
 */
void surbrillance(ptabCase ptC, pCoord pc_case)
{
	if (pc_case != NULL)
	{
	//couleur de la surbrillance
	couleurCourante(205,125,48);
		
	//On traduit les coordonnées d'une case en mode (X;Y), en coordonnées graphiques pour tracer la surbrillance sur cette case
	int xdepart = (*ptC)[pc_case->x][pc_case->y].x1+2;
	int ydepart = (*ptC)[pc_case->x][pc_case->y].y1+2;
	int xarrivee = (*ptC)[pc_case->x][pc_case->y].x3-2;
	int yarrivee = (*ptC)[pc_case->x][pc_case->y].y3-2;
		
	rectangle(xdepart,ydepart,xarrivee,yarrivee);
	}
	return;
}

/**
 * \brief       Fonction qui trace fait les surbrillances sur tous les choix de déplacement
 * \details     Utilise les fonctions surbrillance et les fonctions de Choix
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * 				macase		qui est un pointeur vers une structure qui contient les coordonnées (X;Y)
 * 							de la case où l'on doit faire la surbrillance	
 * \return    	\e vide
 */
void surbrillance_choix(ptabCase ptC, pCoord macase)
{
	if (macase == NULL)
	{
		printf("Pas de cube sélectionnés\n");
	}
	else if (Cas_Extremite(macase) == true)
	{
		printf("J'ai cliqué au centre...pas d'actions possibles\n");
	}
	else
	{
		surbrillance(ptC,Choix_haut(macase));
		surbrillance(ptC,Choix_bas(macase));
		surbrillance(ptC,Choix_droite(macase));
		surbrillance(ptC,Choix_gauche(macase));
	}
}

