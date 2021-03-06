/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file moteur.c
 *  \version 1.2
 *  \brief les fonctions qui gerent le moteur du programme
 */

//* Inclusion des fichiers d'en-tête
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "moteur.h"
#include "GfxLib.h"

/**
 * \brief       Fonction de gestion d'erreur
 * \details     Permet de savoir si la valeur est une coordonnée d'un tableau de taille 5x5
 * \param    	valeur        la valeur dont il est question
 * \return    	Un \e boll représentant si il y a une erreur (true) ou non (false)
 */
bool Cas_Erreur(int valeur)
{
	//test du cas d'erreur
	if ((valeur < 0)||(valeur >= TAILLE_GRILLE ))
	{
		return(true);
	}
	else return(false);
}

/**
 * \brief       Fonction de gestion d'erreur
 * \details     Permet de savoir si la valeur est une coordonnée de l'extremité du tableau
 * \param    	pC        un poibnteur vers une strcuture coord en X,Y
 * \return    	Un \e boll représentant si il y a une erreur (true) ou non (false)
 */
bool Cas_Extremite(pCoord pC)
{
	//Si on est au centre de la grille
	if ((pC->x >= 1) && (pC->y >= 1) && (pC->x <= 3) && (pC->y <= 3))
	{
		//on retourne true (il y a une erreur)
		return(true);
	}
	//sinon on retourne false (pas d'erreur)
	else return(false);
}

/**
 * \brief       Fonction qui accéde au tableau
 * \details     Permet de placer des valeurs dans le tableau en prenant en compte les erreurs
 * \param    	G        	qui est une variable qui représente le plateau du jeu
 * \param		coordligne	qui est la coordonnée de la ligne où l'on veut placer la valeur
 * \param		coordcol	qui est la coordonnée de la colonne où l'on veut placer la valeur
 * \param		valeur		qui est la valeur à placée
 * \return    	Un \e int 0 ou -1 suivant si il y a eu une erreur (-1) ou non
 */
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

/**
 * \brief       Fonction qui accéde au tableau
 * \details     Permet de prendre une valeur dans le tableau en prenant en compte les erreurs
 * \param    	G        	qui est une variable qui représente le plateau du jeu
 * \param		coordligne	qui est la coordonnée de la ligne où l'on veut placer la valeur
 * \param		coordcol	qui est la coordonnée de la colonne où l'on veut placer la valeur
 * \return    	Un \e int qui représente la valeur si aucune erreur ou -1 si il y a eu une erreur
 */
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

/**
 * \brief       Fonction de gestion d'erreur
 * \details     Permet de savoir si la valeur de la case est celle du joueur qui joue;
 * \param    	G			  la grille;
 * 				valeur        1 ou 2 suivant le joueur;
 * 				selection     une strcuture coord en X,Y;
 * \return    	Un \e boll représentant si il y a une erreur (true) ou non (false)
 */
bool Cas_Signe(Grille G, Coord selection, int valeur)
{
	//test du cas d'erreur
	if ((Get(G,selection.x,selection.y) != valeur) && (Get(G,selection.x,selection.y) != 0) )
	{
		return(true);
	}
	else return(false);
}

/**
 * \brief       Fonction qui initialise le plateau du jeu
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	\e vide
 */
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

/**
 * \brief       Fonction qui permet d'initialiser les sélections en début de partie
 * \details		aucun
 * \param    	caseSelection       Le tableau contenant les sélections possibles
 * \return    	\e vide
 */
void Initialisation_Selection (tabSelection caseSelection)
{
	int i;
	for(i = 0; i < 4; i = i + 1) //On initialise les cases de sélection
	{
		caseSelection[i] = NULL;
	}
	return;
}

/**
 * \brief       Fonction qui permet de vérifier la sélection du joueur en phase sélection
 * \details		Elle renvoie l'id de la sélection en cas de correspondance, -1 sinon
 * 				de déterminer qui est gagné
 * \param    	caseSelection       Le tableau contenant les sélections possibles
 * 				macase				La case choisie par le joueur
 * \return    	Un \e int qui sert d'id de correspondance
 */
int Verifie_selection (tabSelection caseSelection, pCoord macase)
{
	int i;
	int idSel = -1;
	for(i = 0; i < 4; i = i + 1) //Cette boucle vérifie si la case sur laquelle on a cliquée correspond à l'un des choix possibles pour déplacer le bloc sélectionné
	{
		if(caseSelection[i] != NULL) //Si la sélection est valide
		{
			if (macase->x == caseSelection[i]->x && macase->y == caseSelection[i]->y) //Test d'égalité sur la structure pCoord
			{
				idSel = i; //Cette affection permettra d'appeler la bonne fonction de décalage
			}
		}
	}
	return idSel; //Si la fonction a trouvée une sélection correspondante, idSel vaut l'indice de cette sélection, sinon -1
}


