#include <stdio.h>
#include <string.h>

void alokuj(int rozmiar, void** p);
void zwolnij(void** p);


struct student
{
	char* nazwisko;
	struct student* next;
};

void nowy(struct student** head, char* surname);
void drukuj(struct student** head);
float transformuj(float in_tab1, float in_tab2);
void funkcja(const float* in_tab1, const float* in_tab2, float* out_tab, int n, float (*transformuj)(float, float));


int main()
{
	void* p = NULL;
	alokuj(1000, &p);
	scanf("%s", p);
	printf("%s \n \n", p);
	zwolnij(&p);

	struct student* head = NULL;
	nowy(&head, "Nowak");
	nowy(&head, "Kowalski");
	drukuj(&head);

	const float tab1[3] = { 1.3,3.5,23.6 }, tab2[3] = { 5.3,6.3,4.1 };
	float tab3[3];
	const int trzy = 3;
	funkcja(tab1, tab2, tab3, trzy, transformuj);

	return 0;
}

void alokuj(int rozmiar, void** p)
{
	*p = malloc(rozmiar);
}

void zwolnij(void** p)
{
	free(*p);
	*p = NULL;
}

void nowy(struct student** head, char* surname)
{
	struct student* nowy = malloc(sizeof(struct student));
	nowy->nazwisko = strdup(surname);
	nowy->next = *head;
	*head = nowy;
}

void drukuj(struct student** head)
{
	struct student* tmp;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->nazwisko)
		{
			printf("%s \n", tmp->nazwisko);
			free(tmp->nazwisko);
		}	
		free(tmp);
	}
}

float transformuj(float in_tab1, float in_tab2)
{
	return in_tab1 * in_tab2;	//Funkcja przypisuje do tablicy wyjsciowej iloczyn liczb z wejsciowych
}

void funkcja(const float* in_tab1, const float* in_tab2, float* out_tab, int n, float (*transformuj)(float, float))
{
	for (int i = 0; i < n; i++)
	{
		out_tab[i] = transformuj(in_tab1[i], in_tab2[i]);
		printf("%.3f \n", out_tab[i]);
	}
}