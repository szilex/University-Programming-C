#include "modulD.h"
#include "bibliotekaY.h"
#include <stdio.h>


void modulD_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Modul D");
	bibliotekaY_tostring(x);
}