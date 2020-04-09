#include <stdio.h>
#include <conio.h>
#include <string.h>
enum stan
{
	wybor,
	odtwarzanie,
	koniec
};

enum zdarzenia
{
	rozpocznij,
	zatrzymaj,
	zakoncz
};

void wyswietl_rozp()
{
	printf("Rozpoczeto odtwarzanie\n\n");
}

void wyswietl_zak()
{
	printf("Zakonczono odtwarzanie\n\n");
}

void nic()
{}

void wybor_gatunku(char* gatunek)
{
	const char* gatunki[5] = { "Pop","Rock","Reagge","Klasyczna","Rap" };
	printf("Dostepne gatunki: \n%s\n%s \n%s \n%s \n%s \n", gatunki[0], gatunki[1], gatunki[2], gatunki[3], gatunki[4]);
	int correct_genre = 0;
	while (!correct_genre)
	{
		scanf("%s", gatunek);
		int i = 0;
		for (; i < 5 && !correct_genre; i++)
			if (!strcmp(gatunek, gatunki[i]))
				correct_genre = 1;
		if (i == 5 && !correct_genre)
			printf("Brak podanego gatunku\n");
	}
}

void odtwarzanie_gatunku(char* gatunek)
{
	printf("Odtwarzam: %s\n", gatunek);
}

void zakonczenie(char* gatunek)
{
	printf("Koniec programu");
}

typedef void(*Akcja)(char*);
typedef void(*Akcja_zmiany)();

int main()
{
	enum stan przejscia[3][3] = { odtwarzanie, wybor, koniec, odtwarzanie, wybor, koniec, koniec, koniec, koniec };
	enum stan s = wybor;

	Akcja akcje[3] = { wybor_gatunku, odtwarzanie_gatunku, zakonczenie };
	Akcja_zmiany akcje_zmiany[3][3] = { nic, wyswietl_rozp, nic, wyswietl_zak, nic, nic, nic, nic, nic };
	char gatunek[1000];
	(akcje[s])(gatunek);	//Na poczatku wybieramy jakis gatunek

	while (s != koniec)
	{
		printf("\nCo chcesz zrobic:\nWybrac gatunek[S]\nOdtworzyc utwor[P]\nZakonczyc[Esc]\n\n");
		while (!kbhit()) {};
		enum zdarzenia z;

		char c = getch();
		int correct = 0;

		switch (c)
		{
		case 'P': 	z = rozpocznij; correct = 1; break;
		case 'S':	z = zatrzymaj; correct = 1; break;
		case 27:	z = zakoncz; correct = 1; break;
		}

		if (correct)
		{
			enum stan nast_stan = przejscia[s][z];
			akcje_zmiany[s][nast_stan]();
			s = nast_stan;
			(akcje[s])(gatunek);

		}
		else
			printf("Bledny klawisz\n");
	}
	return 0;
}