/** \date 6 Janvier 2017
 *  \author Jacquiez.Romain Akebli.Ouassim Berenguer.Antoine
 *  \file main.c
 *  \version 1.0
 *  \brief le module qui reprend toutes les fonctons pour créer le programme
 */

/** Inclusion des fichiers d'en-tête */
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
