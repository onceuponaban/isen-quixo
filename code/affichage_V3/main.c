/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file main.c
 *  \version 2.1
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
		
			/*if (avancementpartie == -1)
			{
				effaceFenetre (185,105,28);
				couleurCourante(0,0,0);
				rectangle((*ptC)[4][0].x1-130,(*ptC)[4][0].y1-35,(*ptC)[4][0].x1-25,(*ptC)[4][0].y1-10);
			}*/
		
			if (avancementpartie == 0)
			//Menu du jeu
			{
				effaceFenetre (185,105,28);
				
				//Le menu du mode graphique :
				Init_coord_grille(ptC);
				Dessine_ecran_menu(ptC);
				//Affichage du logo
				if (image != NULL) // Si l'image a pu être lue
				{
					// On affiche l'image (logo.bmp)
					ecrisImage((largeurFenetre()-image->largeurImage)/2, hauteurFenetre()/2 + 125, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			}
			
			if (avancementpartie == 1)
			//Les règles
			{
				effaceFenetre (255,0,0);

				//Affichage du logo
				if (image != NULL) // Si l'image a pu être lue
				{
					// On affiche l'image (logo.bmp)
					ecrisImage((largeurFenetre()-image->largeurImage)/2, hauteurFenetre()/2 + 125, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			}
			
			if (avancementpartie == 2)
			//Les crédits
			{
				effaceFenetre (0,255,0);

				//Affichage du logo
				if (image != NULL) // Si l'image a pu être lue
				{
					// On affiche l'image (logo.bmp)
					ecrisImage((largeurFenetre()-image->largeurImage)/2, hauteurFenetre()/2 + 125, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			}
			
			
			if (avancementpartie == 10)
			//Menu des modes de jeux
			{
				effaceFenetre (185,105,28);
				
				//Le menu du mode graphique :
				Init_coord_grille(ptC);
				Dessine_ecran_mode(ptC);
				//Affichage du logo
				if (image != NULL) // Si l'image a pu être lue
				{
					// On affiche l'image (logo.bmp)
					ecrisImage((largeurFenetre()-image->largeurImage)/2, hauteurFenetre()/2 + 125, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}
			}

			if (avancementpartie == 20)
			//Durant la partie
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
				/*avancementpartie = -1;
				printf("%d",avancementpartie);
				rafraichisFenetre();
				printf("%d %d %d %d",(*ptC)[4][0].x1-130,(*ptC)[4][0].y1-35,(*ptC)[4][0].x1+45,(*ptC)[4][0].y1-10);*/
				if (avancementpartie == 0)
				{
					if ( Jouer(abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur jouer on passe au menu des modes de jeux
						avancementpartie = 10;
						rafraichisFenetre();
					}
					if ( Regles(abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur règles on passe à l'affichage des règles
						avancementpartie = 1;
						rafraichisFenetre();
					}
					if ( Credits(ptC,abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur crédits on passe à l'affichage des crédits
						avancementpartie = 2;
						rafraichisFenetre();
					}
					if ( Quitter(ptC,abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur quitter, on quitte le programme
						exit(EXIT_SUCCESS);
					}
					break;
				}
				
				if (avancementpartie == 10)
				{
					if ( Jouer(abscisseSouris(),ordonneeSouris()) == true )
					{
						//si sur le menu des modes de jeux, on clic sur 1VS1, on passe à la partie
						avancementpartie = 20;
						rafraichisFenetre();
					}
					if ( Regles(abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur 1 VS IA on passe a la partie contre l'ia
						avancementpartie = 30;
						rafraichisFenetre();
					}
					if ( Menu(ptC,abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur menu on revient à l'écran d'accueil du jeu
						avancementpartie = 0;
						rafraichisFenetre();
					}
					if ( Quitter(ptC,abscisseSouris(),ordonneeSouris()) == true )
					{
						//si on clic sur quitter, on quitte le programme
						exit(EXIT_SUCCESS);
					}
					break;
				}
				
				if (avancementpartie == 20)
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
			Init_coord_grille(ptC);
			if ((largeurFenetre() < 976) || (hauteurFenetre() < 500))
			{
				redimensionneFenetre(976,500);
			}
		break;
		
		// Les messages suivants ne sont pas traités ici
		case Inactivite:
		case Souris:
		break;
	}
}



