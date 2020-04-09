#include "program.h"
#include "bibliotekaX.h"
#include "modulA.h"
#include "modulB.h"
#include "modulC.h"
#include "modulD.h"
#include <stdio.h>

void program_tostring(int n)
{
	int x = n + 1;
	while (n) { putchar('\t'); n--; }
	puts("Program");
	bibliotekaX_tostring(x);
	modulA_tostring(x);
	modulB_tostring(x);
	modulC_tostring(x);
	modulD_tostring(x);
}

int main()

{
	int n = 0;
	program_tostring(n);
	n = getchar();
	return 0;
}