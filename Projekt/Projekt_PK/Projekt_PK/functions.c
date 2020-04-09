#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "vector.h"
#include "functions.h"



void quick(double* tab, int left, int right)
{
	int i = left;
	int j = right;
	double x = tab[(left + right) / 2];
	do
	{
		while (tab[i] < x)	i++;
		while (tab[j] > x)	j--;
		if (i <= j)
		{
			double temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) quick(tab, left, j);
	if (right > i) quick(tab, i, right);
}

void read_from_file(char* name, int* backpack, items** tab_elem, int* amount)
{
	FILE* file = fopen(name, "rb");
	if (!file) {
		perror("Plik wejsciowy");
		exit(4);
	}
	fseek(file, 0, SEEK_END);
	int flength = ftell(file);
	if (flength < 9) {							//9 to d³ugoœæ frazy: "Plecak: x"
		perror("Plik jest za krotki");
		exit(4);
	}
	//printf("Dlugosc pliku: %d\n", flength);
	fseek(file, 0, SEEK_SET);
	char* buffer = (char*)malloc(sizeof(char)*(flength+1));
	if (!buffer) {									//B³êdna alokacja koñczy program
		perror("buffer");
		free(*tab_elem);
		exit(4);
	}
	fread(buffer, sizeof(char), flength, file);		//Odczytanie zawartoœci pliku do bufora
	buffer[flength ] = '\0';
	fclose(file);
	(*amount) = 0;
	for (int i = 0; i <= flength; i++)
	{
		if (buffer[i] == '\n' || i == flength)		//Zliczenie iloœci wierszy
			(*amount)++;
	}
	(*amount)--;
	printf("Ilosc itemow: %d\n", (*amount));

	if ((*amount) > 0) {
		(*tab_elem) = (items*)malloc(sizeof(items)*(*amount));
		char *temp = strtok(buffer, " \r\n");
		if (!strcmp(temp, "Plecak:")) {
			temp = strtok(NULL, " \r\n");
			if (temp) 
				(*backpack) = atoi(temp);
			else {
				perror("Plecak");
				free((*tab_elem));
				free(temp);
				free(buffer);
				exit(4);
			}
			if (*backpack <= 0)
			{
				perror("Rozmiar plecaka");
				free((*tab_elem));
				free(temp);
				free(buffer);
				exit(4);
			}
			temp = strtok(NULL, " \r\n");
			if (temp) 
				strcpy((*tab_elem)[0].name, temp);
			temp = strtok(NULL, " \r\n");
			if (temp) 
				(*tab_elem)[0].value = atoi(temp);
			temp = strtok(NULL, " \r\n");
			if (temp) 
				(*tab_elem)[0].size = atoi(temp);
			printf("%s %d %d\n", (*tab_elem)[0].name, (*tab_elem)[0].value, (*tab_elem)[0].size);
			if ((*amount) > 1) {
				int counter = 1;
				temp = strtok(NULL, " \r\n");
				while (temp != NULL)
				{
					
					strcpy((*tab_elem)[counter].name, temp);
					temp = strtok(NULL, " \r\n");
					if (temp) 
						(*tab_elem)[counter].value = atoi(temp);
					temp = strtok(NULL, " \r\n");
					if (temp) 
						(*tab_elem)[counter].size = atoi(temp);
					printf("%s %d %d\n", (*tab_elem)[counter].name, (*tab_elem)[counter].value, (*tab_elem)[counter].size);
					temp = strtok(NULL, " \r\n");
					counter++;
				}
			}
			free(temp);
			free(buffer);
			int j = 0;
			for (int i = 0; i < (*amount); i++) {
				if (!(*tab_elem)[i].size || !(*tab_elem)[i].name || !(*tab_elem)[i].value) {
					perror("Brak danej przedmiotu");
					free((*tab_elem));
					exit(4);
				}
				if ((*tab_elem)[i].size >(*backpack)) 
					j++;
			}
			if (j == (*amount)) {
				perror("Zaden przedmiot nie zmiesci siê w plecaku");
				free((*tab_elem));
				exit(4);
			}
		}
		else
		{
			perror("Rozmiar plecaka");
			free(buffer);
			free((*tab_elem));
			exit(4);
		}
	}
	else {
		perror("Brak przedmiotow");
		free(buffer);
		free((*tab_elem));
		exit(4);
	}
}

void safe_to_file(char* name, int* max_value) {
	FILE* file = fopen(name, "w");
	if (!file)
		printf("Zapis do pliku nie powiód³ siê/n");
	else {
		for (int i = 1; i <= iterations; i++) 
			fprintf(file, "Maksymalna wartoœæ plecaka po %d iteracji: %d\n", i, max_value[i]);
	}
	fclose(file);
}