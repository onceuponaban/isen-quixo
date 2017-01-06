#include <stdio.h>
#include <stdlib.h>


void init_tab(){

int tab[5][5];
	
	printf("\n \n");
	printf("\t\t\t\t\t---|---|---|---|---\n");
for(int i =0 ; i<5 ; i++){
	for(int j = 0 ; j<1 ; j++){

	tab[i][j]=0;
	
	printf("\t\t\t\t\t %d | %d | %d | %d | %d \n",tab[i][j],tab[i][j],tab[i][j],tab[i][j],tab[i][j]);

	printf("\t\t\t\t\t---|---|---|---|---\n");
	
}
}

	printf("\n \n");
}
int main(void){


init_tab();

return 0;

}
