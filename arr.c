#include "arr.h"

void printarr(struct arr x)
{
	int i, size = x.size;
	printf("[");
	for (i = 0; i < size - 1; i++)
		printf("%d, ", x.a[i]);
	printf("%d]", x.a[size - 1]);
}
void printarrln(struct arr x)
{
	printarr(x);
	printf("\n");
}


