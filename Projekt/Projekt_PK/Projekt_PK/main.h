#ifndef main_h
#define	main_h

#define iterations 100

//Struktura przechowuje informacje o poszczeg�lnych przedmiotach wczytywanych z pliku
struct item {
	char name[15];
	int value;
	int size;
};

typedef struct item items;

#endif 
