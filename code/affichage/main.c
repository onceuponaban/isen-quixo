/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file main.c
 *  \version 1.0
 *  \brief le module qui reprend toutes les fonctons pour créer le programme
 */

//Inclusion des fichiers d'en-tête
#include <stdlib.h>
#include "GfxLib.h"
#include <stdio.h>
#include <stdbool.h>
#include "affichage.h"
#include <math.h>
#include "ESLib.h"
#include "BmpLib.h" // Cet include permet de manipuler des fichiers en .bmp

#define LargeurFenetre 1364
#define HauteurFenetre 589

//Déclarations globales :
	//variables utiles
	int avancementpartie;
	int largeurf,hauteurf;
	pCoord macase;
	
	//le plateau de jeu en mode console
	static Grille Plateau;

	//structures qui gérent les tours et scores des joueurs
	static Joueur joueur1,joueur2;
	static pJoueur pJ,pjoueur1,pjoueur2;
	
	static DonneesImageRGB *image = NULL; // L'image du logo du jeu
	
	//le pointeur vers un tableau 2D de structures
	static ptabCase ptC;

int main(void)
{
	// Initialisation de l'accéleration graphique si elle existe
	initialiseGfx(0, NULL);

	// On ouvre la fenêtre de notre application
	prepareFenetreGraphique("Quixisen !" , LargeurFenetre, HauteurFenetre);

	// Lance la boucle GLUT et aiguille les évenements sur la fonction gestionEvenements ci-après,
	//	qui elle-même utilise fonctionAffichage ci-dessous
	lanceBoucleEvenements();
	// On ne sort jamais de la fonction lanceBoucleEvenements, c'est pourquoi tout ce qui est
	// écrit ci-apres ne sera jamais executé
	// Jamais executé, le programme se terminera ailleurs
	ecrisChaine("Fin du main ");

return(0);
}


// La fonction de gestion des évenements, est appelé automatiquement par le systeme
// dès qu'une évenement survient.
void gestionEvenement(EvenementGfx evenement)
{
	// En fonction de l'evenement envoyé par le systeme...
	switch (evenement)
	{
		// Le message "Initialisation" est envoyé une seule fois, au debut du programme
		// Il faut y placer tout ce qui permet d'initialiser le programme
		case Initialisation:
	
			//initialisation du logo du jeu
			image = lisBMPRGB("logotest.bmp");
			
			//Allocation et orientation des pointeurs :
			
				ptC = malloc(sizeof(*ptC));
				/*Ici il faut mettre un rand()*/
				pJ = &joueur1;
				pjoueur1 = &joueur1;
				pjoueur2 = &joueur2;
	
			//remplissage structure Joueur
			joueur1.numero = 1;
			joueur1.suivant = pjoueur2;
			joueur2.numero = 2;
			joueur2.suivant = pjoueur1;
			
			printf("\n\t\t\t BIENVENUE DANS QUIXISEN \n");
	
			printf("\n Initialisation du plateau de jeu...\n");	
			Initialisation_Grille(Plateau);
			
			avancementpartie = 0;
				
		break;

		// Le systeme demande au programme de dessiner le fenêtre
		case Affichage:
		
			if (avancementpartie == 0)
			{
				effaceFenetre (185,105,28);
				
				//Le menu du mode graphique :
				Init_coord_grille(ptC);
					
				couleurCourante(255,255,255);
				rectangle((*ptC)[4][0].x1-150,(*ptC)[4][0].y1-50,(*ptC)[0][4].x3+150,(*ptC)[0][4].y3+50);
				couleurCourante(115,67,19);
				rectangle((*ptC)[4][0].x1-142,(*ptC)[4][0].y1-42,(*ptC)[0][4].x3+142,(*ptC)[0][4].y3+42);
				
				//Affichage d'une image
				if (image != NULL) // Si l'image a pu être lue
				{
					// On affiche l'image
					ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			}

			//Au moment du choix des joueurs
			if (avancementpartie == 1)
			{
				effaceFenetre (185,105,28);
				//Le menu du mode graphique
				Init_coord_grille(ptC);
					
				couleurCourante(255,255,255);
				rectangle((*ptC)[4][0].x1-150,(*ptC)[4][0].y1-50,(*ptC)[0][4].x3+150,(*ptC)[0][4].y3+50);
				couleurCourante(115,67,19);
				rectangle((*ptC)[4][0].x1-142,(*ptC)[4][0].y1-42,(*ptC)[0][4].x3+142,(*ptC)[0][4].y3+42);
					
				Dessine_cube_grille(ptC);
				surbrillance_choix(ptC,macase);
				
				//=======================pour les tests:
					croix(ptC,0,0);
					croix(ptC,0,4);
				//========================================
			}
			
		break;
		//break du case affichage

		case Clavier: // Une touche du clavier a été pressée
			switch (caractereClavier())
			{
				case'q':
					exit(EXIT_SUCCESS);
				break;
				
				case 'r':
					rafraichisFenetre();
				break;
			}

		case BoutonSouris: // Un bouton de la souris a été appuyé

			if (etatBoutonSouris() == GaucheAppuye)
			{ 
				if (avancementpartie == 0)
				{
					avancementpartie = 1;
					rafraichisFenetre();
					break;
				}
				if (avancementpartie == 1)
				{
					macase = Detecte_case_clic(ptC,abscisseSouris(),ordonneeSouris());	
					rafraichisFenetre();
					break;
				}
			}
			break;
		
        case ClavierSpecial: //une touche spéciale du clavier a été pressée
			switch(toucheClavier())
			{
				case ToucheF11:
					if ( largeurFenetre() != 1366 && hauteurFenetre() != 663 )
					{
						largeurf = largeurFenetre();
						hauteurf = hauteurFenetre();
						//mode plein ecran pour nos machines
						modePleinEcran(); 
						//1366x663 pour nos machines
					}
					else
						redimensionneFenetre(largeurf,hauteurf);
				break;
			}
		
		case Redimensionnement: //quand on redimensionne la fenêtre il y a ces tests
			if ((largeurFenetre() < 600) || (hauteurFenetre() < 400))
			{
				redimensionneFenetre(600,400);
			}
			if ((largeurFenetre() > 1000) && (hauteurFenetre() < 500))
			{
				redimensionneFenetre(1000,666);
			}
		break;
		
		// Les messages suivants ne sont pas traités ici
		case Inactivite:
		case Souris:
		break;
	}
}



