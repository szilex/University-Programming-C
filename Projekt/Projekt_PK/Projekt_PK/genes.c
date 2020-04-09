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
			size += tab_elem[i].size;																			//Obliczanie sum warto�ci i obj�to�ci
			value += tab_elem[i].value;
		}
	}
	if (size > backpack)																						//Dla obj�to�ci wi�kszej od obj.plecaka zwracamy wsp�czynnik du�o
	return (double)1/(backpack*backpack);																		//mniejszy od teoretycznie najgorszego przypadku (1/backpack)
	else
	return (double)value / backpack;																			//Je�eli nie, zwracamy warto�� przedmiot�w/obj. plecaka
}

void roulette(values* tab_values, double* results, int population){
	for (int i = 0; i < population; i++) {
		results[i] = (double)rand()*100 /RAND_MAX;															//Losowanie N liczb z zakresu <0,100>
	}
}

void parents(values* tab_values, double* results, int* indexes, int population) {
	for (int i = 0, j = 0; i < population&& j< population; i++, j++) {
		if (results[i] <= tab_values[j].fit_sum)																//Dob�r indeks�w rodzic�w na podstawie badania czy
		{																										//wylosowana liczba jest mniejsza b�d� r�wna od 
			indexes[i] = j;																						//warto�ci sumy dla danego rodzica
			j--;																								//(obie tablice posortowane s� rosn�co
		}
		else  i--;
	}
}

