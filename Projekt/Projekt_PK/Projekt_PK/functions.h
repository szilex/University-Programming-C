#ifndef functions_h
#define functions_h

void quick(double* tab, int left, int right);
//Funkcja sortuj¹ca tablicê (quicksort)
//Parametry: tab-tablica liczb double, left-lewy koniec przedzia³u, right-prawy koniec przedzia³u

void read_from_file(char* name, int* backpack, items** tab_elem, int* amount);
//Funkcja odczytuj¹ca dane z pliku i zapisuj¹ca je do zmiennych przekazanych przez parametry
//Parametry: name-nazwa pliku, backpack-wskaŸnik na zmienn¹ przechowuj¹c¹ rozmiar plecaka, 
//tab_elem-wskaŸnik na tablicê przedmiotów, amount-wskaŸnik na zmienn¹ z iloœci¹ przedmiotów

void safe_to_file(char* name, int* max_value);
//Funkcja zapisuj¹ca przebieg maksymalnej wartoœci przedmiotów w plecaku przez wszystkie iteracje
//Parametry: name-nazwa pliku wyjœciowego, max_value-tablica z maksymalnymi wartoœciami
#endif 