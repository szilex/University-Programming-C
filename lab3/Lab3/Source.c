#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Source.h"

void kopiuj(FILE* out_file, char* bufor, int size)
{
	fwrite(bufor, 1, size, out_file);
}

void zamien(FILE* out_file, char* bufor, int size)
{
	char* ptr = bufor;
	while (*ptr)
	{
		if (isupper(*ptr))
			*ptr = tolower(*ptr);
		else
		{
			if (islower(*ptr))
				*ptr = toupper(*ptr);
		}
		ptr++;
	}
	fwrite(ptr, 1, size, out_file);
}

void palindrom(FILE* out_file, char* bufor)
{
	const char korektor[] = " \t\r\n";
	char* bufor2;
	bufor2 = strtok(bufor, korektor);
	while (bufor2 != NULL)
	{
		int size = strlen(bufor2), koniec=1;
		for (int i = 0, j = size - 2; i <= j&&koniec; i++, j--)
			if (bufor2[i] != bufor2[j])
				koniec = 0;
		if (koniec)
			fprintf(out_file,"%s ", bufor2);	//palindromy s¹ oddzielone spacj¹
		bufor2 = strtok(NULL, korektor);
	}

}

int main(int argc, char *argv[])
{
	if (argc != 4)
		printf("blad");
	else
	{
		char* option[3] = { "-copy","-replace","-palindrom" };
		char* file_in=argv[1], *file_out=argv[2];
		int choice;
		if (!strcmp(argv[3], option[0]))
			choice = 1;
		else
		{
			if (!strcmp(argv[3], option[1]))
				choice = 2;
			else
			{
				if (!strcmp(argv[3], option[2]))
					choice = 3;
				else
				{
					printf("blad");
					choice = 4;
				}
			}
		}

		if (choice < 4)
		{
			FILE* plik_we, *plik_wy;
			plik_we = fopen(file_in, "rb");
			plik_wy = fopen(file_out, "wb");
			fseek(plik_we, 0, SEEK_END);
			int  size = ftell(plik_we);
			char* buffor = (char*)malloc(sizeof(char)*(size + 1));
			fseek(plik_we, 0, SEEK_SET);
			fread(buffor,1, size, plik_we);
			buffor[size] = '\0';
			switch (choice) 
			{
			case 1: {kopiuj(plik_wy, buffor, size); break; }
			case 2: {zamien(plik_wy, buffor, size); break; }
			case 3: {palindrom(plik_wy, buffor); break; }
			}	
		}

	}
	return 0;
}

/* 
char* p="abc"
if (!strcmp(a,b))      - strcmp porównuje i zwraca 0 jeœli a i b s¹ takie same
strlen(p)- d³ugoœæ ³añcucha pod wskaŸnikiem p
*/
