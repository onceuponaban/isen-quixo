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

#define LargeurFenetre 600
#define HauteurFenetre 600

//Déclarations globales
	int avancementpartie;
	
	static Grille Plateau;

	static Joueur joueur1,joueur2;
	static pJoueur pJ,pjoueur1,pjoueur2;

	static Coord selection;

	static pCoord choix1,choix2,choix3,choix4;
	int monChoix;

int main()
{
	// Initialisation de l'acceleration graphique si elle existe
	initialiseGfx(0, NULL);

	// On ouvre la fenetre de notre application
	prepareFenetreGraphique("Quixisen !" , LargeurFenetre, HauteurFenetre);

	// Lance la boucle GLUT et aiguille les evenements sur la fonction gestionEvenements ci-apres,
	//	qui elle-meme utilise fonctionAffichage ci-dessous
	lanceBoucleEvenements();
	// On ne sort jamais de la fonction lanceBoucleEvenements, c'est pourquoi tout ce qui est
	// ecrit ci-apres ne sera jamais execute
	// Jamais execute, le programme se terminera ailleurs
	ecrisChaine("Fin du main ");

return(0);
}


// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient.
void gestionEvenement(EvenementGfx evenement)
{
	// En fonction de l'evenement envoye par le systeme...
	switch (evenement)
	{
		// Le message "Initialisation" est envoye une seule fois, au debut du programme
		// Il faut y placer tout ce qui permet d'initialiser le programme
		case Initialisation:

			//Orientation des pointeurs
	
			/*Ici faut mettre rand()*/
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
			Initialisation_grille(Plateau);

			break;

		// Le systeme demande au programme de dessiner le fenetre
		case Affichage:

				//Accueil graph
				if (avancementpartie == 0)
				{
					//Le menu du mode graphique
					Dessine(avancementpartie);
				}

				//Durant la partie
				if (avancementpartie == 1)
				{
						//Graphique
						effaceFenetre (0,0,0);
						Dessin(avancementpartie);
						Trace_pion(Plateau,tabcase);
						Affiche_joueur(Joueur_actuel(pJ));

						//Console
						Affiche_grille(Plateau);
						printf("\n C'est au tour du joueur %d de jouer\n" , Joueur_actuel(pJ));
						sautDeLigne();
				}

				//Si gagnant
				if (avancementpartie == 2)
				{
					    effaceFenetre (0,0,0);
						Trace_pion(Plateau,tabcase);
						Trace_ligne_gagnant(Plateau,tabcase);
						avancementpartie = 0;
						Initialisation_grille(Plateau);
						//redessine une grille apres un certain temps pour laisser l'ultilisateur voir la ligne tracée sur l'alignement gagnant
						//fait par la fonction Trace_ligne_gagnant
						demandeRedessinDans_ms(950);
				}

				//Si egalite
				if (avancementpartie == 2)
				{
						/*...*/
				}

			break;

		case Clavier: // Une touche du clavier a ete pressee
			switch (caractereClavier())
			{

			}

		case BoutonSouris: // Un bouton de la souris a ete appuye

			if (etatBoutonSouris() == GaucheAppuye)
			{
				//Si on clic sur Quitter on ferme le programme (cf. Clic_Quitter dans moteur.c)
				Clic_Quitter(abscisseSouris(), ordonneeSouris());
			}
			
			rafraichisFenetre();

			break;


		// Les messages suivants ne sont pas traites ici
		case Inactivite:
        	case ClavierSpecial:
		case Souris:
		case Redimensionnement:
	 		 break;

		 }
	}


