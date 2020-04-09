#include "bibliotekaX.h"
#include <stdio.h>


void bibliotekaX_tostring(int n)
{
	while (n) { putchar('\t'); n--; }
	puts("Biblioteka X");
}