//#include "vld.h"
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "vector.h"
#include "genes.h"
#include "functions.h"

int main(int argc, char* argv[]){

	if (argc != 5){
		printf("Podano za malo argumentow\nSprobuj jeszcze raz\n");
	}
	else {
		
		int population = atoi(argv[3]), backpack, amount;
		double probability = atof(argv[4]);\
		if (population <= 0 || probability < 0) {
			perror("B³êdne dane wejœciowe");
			exit(1);
		}
		items* tab_elem;
		read_from_file(argv[1], &backpack, &tab_elem, &amount);
		genetics(population, backpack, amount, probability, &tab_elem, argv[2]);	
		free(tab_elem);
	}
	system("PAUSE");
	return 0;
}


