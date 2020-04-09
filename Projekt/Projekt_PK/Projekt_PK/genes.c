#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "vector.h"
#include "genes.h"
#include "functions.h"

double adapt(vtr* v,items* tab_elem, int backpack) {
	int size = 0;
	int value = 0;
	for (int i = 0; i < v->size; i++) {
		if (v->data[i] == TRUE) {
			size += tab_elem[i].size;																			//Obliczanie sum wartoœci i objêtoœci
			value += tab_elem[i].value;
		}
	}
	if (size > backpack)																						//Dla objêtoœci wiêkszej od obj.plecaka zwracamy wspó³czynnik du¿o
	return (double)1/(backpack*backpack);																		//mniejszy od teoretycznie najgorszego przypadku (1/backpack)
	else
	return (double)value / backpack;																			//Je¿eli nie, zwracamy wartoœæ przedmiotów/obj. plecaka
}

void roulette(values* tab_values, double* results, int population){
	for (int i = 0; i < population; i++) {
		results[i] = (double)rand()*100 /RAND_MAX;															//Losowanie N liczb z zakresu <0,100>
	}
}

void parents(values* tab_values, double* results, int* indexes, int population) {
	for (int i = 0, j = 0; i < population&& j< population; i++, j++) {
		if (results[i] <= tab_values[j].fit_sum)																//Dobór indeksów rodziców na podstawie badania czy
		{																										//wylosowana liczba jest mniejsza b¹dŸ równa od 
			indexes[i] = j;																						//wartoœci sumy dla danego rodzica
			j--;																								//(obie tablice posortowane s¹ rosn¹co
		}
		else  i--;
	}
}

void breed(vtr** pop_parents, vtr** pop_children, int* indexes, int population, double probability, int amount, int* best_index, items* tab_elem, int backpack) {
	for (int i = 0; i < population; i+=2) {
		int index1 = rand() % (population - i);
		copy_from_end_vector(pop_parents[indexes[index1]], pop_children[i]);									//Dzieci s¹ najpierw kopiami swoich rodziców
		indexes[index1] = indexes[population -i-1];																//Wylosowany rodzic jest usuwany z dlaszego losowania
		int index2 = rand() % (population - i-1);
		copy_from_end_vector(pop_parents[indexes[index2]], pop_children[i + 1]);
		indexes[index2] = indexes[population -i-2];
		int len = 1+ rand() % (amount-1);																		//Punkt krzy¿owania jednopunktowego
		vtr* tail1 = create_vector(len);																		//Tworzenie wektorów o d³ugoœci wektor->size-len
		vtr* tail2 = create_vector(len);
		copy_from_end_vector(pop_children[i], tail1);															//Kopiowanie ogonów
		copy_from_end_vector(pop_children[i + 1], tail2);
		paste_at_end_vector(pop_children[i], tail2) ;															//Wklejanie ogonów na krzy¿
		paste_at_end_vector(pop_children[i + 1], tail1);
		delete_vector(&tail1);																					//Usuwanie ogonów
		delete_vector(&tail2);
		for (int j = 0; j <amount; j++) {																		//MUTACJA
			double mutation1 = (double)rand() / RAND_MAX , mutation2 = (double)rand() / RAND_MAX ;				//Losowanie liczb z przedzia³u <0,1>
			if (mutation1 <= probability) mutate(pop_children[i], j);											//Mutacja je¿eli liczba jest mniejsza od P mutacji
			if (mutation2 <= probability) mutate(pop_children[i + 1], j);
		}
	}
	bool elite = FALSE;																							//ELITARYZM
	double tmp2= adapt(pop_children[0], tab_elem, backpack);													//Dostosawnie pierwszego osobnika z populacji dzieci
	int min = 0;
	double tmp;
	for (int i=1; i < population &&!elite; i++) {
		tmp = adapt(pop_children[i], tab_elem, backpack);
		if (tmp == 1 / (backpack*backpack)) {																	//Szukanie pierwszego elementu o za du¿ej objêtoœci
			paste_at_end_vector(pop_parents[*best_index], pop_children[i]);
			*best_index = i;
			elite = TRUE;
		}
		if (tmp<tmp2){																							//Je¿eli nie ma za du¿ego rozmiaru, szukamy minimum
			tmp2 = tmp;
			min = i;
		}
	}
	if (!elite) {
		if (tmp2 < adapt(pop_parents[*best_index], tab_elem, backpack)) {										//Je¿eli nie wpisano elity sprawdzamy, czy jest lepsza od minimum populacji dzieci
			paste_at_end_vector(pop_parents[*best_index], pop_children[min]);									//Je¿eli tak zamieniamy najs³abszego osobnika na elitarnego z populacji rodziców
			*best_index = min;
		}
	}
}

void mutate(vtr* v, int i) {
	bool change = get_vector(v, i);
	if (change == 1)
		change = 0;
	else change = 1;
	load_vector(v, i, change);
}

