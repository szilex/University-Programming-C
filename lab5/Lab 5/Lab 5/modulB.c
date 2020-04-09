#include "modulB.h"
#include <stdio.h>


void modulB_tostring(int n)
{
	while (n) { putchar('\t'); n--; }
	puts("Modul B");
}