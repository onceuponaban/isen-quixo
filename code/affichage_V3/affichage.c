/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file affichage.c
 *  \version 1.11
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
	couleurCourante(215,135,58);
		
	//On traduit les coordonnées d'une case en mode (X;Y), en coordonnées graphiques pour tracer la surbrillance sur cette case
	int xdepart = (*ptC)[pc_case->x][pc_case->y].x1+2;
	int ydepart = (*ptC)[pc_case->x][pc_case->y].y1+2;
	int xarrivee = (*ptC)[pc_case->x][pc_case->y].x3-2;
	int yarrivee = (*ptC)[pc_case->x][pc_case->y].y3-2;
		
	rectangle(xdepart,ydepart,xarrivee,yarrivee);
	couleurCourante(185,105,28);
	rectangle(xdepart+4,ydepart+4,xarrivee-4,yarrivee-4);
	}
	return;
}

/**
 * \brief       Fonction qui trace les surbrillances sur tous les choix de déplacement
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

/**
 * \brief       Fonction qui dessine l'accueil du mode graphique
 * \details     aucun
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * \return    	\e vide
 */
void Dessine_ecran_menu(ptabCase ptC)
{
	//le fond de l'ecran du menu
	couleurCourante(255,255,255);
	rectangle((*ptC)[4][0].x1-150,(*ptC)[4][0].y1-50,(*ptC)[0][4].x3+150,(*ptC)[0][4].y3+50);
	couleurCourante(115,67,19);
	rectangle((*ptC)[4][0].x1-142,(*ptC)[4][0].y1-42,(*ptC)[0][4].x3+142,(*ptC)[0][4].y3+42);
	
	// on affiche un rectangle
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	rectangle(largeurFenetre()/2-90, hauteurFenetre()/2 + 10, largeurFenetre()/2 + 90, hauteurFenetre()/2 + 70);
	// on affiche un rectangle
	couleurCourante(100, 50, 0); // Choix de la couleur marron
	rectangle(largeurFenetre()/2-85, hauteurFenetre()/2 + 15, largeurFenetre()/2 + 85, hauteurFenetre()/2 + 65);
	// on affiche du texte
	epaisseurDeTrait(2);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("J o u e r", 17,largeurFenetre()/2-51 , hauteurFenetre()/2 + 34);


	// on affiche un rectangle
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	rectangle(largeurFenetre()/2-90, hauteurFenetre()/2 - 30, largeurFenetre()/2 + 90, hauteurFenetre()/2 - 90);
	// on affiche un rectangle
	couleurCourante(100, 50, 0); // Choix de la couleur marron
	rectangle(largeurFenetre()/2-85, hauteurFenetre()/2 - 35, largeurFenetre()/2 + 85, hauteurFenetre()/2 - 85);
	// on affiche du texte
	epaisseurDeTrait(2);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("R e g l e s", 17,largeurFenetre()/2- 62 , hauteurFenetre()/2 - 67);
			
	// on affiche du texte
	epaisseurDeTrait(1);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("C r e d i t s", 20,(*ptC)[4][0].x1-130,(*ptC)[4][0].y1-30);
	// on affiche du texte
	epaisseurDeTrait(1);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("Q u i t t e r", 20,(*ptC)[4][4].x2-43,(*ptC)[4][4].y2-30);
}

/**
 * \brief       Fonction qui dessine le menu des modes de jeu du mode graphique
 * \details     aucun
 * \param    	ptC			car on a besoin du tableau 2D de structures
 * \return    	\e vide
 */
void Dessine_ecran_mode(ptabCase ptC)
{
	//le fond de l'ecran du menu
	couleurCourante(255,255,255);
	rectangle((*ptC)[4][0].x1-150,(*ptC)[4][0].y1-50,(*ptC)[0][4].x3+150,(*ptC)[0][4].y3+50);
	couleurCourante(115,67,19);
	rectangle((*ptC)[4][0].x1-142,(*ptC)[4][0].y1-42,(*ptC)[0][4].x3+142,(*ptC)[0][4].y3+42);
	
	// on affiche un rectangle
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	rectangle(largeurFenetre()/2-90, hauteurFenetre()/2 + 10, largeurFenetre()/2 + 90, hauteurFenetre()/2 + 70);
	// on affiche un rectangle
	couleurCourante(100, 50, 0); // Choix de la couleur marron
	rectangle(largeurFenetre()/2-85, hauteurFenetre()/2 + 15, largeurFenetre()/2 + 85, hauteurFenetre()/2 + 65);
	// on affiche du texte
	epaisseurDeTrait(2);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("1 VS 1", 17,largeurFenetre()/2-35 , hauteurFenetre()/2 + 34);


	// on affiche un rectangle
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	rectangle(largeurFenetre()/2-90, hauteurFenetre()/2 - 30, largeurFenetre()/2 + 90, hauteurFenetre()/2 - 90);
	// on affiche un rectangle
	couleurCourante(100, 50, 0); // Choix de la couleur marron
	rectangle(largeurFenetre()/2-85, hauteurFenetre()/2 - 35, largeurFenetre()/2 + 85, hauteurFenetre()/2 - 85);
	// on affiche du texte
	epaisseurDeTrait(2);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("1 VS IA", 17,largeurFenetre()/2- 37 , hauteurFenetre()/2 - 67);
			
	// on affiche du texte
	epaisseurDeTrait(1);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("M e n u", 20,(*ptC)[4][0].x1-130,(*ptC)[4][0].y1-30);
	// on affiche du texte
	epaisseurDeTrait(1);
	couleurCourante(255, 255, 255); // Choix de la couleur blanche
	afficheChaine("Q u i t t e r", 20,(*ptC)[4][4].x2-43,(*ptC)[4][4].y2-30);
}

