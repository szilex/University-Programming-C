#ifndef functions_h
#define functions_h

void quick(double* tab, int left, int right);
//Funkcja sortuj�ca tablic� (quicksort)
//Parametry: tab-tablica liczb double, left-lewy koniec przedzia�u, right-prawy koniec przedzia�u

void read_from_file(char* name, int* backpack, items** tab_elem, int* amount);
//Funkcja odczytuj�ca dane z pliku i zapisuj�ca je do zmiennych przekazanych przez parametry
//Parametry: name-nazwa pliku, backpack-wska�nik na zmienn� przechowuj�c� rozmiar plecaka, 
//tab_elem-wska�nik na tablic� przedmiot�w, amount-wska�nik na zmienn� z ilo�ci� przedmiot�w

void safe_to_file(char* name, int* max_value);
//Funkcja zapisuj�ca przebieg maksymalnej warto�ci przedmiot�w w plecaku przez wszystkie iteracje
//Parametry: name-nazwa pliku wyj�ciowego, max_value-tablica z maksymalnymi warto�ciami
#endif 