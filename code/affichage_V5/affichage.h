/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file affichage.h
 *  \version 1.11
 *  \brief prototypes des fonctions du module affichage.c
 */

// Inclusion des fichiers d'en-tête
#include "moteur.h"

//Constantes

#define LargeurFenetre 1364
#define HauteurFenetre 589

/*------------------------PROTOTYPE DE L'AFFICHAGE EN MODE CONSOLE--------------------------------------*/

char Convertisseur_Symbole(int);
/**Gère l’affichage des symboles sur la grille. ex : 1 est en réalité X sur la grille*/

void Affiche_Grille(Grille);
/**Affiche de manière conviviale la grille*/

/*------------------------PROTOTYPE DE L'AFFICHAGE EN MODE GRAPHIQUE-------------------------------------*/

void Dessine_cube_grille(ptabCase);
/**fonction qui dessine les ligne de la grille en fonction des coordonnées des cases qui sont
dans le tableau 2D de structs*/

void croix(ptabCase,int,int);
/**fonction qui dessine une croix dans la case dont les coordonnées sont passés en paramètres*/

pCoord Detecte_case_clic(ptabCase,int,int);
/**fonction qui renvoie un pointeur vers une structure qui contient les coordonnées de la
case où l’utilisateur a cliqué.*/

void surbrillance(ptabCase,pCoord);
/**fonction qui trace fait une surbrillance sur la case passée en paramètre*/

void surbrillance_choix(ptabCase,pCoord);
/**fonction qui trace fait une surbrillance sur tous les choix de déplacement*/

void Dessine_ecran_menu(ptabCase);
/**fonction qui dessine en graphique l'accueil*/

void Dessine_ecran_mode(ptabCase);
/**fonction qui dessine en graphique le menu des modes de jeu*/

void Dessine_ecran_regles(ptabCase);
/**fonction qui dessine en graphique les règles du jeu*/

void Dessine_ecran_credits(ptabCase, int pJoueur);
/**fonction qui dessine en graphique les crédits du jeu*/

void Dessine_ecran_gagnant(pJoueur, int);
/**fonction qui dessine en graphique le gagnant de la partie*/

void Dessine_marqueurs(Grille, ptabCase);
/**fonction qui dessine les marqueurs des joueurs en fonction de l'état de la grille*/

bool Jouer(int,int);
/**fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton jouer dans le menu du jeu*/

bool Regles(int,int);
/**fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton règles*/

bool Quitter(ptabCase,int,int);
/**fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton Quitter dans le menu du jeu*/

bool Credits(ptabCase,int,int);
/**fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton Credits dans le menu du jeu*/

bool Menu(ptabCase,int,int);
/**fonction qui permet de déterminer si l'utilisateur à cliquer sur le boutton Menu dans le menu des modes de jeux*/

void disque(float, float, float);
/** Fonction qui dessine un disque aux coordonnées données */

void cercle(ptabCase, int, int);
/** fonction qui dessine un cercle dans la case dont les coordonnées sont passés en paramètre*/
