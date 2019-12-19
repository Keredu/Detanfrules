#ifndef _ARR_H_
#define _ARR_H_

#include <stdio.h>

struct arr {
	int a[256];
	int size;
};

void printarr(struct arr);
void printarrln(struct arr);

#endif
