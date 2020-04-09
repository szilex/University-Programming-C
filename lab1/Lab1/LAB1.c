#include <stdio.h>

#define N 5

void load(double *tab, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%lf", &tab[i]);
}

void show(const double *tab, int n)
{
	for (int i = 0; i<n; i++, tab++)
		printf("%lf\n", *tab);
}

void minmax(int* idx1, int* idx2, const double *tab)
{
	*idx1 = *idx2 = 0;
	double min = tab[0], max = tab[0];
	for (int i = 1; i < N; i++)
	{
		if (min > tab[i])
		{
			*idx1 = i;
			min = tab[i];
		}
		else
			if (max < tab[i])
			{
				*idx2 = i;
				max = tab[i];
			}
	}
}


int main()
{
	double tab[N];
	load(tab, N);
	show(tab, N);
	int min = tab[0], max = tab[0];
	minmax(&min, &max, tab);
	printf("%d\n%d\n%lf\n%lf", min, max, tab[min], tab[max]);

	int czek;
	scanf("%d", &czek);
	return 0;
}