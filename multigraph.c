#include <stdio.h>
#include "multigraph.h"

const char* getNode(enum node n)
{
	switch (n) {
		case NODE_0: return "NODE_0";
		case NODE_1: return "NODE_1";
		case NODE_2: return "NODE_2";
		case NODE_3: return "NODE_3";
		case NODE_4: return "NODE_4";
		case NODE_5: return "NODE_5";
		case NODE_6: return "NODE_6";
		case NODE_7: return "NODE_7";
		case NODE_8: return "NODE_8";
		case NODE_9: return "NODE_9";
		case DISJOINT: return "DISJOINT";
		case SHADOWED: return "SHADOWED";
		case REDUNDANCY: return "REDUNDANCY";
		case GENERALIZED: return "GENERALIZED";
		case NODE_CORRELATED: return "CORRELATED";
		case PARCIALLY_CORRELATED: return "PARCIALLY CORRELATED";
		default: return "Error in getNode";
	}
}

const char* getRel(enum relation rel)
{
	switch (rel) {
		case EQUALS: return "DISJOINT";
		case SUBSET: return "SHADOWED";
		case SUPERSET: return "REDUNDANCY";
		case NOT_EQUALS: return "GENERALIZED";
		case CORRELATED: return "CORRELATED";
		default: return "Error in getRel";
	}
}
