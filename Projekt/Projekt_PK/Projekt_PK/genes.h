#ifndef genes_h
#define	genes_h


//Struktura przechowuj¹ca wspó³czynnik adaptacji, prawdopodobieñstwo (w %) wylosowania oraz sumê prawdopodobieñstw
struct value {
	double adaptation;
	double fit;
	double fit_sum;
};

typedef struct value values;

double adapt(vtr* v, items* tab_elem, int backpack);
//Funkcja obliczaj¹ca wspó³czynnik adaptacji jako wartoœæ plecaka/pojemnoœæ
//Parametry: v-wskaŸnik na wektor, tab_elem- tablica z elementami plecaka, backpack- rozmiar plecaka

void roulette(values* tab_values, double* results, int population);
//Funkcja losuj¹ca wartoœci od 1 do 100
//Parametry: tab_values-tablica z wartoœciami dopasowania osobników, results- tablica wyników ruletki, population-liczba osobników w populacji

void parents(values* tab_values, double* results, int* indexes, int population);
//Funkcja odnajduj¹ca indeksy wylosowanych elementów
//Parametry: tab_values-tablica z wartoœciami dopasowania osobników, results- tablica wyników ruletki,indexes-tablica indeksów liczb, population-liczba osobników w populacji

void breed(vtr** pop_parents, vtr** pop_children, int* indexes, int population, double probability, int amount, int* best_index, items* tab_elem, int backpack);
//Funkcja krzy¿uj¹ca osobniki z populacji rodziców tworz¹c populacjê dzieci
//Parametry: pop_parents-wskaŸnik na tablicê wektorów rodziców, pop_children-wskaŸnik na tablicê wektorów dzieci,
//indexes-tablica indeksów liczb, population-liczba osobników w populacji, probability-prawdopodobieñstwo mutacji, amount- iloœæ przedmiotów (d³ugoœæ wektorów)
//best_index-tablica najwiêkszych wartoœci, tab_elem-tablica z przedmiotami, backpack-rozmiar plecaka

void mutate(vtr* v, int i);
//Funkcja mutuj¹ca bit wektora (zamieniaj¹ca na przeciwny)
//Parametry: v-wskaŸnik na wektor, i-indeks mutowanego bitu

void genetics(int population, int backpack, int amount, double probability, items** tab_elem, char* name);
//Funkcja przeprowadzaj¹ca proces inicjalizacji populacji i jej rozmna¿anie przez liczbê cykli równ¹ iteratons
//Parametry: population-liczebnoœæ populacji, backpack-rozmiar plecaka, amount-liczba przedmiotów, probability-prawdopodobieñstwo mutacji, 
//tab_elem-wskaŸnik na tablicê z przedmiotami, name-nazwa pliku wyjœciowego

#endif 