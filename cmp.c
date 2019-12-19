#include "cmp.h"

int cmp(struct rule r1, struct rule r2, enum relation *relations)
{

	int i, j, inr1[r1.size], inr2[r2.size], inboth[r1.size], added;
	int accinr1 = 0, accinr2 = 0, accinboth = 0;
	for (i = 0; i < r1.size; i++) {
		added = 0;
		for (j = 0; j < r2.size; j++){
			if (r1.fields[i].sel == r2.fields[j].sel) {
				inboth[accinboth++] = r1.fields[i].sel;
				added = 1;
				break; 
			}
		}
		if (!added)
			inr1[accinr1++] = r1.fields[i].sel;
	}

	for (i = 0; i < r2.size; i++) {
		added = 0;
		for (j = 0; j < r1.size; j++){
			if (r2.fields[i].sel == r1.fields[j].sel) {
				added = 1;
				break; 
			}
		}
		if (!added)
			inr1[accinr2++] = r2.fields[i].sel;
	}

	int numfields = accinr1 + accinr2 + accinboth;
	int accr = 0, k;

	for (i = 0; i < accinr1; i++)
		relations[accr++] = SUPERSET; // At least one * in r2

	for (i = 0; i < accinr2; i++)
		relations[accr++] = SUBSET; // At least one * in r1
	
	for (k = 0; k < accinboth; k++)
		for (i = 0; i < r1.size; i++)
			for (j = 0; j < r2.size; j++)
				if (inboth[k] == r1.fields[i].sel && 
					inboth[k] == r2.fields[j].sel)
					relations[accr++] = frel(r1,r2, i, j);

	return numfields;

}

enum relation frel(struct rule r1, struct rule r2, int a, int b)
{
	struct field f1 = r1.fields[a];
	struct field f2 = r2.fields[b];
	enum relation rel = -2;
	int type1 = r1.fields[a].type;
	int type2 = r2.fields[b].type;
	int type = type1*10+type2;
	int include = 0, eq = 0;
	int i, j, minf1, maxf1, minf2, maxf2;

	switch(type){
		case SINGLETON_SINGLETON:
			if (f1.value == f2.value)
				rel = EQUALS;
			else
				rel = NOT_EQUALS;
			break;
		case SINGLETON_RANGE:
			// We are assuming that r2.x <= r2.y
			if (f1.value >= f2.range.x || f1.value <= f2.range.y)
				rel = SUPERSET;
			else
				rel = NOT_EQUALS;
			break;
		case SINGLETON_SET:
			for(i = 0; i < f2.set.size; i++)
				if (f2.set.elems[i] == f1.value){
					include = 1;
					break;
				}
			if (include)
				rel = SUPERSET;
			else
				rel = NOT_EQUALS;
			break;
		case RANGE_SINGLETON:
			if (f2.value >= f1.range.x || f2.value <= f1.range.y)
				rel = SUBSET;
			else
				rel = NOT_EQUALS;
			break;
		case RANGE_RANGE:
			minf1 = f1.range.x;
			maxf1 = f1.range.y;
			minf2 = f2.range.x;
			maxf2 = f2.range.y;

			if (minf1 > maxf2 || minf2 > maxf1)
				rel = NOT_EQUALS;
			else {
				if (minf1 > minf2) {
					if (maxf1 > maxf2)
						rel = CORRELATED;
					else
						rel = SUPERSET;
				} else if (minf1 < minf2) {
					if (maxf1 < maxf2)
						rel = CORRELATED;
					else
						rel = SUBSET;
				} else {
					if (maxf1 > maxf2)
						rel = SUBSET;
					else if (maxf1 < maxf2)
						rel = SUPERSET;
					else
						rel = EQUALS;
				}
			}
				
			break;
		case RANGE_SET:
			minf1 = f1.range.x;
			maxf1 = f1.range.y;
			minf2 = findmin(f2.set.elems,f2.set.size);
			maxf2 = findmax(f2.set.elems,f2.set.size);

			if (minf1 > maxf2 || minf2 > maxf1)
				rel = NOT_EQUALS;
			else {
				if (minf1 > minf2) {
					if (maxf1 > maxf2)
						rel = CORRELATED;
					else
						rel = SUPERSET;
				} else if (minf1 < minf2) {
					if (maxf1 < maxf2)
						rel = CORRELATED;
					else
						rel = SUBSET;
				} else {
					if (maxf1 > maxf2)
						rel = SUBSET;
					else if (maxf1 < maxf2)
						rel = SUPERSET;
					else
						rel = EQUALS;
				}
			}
			break;
		case SET_SINGLETON:
			for(i = 0; i < f1.set.size; i++)
				if (f1.set.elems[i] == f2.value){
					include = 1;
					break;
				}
			if (include)
				rel = SUBSET;
			else
				rel = NOT_EQUALS;
			break;
		case SET_RANGE:
			minf1 = findmin(f1.set.elems, f1.set.size);
			maxf1 = findmax(f2.set.elems, f2.set.size);
			minf2 = f2.range.x;
			maxf2 = f2.range.y;

			if (minf1 > maxf2 || minf2 > maxf1)
				rel = NOT_EQUALS;
			else {
				if (minf1 > minf2) {
					if (maxf1 > maxf2)
						rel = CORRELATED;
					else
						rel = SUPERSET;
				} else if (minf1 < minf2) {
					if (maxf1 < maxf2)
						rel = CORRELATED;
					else
						rel = SUBSET;
				} else {
					if (maxf1 > maxf2)
						rel = SUBSET;
					else if (maxf1 < maxf2)
						rel = SUPERSET;
					else
						rel = EQUALS;
				}
			}
			break;
		case SET_SET:
			if (f1.set.size == f2.set.size) {
				for (i = 0; i < f1.set.size; i++)
					if (f1.set.elems[i] == f2.set.elems[i])
						eq++;
				if (eq == f1.set.size)
					rel = EQUALS;
				else if (eq == 0)
					rel = NOT_EQUALS;
				else
					rel = CORRELATED;
			} else {
				for (i = 0; i < f1.set.size; i++)
					for (j = 0; j < f2.set.size; j++)
						if (f1.set.elems[i] == f2.set.elems[j])
							eq++;
				if (eq == f1.set.size)
					rel = SUPERSET;
				else if (eq == f2.set.size)
					rel = SUBSET;
				else if (eq == 0)
					rel = NOT_EQUALS;
				else 
					rel = CORRELATED;
			}	
			break;
		default:
			rel = -1;
	}

	if (rel == -1 || rel == -2)
		printf("err in frel function: res = %d\n", rel);

	return rel;
}

int findmax(int *a, int tam)
{
	int res = a[0];
	int i;
	for (i = 1; i < tam; i++)
		if (a[i] > res)
			res = a[i];
	return res;
}

int findmin(int *a, int tam)
{
	int res = a[0];
	int i;
	for (i = 1; i < tam; i++)
		if (a[i] < res)
			res = a[i];
	return res;
}



