#ifndef main_h
#define	main_h

#define iterations 100

//Struktura przechowuje informacje o poszczególnych przedmiotach wczytywanych z pliku
struct item {
	char name[15];
	int value;
	int size;
};

typedef struct item items;

#endif 
