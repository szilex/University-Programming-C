#include "bibliotekaY.h"
#include "bibliotekaX.h"
#include <stdio.h>


void bibliotekaY_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Biblioteka Y");
	bibliotekaX_tostring(x);
}