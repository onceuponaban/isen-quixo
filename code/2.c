#include <stdio.h>


	char table [5][5] = {


                 {'A','B','C','D','E'},

                 {'F','G','H','I','J'},

                 {'K','L','M','N','O'},

                 {'P','Q','R','S','T'},

                 {'U','V','W','X','Y'}

					};





void affiche() {

		for (int i = 0; i<5 ; i++){
			for(int j =0; j<1 ; j++){


        printf("  \t\t\t\t%c | %c | %c | %c | %c\n", table[i][j], table[i][j+1], table[i][j+2], table[i][j+3], table[i][j+4]);



        printf("\t\t\t\t--|---|---|---|---\n");



		}
		}


}

int main(void){

affiche();
return 0;
}