void genetics(int population, int backpack, int amount, double probability, items** tab_elem, char* name) {
	if (population % 2 == 1) population += 1;
	vtr** tab_pop = (vtr**)malloc(sizeof(vtr*) * population);													//Utworzenie pierwszej populacji rodziców
	if (!tab_pop) {																								//Niepoprawna alokacja koñczy program
		perror("tab_pop");
		free(*tab_elem);
		exit(3);
	}						
	for (int i = 0; i < population; i++)
		tab_pop[i] = init_vector(amount);																		//Inicjalizacja populacji
	
	int* max_value = (int*)malloc(sizeof(int)*(iterations+1));													//Tablica przechowuj¹ca najwiêkszy rozmiar plecaka po ka¿dej iteracji
	if (!max_value) {																							//Niepoprawna alokacja koñczy program
		perror("tab_pop");
		for (int i = 0; i < population; i++)
			delete_vector(&tab_pop[i]);
		free(tab_pop);
		free(*tab_elem);
		exit(3);
	}
	max_value[0] = 0;																							//Wymienione zmienne s¹ alokowane i zwalniane w pêtli
	
	values* tab_values;																							//WskaŸnik na struktury values
	vtr** tab_pop2;																								//WskaŸnik na wektory nowej populacji
	double* results;																							//WskaŸnik na wyniki ruletki
	int* indexes;																								//WskaŸnik na indeksy wylosowanych rodziców
	int best_index;
	
	for (int cycles = 1; cycles <= iterations; cycles++) {
		tab_values = (values*)malloc(sizeof(values)*population);												//Tablica przechowuj¹ca struktury z danymi liczbowymi populacji
		if (!tab_values) {																						//Niepoprawna alokacja koñczy program
			perror("tab_values");
			for (int i = 0; i < population; i++)
				delete_vector(&tab_pop[i]);
			free(tab_pop);
			free(max_value);
			free(*tab_elem);
			exit(3);
		}
		double sum = 0;
		max_value[cycles] = max_value[cycles - 1];																//Przepisanie poprzedniego maksimum
		for (int i = 0; i < population; i++){
			tab_values[i].adaptation = adapt(tab_pop[i], *tab_elem, backpack);									//Obliczenie wspó³czynnika adaptacji
			if (tab_values[i].adaptation!=1/(backpack*backpack)&&max_value[cycles] < tab_values[i].adaptation*backpack) {
				max_value[cycles] = (int)(tab_values[i].adaptation*backpack);									//Zmiana maksimum w danej iteracji dla elementu o lepszej adaptacji
				best_index = i;
			}
			sum += tab_values[i].adaptation;
		}
		tab_values[0].fit = tab_values[0].fit_sum = tab_values[0].adaptation * 100 / sum;	
		for (int i = 1; i < population; i++){
			tab_values[i].fit = tab_values[i].adaptation * 100 / sum;											//Wspó³czynnik dopasowania jako wsp. adaptacji/sumê wszystkich wsp. adaptacji (w %)
			tab_values[i].fit_sum = tab_values[i].fit + tab_values[i - 1].fit_sum;								//Suma wszystkich poprzednich i obecnego wsp. dopasowania
			//print_vector(tab_pop[i]);
			//printf("\t\t%f\t%f\t%f\n", tab_values[i].adaptation, tab_values[i].fit, tab_values[i].fit_sum);
		}
		//putc('\n', stdout);
		results = (double*)malloc(sizeof(double)*population);													//Tablica z wynikami losowania ruletk¹
		if (!results) {																							//Niepoprawna alokacja koñczy program
			perror("results");
			for (int i = 0; i < population; i++)
				delete_vector(&tab_pop[i]);
			free(tab_pop);
			free(max_value);
			free(tab_values);
			free(*tab_elem);
			exit(3);
		}
		roulette(tab_values, results, population);																//Losowanie liczb double z zakresu 1-100
		quick(results, 0, population - 1);																		//Sortowanie rosn¹ce wyników
		indexes = (int*)malloc(sizeof(int)*population);															//Tablica na indeksy wylosowanych rodziców
		if (!indexes) {									//Niepoprawna alokacja koñczy program
			perror("indexes");
			for (int i = 0; i < population; i++)
				delete_vector(&tab_pop[i]);
			free(tab_pop);
			free(max_value);
			free(tab_values);
			free(results);
			free(*tab_elem);
			exit(3);
		}
		if (tab_values[population - 1].fit_sum != 100.0)														//Dla du¿ej liczby population nie zawsze wychodzi 100 na koñcu
			tab_values[population - 1].fit_sum = 100.0;
		parents(tab_values, results, indexes, population);														//Znalezienie rodziców na podstawie wylosowanych w ruletce liczb
		free(tab_values);																						//Zwolnienie tablic z wartoœciami i wynikami ruletki
		free(results);
		tab_pop2 = (vtr**)malloc(sizeof(vtr*)*population);														//Alokacja pamiêci na populacjê dzieci
		if (!tab_pop2) {																						//Niepoprawna alokacja koñczy program
			perror("tab_pop2");
			for (int i = 0; i < population; i++)
				delete_vector(&tab_pop[i]);
			free(tab_pop);
			free(max_value);
			free(tab_values);
			free(results);
			free(indexes);
			free(*tab_elem);
			exit(3);
		}
		for (int i = 0; i < population; i++) {
			tab_pop2[i] = create_vector(amount);																//Alokacja pamiêci na poszczególne dzieci
		}
		breed(tab_pop, tab_pop2, indexes, population, probability, amount, &best_index, *tab_elem, backpack);	//Rozma¿anie populacji rodziców i utworzenie populacji dzieci
		free(indexes);																							//Zwolnienie tablicy indeksów
		for (int i = 0; i < population; i++)
			delete_vector(&tab_pop[i]);	
		free(tab_pop);																							//Usuwanie populacji rodzicow
		tab_pop = tab_pop2;																						//Zamiana populacji dzieci na populacje rodzicow w kolejnej iteracji
	}	
	for (int i = 1; i <= iterations; i++) {
		printf("Maksymalna wartosc w %d iteracji: %d\n", i, max_value[i]);
	}
	safe_to_file(name, max_value);																				//Zapis przebiegu maksimum przez wszystkie iteracje do pliku
	free(max_value);																							//Zwolnienie tablicy z maksymalnymi wartosciami
	for (int i = 0; i < population; i++)
		delete_vector(&tab_pop[i]);																				//Usuniêcie populacji rodziców na koñcu programu
	free(tab_pop);
}