#ifndef _MULTIGRAPH_H_
#define _MULTIGRAPH_H_

#include <stdio.h>

enum relation {
	EQUALS = 1,
	SUBSET = 2,
	SUPERSET = 3,
	NOT_EQUALS = 4,
	CORRELATED = 5
};

enum cmp_type{
	SINGLETON_SINGLETON = 0,
	SINGLETON_RANGE = 1,
	SINGLETON_SET = 2,
	RANGE_SINGLETON = 10,
	RANGE_RANGE = 11,
	RANGE_SET = 12,
	SET_SINGLETON = 20,
	SET_RANGE = 21,
	SET_SET = 22
};

enum node {
	NODE_0, NODE_1, NODE_2, NODE_3, NODE_4,
	NODE_5, NODE_6, NODE_7, NODE_8, NODE_9,
	DISJOINT, SHADOWED, REDUNDANCY, GENERALIZED,
	NODE_CORRELATED, PARCIALLY_CORRELATED  

};

const char* getNode(enum node);
const char* getRel(enum relation);

#endif
