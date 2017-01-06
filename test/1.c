#include <stdio.h>



/*int main(void){ */


		int joueur = 0;



    	int gagne = 0;



    	int choix = 0;



    	int range = 0;



    	int column = 0;



    	int line = 0;


	char table [5][5] = {


                 {'A','B','C','D','E'},

                 {'F','G','H','I','J'},

                 {'K','L','M','N','O'},

                 {'P','Q','R','S','T'},

                 {'U','V','W','X','Y'}

					};





void affiche() {

		/*for (int i = 0; i<5 ; i++){
			for(int j =1 ; j<i ; j++){


        printf(" %c | %c | %c | %c | %c\n", table[i][j], table[i][j], table[i][j], table[i][j], table[i][j]);



        printf("---|---|---|---|---\n");



		}
		}

*/


        printf("\n\n");



        printf("\t\t\t %c | %c | %c | %c | %c\n", table[0][0], table[0][1], table[0][2], table[0][3], table[0][4]);



        printf("\t\t\t---|---|---|---|---\n");



        printf("\t\t\t %c | %c | %c | %c | %c\n", table[1][0], table[1][1], table[1][2], table[1][3], table[1][4]);



        printf("\t\t\t---|---|---|---|---\n");



        printf("\t\t\t %c | %c | %c | %c | %c\n", table[2][0], table[2][1], table[2][2], table[2][3], table[2][4]);



		printf("\t\t\t---|---|---|---|---\n");



        printf("\t\t\t %c | %c | %c | %c | %c\n", table[3][0], table[3][1], table[3][2], table[3][3], table[3][4]);



		printf("\t\t\t---|---|---|---|---\n");


        printf("\t\t\t %c | %c | %c | %c | %c\n", table[4][0], table[4][1], table[4][2], table[4][3], table[4][4]);



		printf("\n \n");
}

int main(void){

affiche();
return 0;
}
/*int main(){

affiche();

return 0;
}*/