/**
 * \brief       Fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton jouer ou 1 VS 1 dans le menu du jeu
 * \details     aucun
 * \param    	absc		l'abscisse de la souris lors du clic
 * 				ord			l'ordonnée de la souris lors du clic
 * \return    	\e bool , true si il a cliqué sur jouer/ 1VS 1 sinon false
 */
bool Jouer(int absc, int ord)
{	
	int largMin,largMax,ordMin,ordMax;
	
	largMin = (largeurFenetre()/2)- 85;
	largMax = (largeurFenetre()/2) + 85;
	ordMin = (hauteurFenetre()/2) + 15;
	ordMax = (hauteurFenetre()/2) + 65;
	
	if ( absc >= largMin && ord >= ordMin && absc <= largMax && ord <= ordMax ) 
	{
		return true;
	}
	
return false;
}

/**
 * \brief       Fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton Règles
 * \details     aucun
 * \param    	absc		l'abscisse de la souris lors du clic
 * 				ord			l'ordonnée de la souris lors du clic
 * \return    	\e bool , true si il a cliqué sur règles sinon false
 */
bool Regles(int absc, int ord)
{	
	int largMin,largMax,ordMin,ordMax;
	
	largMin = (largeurFenetre()/2)- 85;
	largMax = (largeurFenetre()/2) + 85;
	ordMin = (hauteurFenetre()/2) - 85;
	ordMax = (hauteurFenetre()/2) - 35;
	
	if ( absc >= largMin && ord >= ordMin && absc <= largMax && ord <= ordMax ) 
	{
		return true;
	}
return false;
}

/**
 * \brief       Fonction qui permet de déterminer si l'utilisateur à cliquer sur l'espace Credits
 * \details     aucun
 * \param    	ptC			Aide pour les coordonnées
 * 				absc		l'abscisse de la souris lors du clic
 * 				ord			l'ordonnée de la souris lors du clic
 * \return    	\e bool , true si il a cliqué sur credits sinon false
 */
bool Credits(ptabCase ptC, int absc, int ord)
{	
	int largMin,largMax,ordMin,ordMax;
	
	largMin = (*ptC)[4][0].x1-130;
	largMax = (*ptC)[4][0].x1+45;
	ordMin = (*ptC)[4][0].y1-35;
	ordMax = (*ptC)[4][0].y1-10;
		
	if ( absc >= largMin && ord >= ordMin && absc <= largMax && ord <= ordMax ) 
	{
		return true;
	}
return false;
}

/**
 * \brief       Fonction qui permet de déterminer si l'utilisateur à cliquer sur l'espace Quitter
 * \details     aucun
 * \param    	ptC			Aide pour les coordonnées
 * 				absc		l'abscisse de la souris lors du clic
 * 				ord			l'ordonnée de la souris lors du clic
 * \return    	\e bool , true si il a cliqué sur quitter sinon false
 */
bool Quitter(ptabCase ptC, int absc, int ord)
{	
	int largMin,largMax,ordMin,ordMax;
	
	largMin = (*ptC)[4][4].x2-43;
	largMax = (*ptC)[4][4].x2+130;
	ordMin = (*ptC)[4][0].y1-35;
	ordMax = (*ptC)[4][0].y1-10;
		
	if ( absc >= largMin && ord >= ordMin && absc <= largMax && ord <= ordMax ) 
	{
		return true;
	}
return false;
}

/**
 * \brief       Fonction qui permet de déterminer si l'utilisateur à cliquer sur l'espace Menu
 * \details     aucun
 * \param    	ptC			Aide pour les coordonnées
 * 				absc		l'abscisse de la souris lors du clic
 * 				ord			l'ordonnée de la souris lors du clic
 * \return    	\e bool , true si il a cliqué sur Menu sinon false
 */
bool Menu(ptabCase ptC, int absc, int ord)
{	
	int largMin,largMax,ordMin,ordMax;
	
	largMin = (*ptC)[4][0].x1-130;
	largMax = (*ptC)[4][0].x1-25;
	ordMin = (*ptC)[4][0].y1-35;
	ordMax = (*ptC)[4][0].y1-10;
		
	if ( absc >= largMin && ord >= ordMin && absc <= largMax && ord <= ordMax ) 
	{
		return true;
	}
return false;
}