void breed(vtr** pop_parents, vtr** pop_children, int* indexes, int population, double probability, int amount, int* best_index, items* tab_elem, int backpack) {
	for (int i = 0; i < population; i+=2) {
		int index1 = rand() % (population - i);
		copy_from_end_vector(pop_parents[indexes[index1]], pop_children[i]);									//Dzieci s� najpierw kopiami swoich rodzic�w
		indexes[index1] = indexes[population -i-1];																//Wylosowany rodzic jest usuwany z dlaszego losowania
		int index2 = rand() % (population - i-1);
		copy_from_end_vector(pop_parents[indexes[index2]], pop_children[i + 1]);
		indexes[index2] = indexes[population -i-2];
		int len = 1+ rand() % (amount-1);																		//Punkt krzy�owania jednopunktowego
		vtr* tail1 = create_vector(len);																		//Tworzenie wektor�w o d�ugo�ci wektor->size-len
		vtr* tail2 = create_vector(len);
		copy_from_end_vector(pop_children[i], tail1);															//Kopiowanie ogon�w
		copy_from_end_vector(pop_children[i + 1], tail2);
		paste_at_end_vector(pop_children[i], tail2) ;															//Wklejanie ogon�w na krzy�
		paste_at_end_vector(pop_children[i + 1], tail1);
		delete_vector(&tail1);																					//Usuwanie ogon�w
		delete_vector(&tail2);
		for (int j = 0; j <amount; j++) {																		//MUTACJA
			double mutation1 = (double)rand() / RAND_MAX , mutation2 = (double)rand() / RAND_MAX ;				//Losowanie liczb z przedzia�u <0,1>
			if (mutation1 <= probability) mutate(pop_children[i], j);											//Mutacja je�eli liczba jest mniejsza od P mutacji
			if (mutation2 <= probability) mutate(pop_children[i + 1], j);
		}
	}
	bool elite = FALSE;																							//ELITARYZM
	double tmp2= adapt(pop_children[0], tab_elem, backpack);													//Dostosawnie pierwszego osobnika z populacji dzieci
	int min = 0;
	double tmp;
	for (int i=1; i < population &&!elite; i++) {
		tmp = adapt(pop_children[i], tab_elem, backpack);
		if (tmp == 1 / (backpack*backpack)) {																	//Szukanie pierwszego elementu o za du�ej obj�to�ci
			paste_at_end_vector(pop_parents[*best_index], pop_children[i]);
			*best_index = i;
			elite = TRUE;
		}
		if (tmp<tmp2){																							//Je�eli nie ma za du�ego rozmiaru, szukamy minimum
			tmp2 = tmp;
			min = i;
		}
	}
	if (!elite) {
		if (tmp2 < adapt(pop_parents[*best_index], tab_elem, backpack)) {										//Je�eli nie wpisano elity sprawdzamy, czy jest lepsza od minimum populacji dzieci
			paste_at_end_vector(pop_parents[*best_index], pop_children[min]);									//Je�eli tak zamieniamy najs�abszego osobnika na elitarnego z populacji rodzic�w
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
	vtr** tab_pop = (vtr**)malloc(sizeof(vtr*) * population);													//Utworzenie pierwszej populacji rodzic�w
	if (!tab_pop) {																								//Niepoprawna alokacja ko�czy program
		perror("tab_pop");
		free(*tab_elem);
		exit(3);
	}						
	for (int i = 0; i < population; i++)
		tab_pop[i] = init_vector(amount);																		//Inicjalizacja populacji
	
	int* max_value = (int*)malloc(sizeof(int)*(iterations+1));													//Tablica przechowuj�ca najwi�kszy rozmiar plecaka po ka�dej iteracji
	if (!max_value) {																							//Niepoprawna alokacja ko�czy program
		perror("tab_pop");
		for (int i = 0; i < population; i++)
			delete_vector(&tab_pop[i]);
		free(tab_pop);
		free(*tab_elem);
		exit(3);
	}
	max_value[0] = 0;																							//Wymienione zmienne s� alokowane i zwalniane w p�tli
	
	values* tab_values;																							//Wska�nik na struktury values
	vtr** tab_pop2;																								//Wska�nik na wektory nowej populacji
	double* results;																							//Wska�nik na wyniki ruletki
	int* indexes;																								//Wska�nik na indeksy wylosowanych rodzic�w
	int best_index;
	
	for (int cycles = 1; cycles <= iterations; cycles++) {
		tab_values = (values*)malloc(sizeof(values)*population);												//Tablica przechowuj�ca struktury z danymi liczbowymi populacji
		if (!tab_values) {																						//Niepoprawna alokacja ko�czy program
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
			tab_values[i].adaptation = adapt(tab_pop[i], *tab_elem, backpack);									//Obliczenie wsp�czynnika adaptacji
			if (tab_values[i].adaptation!=1/(backpack*backpack)&&max_value[cycles] < tab_values[i].adaptation*backpack) {
				max_value[cycles] = (int)(tab_values[i].adaptation*backpack);									//Zmiana maksimum w danej iteracji dla elementu o lepszej adaptacji
				best_index = i;
			}
			sum += tab_values[i].adaptation;
		}
		tab_values[0].fit = tab_values[0].fit_sum = tab_values[0].adaptation * 100 / sum;	
		for (int i = 1; i < population; i++){
			tab_values[i].fit = tab_values[i].adaptation * 100 / sum;											//Wsp�czynnik dopasowania jako wsp. adaptacji/sum� wszystkich wsp. adaptacji (w %)
			tab_values[i].fit_sum = tab_values[i].fit + tab_values[i - 1].fit_sum;								//Suma wszystkich poprzednich i obecnego wsp. dopasowania
			//print_vector(tab_pop[i]);
			//printf("\t\t%f\t%f\t%f\n", tab_values[i].adaptation, tab_values[i].fit, tab_values[i].fit_sum);
		}
		//putc('\n', stdout);
		results = (double*)malloc(sizeof(double)*population);													//Tablica z wynikami losowania ruletk�
		if (!results) {																							//Niepoprawna alokacja ko�czy program
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
		quick(results, 0, population - 1);																		//Sortowanie rosn�ce wynik�w
		indexes = (int*)malloc(sizeof(int)*population);															//Tablica na indeksy wylosowanych rodzic�w
		if (!indexes) {									//Niepoprawna alokacja ko�czy program
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
		if (tab_values[population - 1].fit_sum != 100.0)														//Dla du�ej liczby population nie zawsze wychodzi 100 na ko�cu
			tab_values[population - 1].fit_sum = 100.0;
		parents(tab_values, results, indexes, population);														//Znalezienie rodzic�w na podstawie wylosowanych w ruletce liczb
		free(tab_values);																						//Zwolnienie tablic z warto�ciami i wynikami ruletki
		free(results);
		tab_pop2 = (vtr**)malloc(sizeof(vtr*)*population);														//Alokacja pami�ci na populacj� dzieci
		if (!tab_pop2) {																						//Niepoprawna alokacja ko�czy program
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
			tab_pop2[i] = create_vector(amount);																//Alokacja pami�ci na poszczeg�lne dzieci
		}
		breed(tab_pop, tab_pop2, indexes, population, probability, amount, &best_index, *tab_elem, backpack);	//Rozma�anie populacji rodzic�w i utworzenie populacji dzieci
		free(indexes);																							//Zwolnienie tablicy indeks�w
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
		delete_vector(&tab_pop[i]);																				//Usuni�cie populacji rodzic�w na ko�cu programu
	free(tab_pop);
}