/**
 * \brief       Fonction qui permet de savoir le gagnant
 * \details		Elle apelle les autres fonctions \e Gagne et grâce a une suite de test permet
 * 				de déterminer qui est gagné
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne(Grille G)
{
	int i;
	bool joueur1Gagnant = false;
	bool joueur2Gagnant = false;
	for (i = 0; i < TAILLE_GRILLE; i = i + 1) //Pour toutes les lignes et colonnes, on vérifie si il y a au moins un gagnant
	{
		if (Gagne_colonne(G,i) == 1 || Gagne_ligne(G,i) == 1)
		{
			joueur1Gagnant = true;
		}
		if (Gagne_colonne(G,i) == 2 || Gagne_ligne(G,i) == 2)
		{
			joueur2Gagnant = true;
		}
	}
	//De même pour les diagonales
	if (Gagne_diagonale(G) == 1 || Gagne_diagonale2(G) == 1)
	{
		joueur1Gagnant = true;
	}
	if (Gagne_diagonale(G) == 2 || Gagne_diagonale2(G) == 2)
	{
		joueur2Gagnant = true;
	}
	if (joueur1Gagnant == true && joueur2Gagnant == true) //Cas spécial dans ce jeu, le gagnant est l'adversaire de celui qui a provoqué la victoire des deux joueurs
	{
		return -1;
	}
	else if (joueur1Gagnant == true) //Si le joueur 1 est le seul gagnant
	{
		return 1;
	}
	else if (joueur2Gagnant == true) //Si le joueur 2 est le seul gagnant
	{
		return 2;
	}
	return(0);
	//Aucun gagnant
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement vertical sur le plateau
 * \param    	G		qui est une variable qui représente le plateau du jeu
 * 				colonne	qui est la colonne vérifiée
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_colonne(Grille G, int colonne)
{
	int ligne,somme;
	somme = 0;
	for(ligne = 0; ligne < TAILLE_GRILLE; ligne++)
	{
	//Dans la colonne, on vérifie toutes les cases
		if( (Get(G,0,colonne) == Get(G,ligne,colonne)) && (Get(G,ligne,colonne) != 0) )
		//Si la première case est égale à la case que l'on vérfie et est non nulle
		{
			somme = somme + 1;
			//On incrémente la somme de marqueurs identiques
		}
	}
	if (somme == TAILLE_GRILLE)
	{
		/*Si la somme de marqueurs requise pour gagner est atteinte
		* On récupère la valeur du marqueur gagnant
		*/
		return(Get(G,0,colonne));
		//On retourne ce marqueur
	}
	return(0);
	//Aucun gagnant
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement horizontal sur le plateau
 * \param    	G		qui est une variable qui représente le plateau du jeu
 * 				ligne	qui est la ligne vérifiée
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_ligne(Grille G, int ligne)
{
	int colonne, somme;
	somme = 0;
	for(colonne = 0; colonne < TAILLE_GRILLE; colonne++)
	{
	//Dans la ligne, on vérifie toutes les cases
		if( (Get(G,ligne,0) == Get(G,ligne,colonne)) && (Get(G,ligne,colonne) != 0) )
		//Si la première case est égale à la case que l'on vérfie et est non nulle
		{
			somme = somme + 1;
			//On incrémente la somme de marqueurs identiques
		}
	}
	if (somme == TAILLE_GRILLE)
	{
		/*Si la somme de marqueurs requise pour gagner est atteinte
		* On récupère la valeur du marqueur gagnant
		*/
		return(Get(G,ligne,0));
		//On retourne ce marqueur
	}
	return(0);
	//Aucun gagnant
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement par diagonal sur le plateau
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_diagonale(Grille G)
{
	int indice,somme;
	somme = 0;

	//On regarde la diagonale
	for (indice = 0; indice < TAILLE_GRILLE; indice++)
	{
		if( (Get(G,indice,indice) == Get(G,0,0)) && (Get(G,indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		/*Si la case en haut à gauche est égale à la case que l'on vérfie et est non nulle
		* On incrémente la somme de marqueurs identiques
		*/
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,0,0));
		//On retourne le numéro du joueur
	}

	return(0);
	/**Aucun gagnant*/
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement par diagonal inverse sur le plateau
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_diagonale2(Grille G)
{
	int indice,somme;
	somme = 0;

	//On regarde la diagonale
	for (indice = 0 ; indice < TAILLE_GRILLE; indice++)
	{
		if( (Get(G,TAILLE_GRILLE-1-indice,indice) == Get(G,TAILLE_GRILLE-1,0)) && (Get(G,TAILLE_GRILLE-1-indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		/*Si la case en bas à droite est égale à la case que l'on vérfie et est non nulle
		* On incrémente la somme de marqueurs identiques
		*/
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,TAILLE_GRILLE-1,0));
		//On retourne le numéro du joueur
	}

	return(0);
	/**Aucun gagnant*/
}

/**
 * \brief       Fonction qui permet de changer de joueur
 * \details		Elle exploite le fait que pJ est une variable globale
 * \param    	le pointeur pJ
 * \return    	\e void
 */
 void Joueur_suivant(pJoueur *pp)
 {
	 *pp=(*pp)->suivant;
 }

 /**
 * \brief       Fonction qui retourne l'ID du joueur actuel
 * \param    	le pointeur pJ
 * \return    	\e int qui correspond à l'ID du joueur actuel
 */
 int Joueur_actuel(pJoueur p)
 {
	 return (p->numero);
 }

/**
 * \brief       Fonction qui permet de retourner les choix des décalages
 * \details		Gère le choix du haut
 * \param    	coordCase		qui est la selection du joueur
 * \return    	pCoordHaut		un pointeur vers une structure Coord qui contient les coordonnées de la case où
 * 								va se faire le décalage
 */
pCoord Choix_haut(pCoord pcoordCase)
{
	pCoord pCoordHaut;

	if (pcoordCase->x == 0)
	{
		return(NULL);
		//on est déjà en haut de la grille, il n'est pas possible de choisir une case plus haute
	}

	pCoordHaut = malloc(sizeof(Coord));
	pCoordHaut->y = pcoordCase->y;
	pCoordHaut->x = 0;

	return (pCoordHaut);
}

/**
 * \brief       Fonction qui permet de retourner les choix des décalages
 * \details		Gère le choix du bas
 * \param    	coordCase		qui est la selection du joueur
 * \return    	pCoordBas		un pointeur vers une structure Coord qui contient les coordonnées de la case où
 * 								va se faire le décalage
 */
pCoord Choix_bas(pCoord pcoordCase)
{
	pCoord pCoordBas;

	if (pcoordCase->x == 4)
	{
		return(NULL);
		//on est déjà en bas de la grille, il n'est pas possible de choisir une case plus basse
	}

	pCoordBas = malloc(sizeof(Coord));
	pCoordBas->y = pcoordCase->y;
	pCoordBas->x = 4;

	return (pCoordBas);
}

/**
 * \brief       Fonction qui permet de retourner les choix des décalages
 * \details		Gère le choix de droite
 * \param    	coordCase		qui est la selection du joueur
 * \return    	pCoordDroite	un pointeur vers une structure Coord qui contient les coordonnées de la case où
 * 								va se faire le décalage
 */
pCoord Choix_droite(pCoord pcoordCase)
{
	pCoord pCoordDroite;

	if (pcoordCase->y == 4)
	{
		return(NULL);
		//on est déjà à droite de la grille, il n'est pas possible de choisir une case plus à droite
	}

	pCoordDroite = malloc(sizeof(Coord));
	pCoordDroite->y = 4;
	pCoordDroite->x = pcoordCase->x;

	return (pCoordDroite);
}

/**
 * \brief       Fonction qui permet de retourner les choix des décalages
 * \details		Gère le choix de gauche
 * \param    	coordCase		qui est la selection du joueur
 * \return    	pCoordGauche	un pointeur vers une structure Coord qui contient les coordonnées de la case où
 * 								va se faire le décalage
 */
pCoord Choix_gauche(pCoord pcoordCase)
{
	pCoord pCoordGauche;

	if (pcoordCase->y == 0)
	{
		return(NULL);
		//on est déjà à gauche de la grille, il n'est pas possible de choisir une case plus à gauche
	}

	pCoordGauche = malloc(sizeof(Coord));
	pCoordGauche->y = 0;
	pCoordGauche->x = pcoordCase->x;

	return (pCoordGauche);
}

/**
 * \brief       Fonction qui permet faire un décalage
 * \details		Gère le décalage de gauche à droite
 * \param    	P			qui est le plateau de jeu
 * 				selection	qui est la sélection du joueur (la case qu'il veut déplacer)
 * 				numJoueur	qui est le numéro du joueur qui décale
 * \return    	\e void
 */
void Decale_ligne_gauche(Grille P, Coord selection,int numJoueur)
{
	int y;

	for (y = selection.y; y >= 1; y--)
	{
		Set(P,selection.x,y,Get(P,selection.x,y-1));
	}

	Set(P,selection.x,0,numJoueur);
}

/**
 * \brief       Fonction qui permet faire un décalage
 * \details		Gère le décalage de droite à gauche
 * \param    	P			qui est le plateau de jeu
 * 				selection	qui est la sélection du joueur (la case qu'il veut déplacer)
 * 				numJoueur	qui est le numéro du joueur qui décale
 * \return    	\e void
 */
void Decale_ligne_droite(Grille P, Coord selection,int numJoueur)
{
	int y;

	for (y = selection.y; y < (TAILLE_GRILLE-1); y++)
	{
		Set(P,selection.x,y,Get(P,selection.x,y+1));
	}

	Set(P,selection.x,TAILLE_GRILLE-1,numJoueur);
}

/**
 * \brief       Fonction qui permet faire un décalage
 * \details		Gère le décalage de haut en bas
 * \param    	P			qui est le plateau de jeu
 * 				selection	qui est la sélection du joueur (la case qu'il veut déplacer)
 * 				numJoueur	qui est le numéro du joueur qui décale
 * \return    	\e void
 */
void Decale_colonne_haut(Grille P, Coord selection,int numJoueur)
{
	int x;

	for (x = selection.x; x >= 1; x--)
	{
		Set(P,x,selection.y,Get(P,x-1,selection.y));
	}

	Set(P,0,selection.y,numJoueur);
}

/**
 * \brief       Fonction qui permet faire un décalage
 * \details		Gère le décalage de bas en haut
 * \param    	P			qui est le plateau de jeu
 * 				selection	qui est la sélection du joueur (la case qu'il veut déplacer)
 * 				numJoueur	qui est le numéro du joueur qui décale
 * \return    	\e void
 */
void Decale_colonne_bas(Grille P, Coord selection,int numJoueur)
{
	int x;

	for (x = selection.x; x < (TAILLE_GRILLE-1); x++)
	{
		Set(P,x,selection.y,Get(P,x+1,selection.y));
	}

	Set(P,TAILLE_GRILLE-1,selection.y,numJoueur);
}

/*=============================================================================================================================*/

/**
 * \brief       Fonction qui initialise le tableau 2D de structures avec toutes les coordonnées
 * \details		On passe par un pointeur vers le tableau 2D de struct
 * \param    	ptC		le pointeur vers un tableau tabCase
 * \return    	\e void
 */
void Init_coord_grille(ptabCase ptC)
{
	 int i,j;
	 int xmin,ymin;
	 int taille;

	//On définit l'origine de notre tableau (en bas à gauche)
	taille = largeurFenetre()/15;
	ymin = (hauteurFenetre()-(taille*5))/2;
	xmin = (largeurFenetre()-(taille*5))/2;

	for(i = 4; i >= 0; i--)
	/*On calcule maintenant les coordonnées des quatres points de chaque case de la grille en mode console
	*et on les stock dans notre tableau 2D de structs*/
	{
		for (j = 0; j < TAILLE_GRILLE; j++)
		{
			(*ptC)[i][j].x1 = xmin + (j*taille);
			(*ptC)[i][j].y1 = ymin + ((TAILLE_GRILLE-1-i)*taille);
			(*ptC)[i][j].x2 = (*ptC)[i][j].x1 + taille;
			(*ptC)[i][j].y2 = (*ptC)[i][j].y1;
			(*ptC)[i][j].x3 = (*ptC)[i][j].x2;
			(*ptC)[i][j].y3 = (*ptC)[i][j].y2 + taille;
			(*ptC)[i][j].x4 = (*ptC)[i][j].x1;
			(*ptC)[i][j].y4 = (*ptC)[i][j].y3;
		}
	}
}

/**
 * \brief       Fonction qui place le marqueur du joueur et fait le décalage approprié
 * \details		Utilise beaucoup de paramètres
 * \param    	Plateau				le plateau de jeu (tableau 2D)
 * 				pJ 					le pointeur qui gère les srtuctures joueurs (utile pour mettre le bon marqueur)
 * 				caseAncre			nécessaire pour savoir d'où par le décalage
 * 				idCaseSelection		permet de savoir quel décalage il faut faire
 * \return    	\e void
 */
void Place_Decale(Grille Plateau, pJoueur pJ, pCoord caseAncre, int idCaseSelection)
{
	switch(idCaseSelection) 
	//Ce switch appelle la fonction décalage appropriée
	{
		case 0:
			Decale_colonne_haut(Plateau, *caseAncre, pJ->numero);
		break;
		
		case 1:
			Decale_colonne_bas(Plateau, *caseAncre, pJ->numero);
		break;
		
		case 2:
			Decale_ligne_droite(Plateau, *caseAncre, pJ->numero);
		break;
		
		case 3:
			Decale_ligne_gauche(Plateau, *caseAncre, pJ->numero);
		break;
		
		default: //Si la case n'était pas valide (idCaseSelection vaut alors -1)
		printf("Mauvaise case! Il faut choisir une des cases en surbrillance.\n");
		break;
	}
}

