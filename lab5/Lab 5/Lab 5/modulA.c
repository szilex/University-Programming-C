#include "modulA.h"
#include "podmodulA1.h"
#include "podmodulA2.h"
#include "bibliotekaX.h"
#include <stdio.h>


void modulA_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Modul A");
	bibliotekaX_tostring(x);
	podmodulA1_tostring(x);
	podmodulA2_tostring(x);
}