#include <stdio.h>
#include "rule.h"

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
	
	printrs(rs);

	return 0;
}
