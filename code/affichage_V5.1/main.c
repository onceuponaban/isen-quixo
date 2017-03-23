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
	int frame;
	int vainqueur;

	//le plateau de jeu en mode console
	static Grille Plateau;

	//structures qui gérent les tours et scores des joueurs
	static Joueur joueur1,joueur2;
	static pJoueur pJ,pjoueur1,pjoueur2;

	static DonneesImageRGB *image = NULL; // L'image du logo du jeu

	//le pointeur vers un tableau 2D de structures
	static ptabCase ptC;

	//Un tableau statique de 4 pointeurs vers coord pour la gestion des cases sélectionnées et les variables associées
	static tabSelection caseSelection;
	static int idCaseSelection;
	static pCoord caseAncre;

	//Un booléen servant pour la sélection d'une case lors de la partie
	static bool modeSelection;

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

			Initialisation_Selection(caseSelection); //On initialise le tableau de sélection
			idCaseSelection = -1; //On initialise l'id de sélection
			caseAncre = NULL; //On initialise l'ancre
			//remplissage structure Joueur
			joueur1.numero = 1;
			joueur1.suivant = pjoueur2;
			joueur2.numero = 2;
			joueur2.suivant = pjoueur1;

			frame = 0;
			modeSelection = false;
			vainqueur = 0;

			printf("\n\t\t\t BIENVENUE DANS QUIXISEN \n");

			printf("\n Initialisation du plateau de jeu...\n");
			Initialisation_Grille(Plateau);

			avancementpartie = 0;

			//Provoque 25 rafraichissements par seconde. On se sert de ça pour les animations, comme par example les crédits défilants.
			demandeAnimation_ips(25);

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
				effaceFenetre (185,105,28);

				//On affiche les règles
				Dessine_ecran_regles(ptC);

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
				effaceFenetre (185,105,28);
				//On affiche les crédits
				if (frame < 350) //On affiche 350 frames sur ces crédits.
				{
					Dessine_ecran_credits(ptC, frame); //On affiche l'écran des crédits
					if (frame < 100) //Inutile d'afficher l'image après la 101ème frame, car après elle serait hors des bords de l'écran.
					{
						if (image != NULL) // Si l'image a pu être lue
						{
							// On affiche l'image (logo.bmp)
							ecrisImage((largeurFenetre()-image->largeurImage)/2, (float) hauteurFenetre()*frame/100, image->largeurImage, image->hauteurImage, image->donneesRGB);
						}
					}
					frame = frame + 1; //On avance d'une frame dans le temps
				}
				else //animation finie, on réinitialise et on revient sur le menu principal.
				{
					frame = 0;
					avancementpartie = 0;
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
				Affiche_Grille(Plateau);
				effaceFenetre (185,105,28);
				//Le menu du mode graphique
				Init_coord_grille(ptC);

				couleurCourante(255,255,255);
				rectangle((*ptC)[4][0].x1-150,(*ptC)[4][0].y1-50,(*ptC)[0][4].x3+150,(*ptC)[0][4].y3+50);
				couleurCourante(115,67,19);
				rectangle((*ptC)[4][0].x1-142,(*ptC)[4][0].y1-42,(*ptC)[0][4].x3+142,(*ptC)[0][4].y3+42);

				vainqueur = Gagne(Plateau);
				if (vainqueur == 0)
				{
					Dessine_cube_grille(ptC);
					if(modeSelection == true)
					{
						surbrillance_choix(ptC,caseAncre);
					}

					//=======================pour les tests:
						//croix(ptC,0,0);
						//croix(ptC,0,4);
					//========================================

					Dessine_marqueurs(Plateau, ptC);
				}
				else
				{
					Dessine_ecran_gagnant(pJ, vainqueur);
				}
			}

		break;
		//break du case affichage

		case Clavier: // Une touche du clavier a été pressée
			switch (caractereClavier())
			{
				case 'Q':
				case 'q':
					exit(EXIT_SUCCESS);
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
				if (avancementpartie == 1)
				{
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
				}
				if (avancementpartie == 2)
				{
					//si on clic pendant les crédits, on réinitialise l'état de l'animation et on revient au menu
					frame = 0;
					avancementpartie = 0;
					rafraichisFenetre();
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
					if (vainqueur == 0)
					{
						macase = Detecte_case_clic(ptC,abscisseSouris(),ordonneeSouris());
						//On récupère les infos sur la case sur laquelle le joueur a cliqué
						if (macase != NULL && Cas_Extremite(macase) == false)
						//Si le joueur a cliqué sur une case à l'extrémité du tableau
						{
							if (modeSelection == false)
							//Si on n'est pas en mode sélection (début de partie ou après la fin du tour du joueur précédent par exemple)
							{
								if(Cas_Signe(Plateau,*macase,pJ->numero) == false)
								//On vérifie si la case est vierge ou appartient au joueur
								{
									caseAncre = macase; //On fixe l'ancre sur la case cliquée
									//On attribue les sélections potentielles au tableau de sélection
									//0 = haut, 1 = bas, 2 = droite, 3 = gauche
									//Si la sélection n'est pas valide (par example le choix haut si la case est déjà sur la ligne la plus haute), elle vaudra NULL du au comportement des fonctions de choix.
									caseSelection[0]=Choix_haut(macase);
									caseSelection[1]=Choix_bas(macase);
									caseSelection[2]=Choix_droite(macase);
									caseSelection[3]=Choix_gauche(macase);

									modeSelection = true;
									//On passe en mode sélection
								}
							}

							if (modeSelection == true)  //Si on est en mode sélection
							{
								idCaseSelection = Verifie_selection(caseSelection, macase);
								//On cherche si on a cliqué sur une sélection valide et si oui laquelle

								//On place et on decale
								Place_Decale(Plateau,pJ,caseAncre,idCaseSelection);

								if (idCaseSelection != -1) //Si le déplacement a réussi
								{
									modeSelection = false; //On sort du mode sélection pour le joueur suivant
									Joueur_suivant(&pJ); //On passe au joueur suivant
								}
							}
						}
					}
					rafraichisFenetre();
					break;
				}
			}
			if(etatBoutonSouris() == DroiteAppuye)
			{
				if(avancementpartie == 20 && modeSelection == true) //Si on clique droit pendant la partie et qu'on est en mode selection, on peut déselectionner la case pour en choisir une autre.
				{
					modeSelection = false;
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



