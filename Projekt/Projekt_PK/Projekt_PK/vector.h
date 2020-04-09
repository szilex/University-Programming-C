#ifndef vector_h
#define vector_h

//Struktura reprezentuj¹ca bit (wartoœci 0 i 1)
enum boolean{
	FALSE = 0,
	TRUE = 1
};

//Struktura reprezentuj¹ca wektor o d³ugoœci size zawieraj¹ca ci¹g bitów data
struct vector {
	int size;
	enum boolean* data;
};

typedef enum boolean bool;
typedef struct vector vtr;

vtr* init_vector(int n);
//Funkcja tworz¹ca wektor, która od razu inicjuje go wartoœciami losowymi 
//Parametr: n-d³ugoœæ wektora    Wartoœæ zwracana: wskaŸnik na zainicjalizowany wektor

vtr* create_vector(int n);
//Funkcja tworz¹ca wektor, która nie inicjuje jego wartoœci
//Parametr: n-d³ugoœæ wektora    Wartoœæ zwracana: wskaŸnik na utworzony wektor

void copy_from_end_vector(vtr* v1, vtr* v2);
//Funkcja kopiuj¹ca wektor o d³ugoœci wektora v2 z koñca wektora v1
//Parametry: v1-wskaŸnik na wektor od którego kopiowany jest ogon, v2-wskaŸnik na wektor do którego zapisany zostanie ogon

void paste_at_end_vector(vtr* v1, vtr* v2);
//Funkcja zamieniaj¹ca koniec wektora v1 na wektor v2
//Parametry: v1-wskaŸnik na wektor modyfikowany, v2-wskaŸnik na wektor wstawiany

void delete_vector(vtr** v);
//Funkcja zwalniaj¹ca wskaŸnik na zawartoœæ wektora oraz na wektor
//Parametr: v-wskaŸnik na wskaŸnik na usuwany wektor

int resize_vector(vtr* v, int n);
//Funkcja zmieniaj¹ca d³ugoœæ wektora na n
//Parametry: v-wskaŸnik na wektor, n-nowa d³ugoœæ	Wartoœæ zwracana: nowa d³ugoœæ wektora 

bool get_vector(vtr* v, int i);
//Funkcja zwracaj¹ca jeden znak z wektora
//Parametry: v-wskaŸnik na wektor, i-indeks elementu w wektorze		Wartoœæ zwracana: wartoœæ bitu wektora

void load_vector(vtr* v, int i, bool t);
//Funkcja zmieniaj¹ca bit na pozycji i w wektorze na t
//Parametry: v-wskaŸnik na wektor, i-indeks elementu w wektorze, t-nowa wartoœæ bitu

void print_vector(vtr* v);
//Funkcja drukuj¹ca zawartoœæ wektora (ci¹g bitów)
//Parametry: v-wskaŸnik na wektor

#endif 
