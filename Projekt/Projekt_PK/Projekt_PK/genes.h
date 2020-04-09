#ifndef genes_h
#define	genes_h


//Struktura przechowuj�ca wsp�czynnik adaptacji, prawdopodobie�stwo (w %) wylosowania oraz sum� prawdopodobie�stw
struct value {
	double adaptation;
	double fit;
	double fit_sum;
};

typedef struct value values;

double adapt(vtr* v, items* tab_elem, int backpack);
//Funkcja obliczaj�ca wsp�czynnik adaptacji jako warto�� plecaka/pojemno��
//Parametry: v-wska�nik na wektor, tab_elem- tablica z elementami plecaka, backpack- rozmiar plecaka

void roulette(values* tab_values, double* results, int population);
//Funkcja losuj�ca warto�ci od 1 do 100
//Parametry: tab_values-tablica z warto�ciami dopasowania osobnik�w, results- tablica wynik�w ruletki, population-liczba osobnik�w w populacji

void parents(values* tab_values, double* results, int* indexes, int population);
//Funkcja odnajduj�ca indeksy wylosowanych element�w
//Parametry: tab_values-tablica z warto�ciami dopasowania osobnik�w, results- tablica wynik�w ruletki,indexes-tablica indeks�w liczb, population-liczba osobnik�w w populacji

void breed(vtr** pop_parents, vtr** pop_children, int* indexes, int population, double probability, int amount, int* best_index, items* tab_elem, int backpack);
//Funkcja krzy�uj�ca osobniki z populacji rodzic�w tworz�c populacj� dzieci
//Parametry: pop_parents-wska�nik na tablic� wektor�w rodzic�w, pop_children-wska�nik na tablic� wektor�w dzieci,
//indexes-tablica indeks�w liczb, population-liczba osobnik�w w populacji, probability-prawdopodobie�stwo mutacji, amount- ilo�� przedmiot�w (d�ugo�� wektor�w)
//best_index-tablica najwi�kszych warto�ci, tab_elem-tablica z przedmiotami, backpack-rozmiar plecaka

void mutate(vtr* v, int i);
//Funkcja mutuj�ca bit wektora (zamieniaj�ca na przeciwny)
//Parametry: v-wska�nik na wektor, i-indeks mutowanego bitu

void genetics(int population, int backpack, int amount, double probability, items** tab_elem, char* name);
//Funkcja przeprowadzaj�ca proces inicjalizacji populacji i jej rozmna�anie przez liczb� cykli r�wn� iteratons
//Parametry: population-liczebno�� populacji, backpack-rozmiar plecaka, amount-liczba przedmiot�w, probability-prawdopodobie�stwo mutacji, 
//tab_elem-wska�nik na tablic� z przedmiotami, name-nazwa pliku wyj�ciowego

#endif 