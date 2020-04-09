#include "podmodulA2.h"
#include <stdio.h>

void podmodulA2_tostring(int n)
{
	while (n) { putchar('\t'); n--; }
	puts("Podmodul A2");
}