#include <stdio.h>
#include <stdlib.h>
#include "cmp.h"
#include "arr.h"

int main()
{
	printf("Running %s\n",__FILE__);

	struct rule r0 = {
		.fields[0] = {0, 1, .range = {2, 8}},
		.fields[1] = {2, 0, 4},
		.fields[2] = {3, 2, .set = {{1, 5, 2}, 3}},
		.fields[3] = {4, 0, 3},
		.fields[4] = {255, 0, 1},
		.size = 5};

	struct rule r1 = {
		 .fields[0] = {0, 0, 4},
		 .fields[1] = {2, 1, .range = {2, 8}},
		 .fields[2] = {3, 2, .set = {{1, 3, 2}, 3}},
		 .fields[3] = {255, 0, 0},
		 .size = 4};

	struct rule r2 = {
		.fields[0] = {0, 0, 4},
		.fields[1] = {1, 0, 3},
		.fields[2] = {2, 2, .set = {{3, 4, 5}, 3}},
		.fields[3] = {255, 0, 0},
		.size = 4};

	struct ruleset rs = {
		.rules[0] = r0,
		.rules[1] = r1,
		.rules[2] = r2,
		.size = 3};

	int i, j, h, x, numfields, k = 0;
	/*struct arr real_relations[] = {
		{.a[0] = 3, .a[1] = 2, .a[2] = 3, .a[3] = 5, .a[4] = 4, .size = 5},
		{.a[0] = 3, .a[1] = 3, .a[2] = 2, .a[3] = 2, .a[4] = 3, .a[5] = 4, .size = 6},
		{.a[0] = 3, .a[1] = 2, .a[2] = 1, .a[3] = 2, .a[4] = 1, .size = 5}
	};*/

	for (i = 0; i < rs.size - 1; i++)
		for (j = i + 1; j < rs.size; j++){
			enum relation relations[6];
			printf("\nComparing rule %d with rule %d\n", i, j);
			numfields = cmp(rs.rules[i], rs.rules[j], relations);
			//for (x = 0; x < numfields; x++) 
			//		myarr.a[x] = relations[x];
			//myarr.size = numfields;

			printf("Relations = [");
			for (x = 0; x < numfields - 1; x++)
				printf("%s, ", getRel(relations[x]));
			printf("%s]\n", getRel(relations[numfields - 1]));
			//printf("Real Rels = ");
			//printarrln(real_relations[k++]);
		}





	return 0;
}
