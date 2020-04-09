#ifndef vector_h
#define vector_h

//Struktura reprezentuj�ca bit (warto�ci 0 i 1)
enum boolean{
	FALSE = 0,
	TRUE = 1
};

//Struktura reprezentuj�ca wektor o d�ugo�ci size zawieraj�ca ci�g bit�w data
struct vector {
	int size;
	enum boolean* data;
};

typedef enum boolean bool;
typedef struct vector vtr;

vtr* init_vector(int n);
//Funkcja tworz�ca wektor, kt�ra od razu inicjuje go warto�ciami losowymi 
//Parametr: n-d�ugo�� wektora    Warto�� zwracana: wska�nik na zainicjalizowany wektor

vtr* create_vector(int n);
//Funkcja tworz�ca wektor, kt�ra nie inicjuje jego warto�ci
//Parametr: n-d�ugo�� wektora    Warto�� zwracana: wska�nik na utworzony wektor

void copy_from_end_vector(vtr* v1, vtr* v2);
//Funkcja kopiuj�ca wektor o d�ugo�ci wektora v2 z ko�ca wektora v1
//Parametry: v1-wska�nik na wektor od kt�rego kopiowany jest ogon, v2-wska�nik na wektor do kt�rego zapisany zostanie ogon

void paste_at_end_vector(vtr* v1, vtr* v2);
//Funkcja zamieniaj�ca koniec wektora v1 na wektor v2
//Parametry: v1-wska�nik na wektor modyfikowany, v2-wska�nik na wektor wstawiany

void delete_vector(vtr** v);
//Funkcja zwalniaj�ca wska�nik na zawarto�� wektora oraz na wektor
//Parametr: v-wska�nik na wska�nik na usuwany wektor

int resize_vector(vtr* v, int n);
//Funkcja zmieniaj�ca d�ugo�� wektora na n
//Parametry: v-wska�nik na wektor, n-nowa d�ugo��	Warto�� zwracana: nowa d�ugo�� wektora 

bool get_vector(vtr* v, int i);
//Funkcja zwracaj�ca jeden znak z wektora
//Parametry: v-wska�nik na wektor, i-indeks elementu w wektorze		Warto�� zwracana: warto�� bitu wektora

void load_vector(vtr* v, int i, bool t);
//Funkcja zmieniaj�ca bit na pozycji i w wektorze na t
//Parametry: v-wska�nik na wektor, i-indeks elementu w wektorze, t-nowa warto�� bitu

void print_vector(vtr* v);
//Funkcja drukuj�ca zawarto�� wektora (ci�g bit�w)
//Parametry: v-wska�nik na wektor

#endif 
