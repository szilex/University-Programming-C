#include "podmodulC1.h"
#include "bibliotekaY.h"
#include <stdio.h>

void podmodulC1_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Podmodul C1");
	bibliotekaY_tostring(x);
}