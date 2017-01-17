// Date : 06/01/2017
// Auteurs : JACQUIEZ Romain, Ouassim AKEBLI et Antoine BERENGUER
// Contenu : le module main.c
// Resume : le module qui reprend toutes les fonctons pour créer le programme

#include <stdlib.h>
#include "GfxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "affichage.h"

int main(void)
{
	static Grille Plateau;
	
	Initialisation_Grille(Plateau);
	
	Affiche_Grille(Plateau);	
	
	return(0);
}
