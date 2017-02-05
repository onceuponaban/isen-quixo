/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file moteur.c
 *  \version 1.0
 *  \brief les fonctions qui gerent le moteur du programme
 */

/** Inclusion des fichiers d'en-tête */
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
	/**test du cas d'erreur*/
	if ((valeur < 0)||(valeur >= TAILLE_GRILLE ))
	{
		return(true);
	}
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
	/**vérification de la validité de la case*/
	if ((Cas_Erreur(coordligne) == true)||(Cas_Erreur(coordcol) == true))
	{
		return(-1);
	}
	else

	/**on affecte la valeur a la case de la grille*/
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
	/**vérification de la validité de la case*/
	if ((Cas_Erreur(coordligne) == true)||(Cas_Erreur(coordcol) == true))
	{
		return(-1);
	}
	else

	/**on recupere la valeur de la case de la grille*/
	valeur = G[coordligne][coordcol];

	return(valeur);
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

	/**parcours la grille et la remplie de 0*/
	for (indiceligne = 0; indiceligne < TAILLE_GRILLE; indiceligne = indiceligne + 1)
	{
		for (indicecol = 0; indicecol < TAILLE_GRILLE; indicecol = indicecol + 1)
		{
			Set(G,indiceligne,indicecol,0);
		}
	}
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
	int gagnant;
	
	if (Gagne_colonne(G) != 0)
	{
		gagnant = Gagne_colonne(G);
		return (gagnant);
		/**Si on gagne par colonne on renvoie le gagnant*/
	}
	else if (Gagne_ligne(G) != 0)
	{
		gagnant = Gagne_ligne(G);
		return (gagnant);
		/**Sinon si on gagne par ligne on renvoie le gagnant*/
	}
	else if (Gagne_diagonale(G) != 0)
	{
		gagnant = Gagne_diagonale(G);
		return (gagnant);
		/**Sinon si on gagne par la diagonale on renvoie le gagnant*/
	}
	else if (Gagne_diagonale2(G) != 0)
	{
		gagnant = Gagne_diagonale2(G);
		return (gagnant);
		/**Sinon si on gagne par la diagonale inverse on renvoie le gagnant*/
	}
		
	return(0);
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement vertical sur le plateau
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_colonne(Grille G)
{
	int ligne,colonne,somme;
	somme = 0;
	
	for(colonne = 0; colonne < TAILLE_GRILLE; colonne++)
	{ 
	/**On regarde toutes les colonnes*/
		for(ligne = 0; ligne < TAILLE_GRILLE; ligne++)
		{			
		/**Dans la colonne, on vérifie toutes les cases*/
			if( (Get(G,0,colonne) == Get(G,ligne,colonne)) && (Get(G,ligne,colonne) != 0) )
			/**Si la première case est égale à la case que l'on vérfie et est non nulle*/
			{
				somme = somme + 1;
				/**On incrémente la somme de marqueurs identiques*/
			}
		}
	}
	if (somme == TAILLE_GRILLE) 
	{
		/**Si la somme de marqueurs requise pour gagner est atteinte
		* On récupère la valeur du marqueur gagnant
		*/
		return(Get(G,0,colonne)); 
		/**On retourne ce marqueur*/
	}else
	{
		somme = 0;
	}
	
	return(0);
	/**Aucun gagnant*/
}

/**
 * \brief       Fonction qui permet de savoir si il y a un gagnant
 * \details		Elle vérifie si il y a un alignement horizontal sur le plateau
 * \param    	G        qui est une variable qui représente le plateau du jeu
 * \return    	Un \e int qui est le numéro du joueur gagnant
 */
int Gagne_ligne(Grille G)
{
	int cube, ligne, somme;
	somme = 0;
	
	for(ligne = 0; ligne < TAILLE_GRILLE; ligne++)
	{ 
	/**On regarde toutes les lignes*/
		for(cube = 0; cube < TAILLE_GRILLE; cube++)
		{
		/**Dans la ligne, on vérifie toutes les cases*/
			if( (Get(G,ligne,0) == Get(G,ligne,cube)) && (Get(G,ligne,cube) != 0) )
			/**Si la première case est égale à la case que l'on vérfie et est non nulle*/
			{
				somme = somme + 1;
				/**On incrémente la somme de marqueurs identiques*/
			}
		}
	}
	if (somme == TAILLE_GRILLE) 
	{
		/**Si la somme de marqueurs requise pour gagner est atteinte
		* On récupère la valeur du marqueur gagnant
		*/
		return(Get(G,ligne,0)); 
		/**On retourne ce marqueur*/
	}else
	{
		somme = 0;
	}
	
	return(0);
	/**Aucun gagnant*/
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
	
	/**On regarde la diagonale*/
	for (indice = 0; indice < TAILLE_GRILLE; indice++)
	{
		if( (Get(G,indice,indice) == Get(G,0,0)) && (Get(G,indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		/**Si la case en haut à gauche est égale à la case que l'on vérfie et est non nulle
		* On incrémente la somme de marqueurs identiques
		*/
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,0,0));
		/**On retourne le numéro du joueur*/
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
	
	/**On regarde la diagonale */
	for (indice = TAILLE_GRILLE-1 ; indice >= 0; indice--)
	{
		if( (Get(G,indice,indice) == Get(G,TAILLE_GRILLE-1,TAILLE_GRILLE-1)) && (Get(G,indice,indice) != 0) )
		{
			somme = somme + 1;
		}
		/**Si la case en bas à droite est égale à la case que l'on vérfie et est non nulle
		* On incrémente la somme de marqueurs identiques
		*/
	}
	if (somme == TAILLE_GRILLE)
	{
		return(Get(G,TAILLE_GRILLE-1,TAILLE_GRILLE-1));
		/**On retourne le numéro du joueur*/
	}
	
	return(0);
	/**Aucun gagnant*/
}

/**
 * \brief       Fonction qui permet de changer de joueur
 * \details		Elle exploite le fait que pJ est une variable globale
 * \param    	le pointeur pJ
 * \return    	void
 */
 void Joueur_suivant(pJoueur p)
 {
	 p=p->suivant;
	 return;
 }

 /**
 * \brief       Fonction qui retourne l'ID du joueur actuel
 * \param    	le pointeur pJ
 * \return    	Un int qui correspond à l'ID du joueur actuel
 */
 int Joueur_actuel(pJoueur p)
 {
	 return (p->numero);
 }
