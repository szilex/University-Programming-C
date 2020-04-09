#include "modulC.h"
#include "podmodulC1.h"
#include <stdio.h>


void modulC_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Modul C");
	podmodulC1_tostring(x);
}