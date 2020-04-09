#include "podmodulA1.h"
#include "bibliotekaX.h"
#include <stdio.h>

void podmodulA1_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Podmodul A1");
	bibliotekaX_tostring(x);
}