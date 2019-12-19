#include "anomalies.h"

void anomalies (struct ruleset rs)
{
	int i,j, a;
	for (i = 0; i < rs.size - 1; i++)
		for (j = i + 1; j < rs.size; j++) {
			a = anomaly(rs.rules[i], rs.rules[j]);
			if (a != 10)
				printa(i, j, a);
		}
}

enum node anomaly (struct rule r1, struct rule r2)
{
//	struct arr myarr;
	int i;
	enum relation r, relations[256];
	enum node n = NODE_0;
	int numfields = cmp(r1, r2, relations);
/*
	for (i = 0; i < numfields; i++) 
		myarr.a[i] = relations[i];
	myarr.size = numfields;
*/
	for (i = 0; i < numfields - 2; i++) {		
		r = relations[i];
		n = nn(r, n, 0);
	}
	r = relations[i];
	n = nn(r, n, 1);
	i++;
	r = relations[i];
	n = fn(r, n);
	
	return n;
}

enum node nn(enum relation r, enum node n, int lf)
{
	int res;

	if (r == NOT_EQUALS || n == SHADOWED)
		return SHADOWED;
	if (r == CORRELATED)
		return n;
	switch (n) {
	case NODE_0:
		if (r == EQUALS)
			res = NODE_1;
		else if (r == SUBSET)
			res = NODE_2;
		else if (r == SUPERSET)
			res = NODE_3;
		else
			res = -1;
		break;
	case NODE_1:
		if (r == EQUALS)
			res = NODE_4;
		else if (r == SUBSET)
			res = NODE_5;
		else if (r == SUPERSET)
			res = NODE_6;
		else
			res = -1;
		break;
	case NODE_2:
		if (r == EQUALS)
			res = NODE_5;
		else if (r == SUBSET)
			res = NODE_5;
		else if (r == SUPERSET)
			res = NODE_7;
		else
			res = -1;
		break;
	case NODE_3:
		if (r == EQUALS)
			res = NODE_6;
		else if (r == SUBSET)
			res = NODE_7;
		else if (r == SUPERSET)
			res = NODE_6;
		else
			res = -1;
		break;
	case NODE_4:
		if (lf) {
			if (r == EQUALS)
				res = NODE_8;
			else if (r == SUBSET)
				res = NODE_8;
			else if (r == SUPERSET)
				res = NODE_9;
			else
				res = -1;
		} else {
			if (r == EQUALS)
				res = NODE_4;
			else if (r == SUBSET)
				res = NODE_5;
			else if (r == SUPERSET)
				res = NODE_6;
			else
				res = -1;
		}
		break;
	case NODE_5:
		if (lf) {
			if (r == EQUALS)
				res = NODE_8;
			else if (r == SUBSET)
				res = NODE_8;
			else if (r == SUPERSET)
				res = NODE_7;
			else
				res = -1;
		}
		else {
			if (r == EQUALS)
				res = NODE_5;
			else if (r == SUBSET)
				res = NODE_5;
			else if (r == SUPERSET)
				res = NODE_7;
			else
				res = -1;
		}
		break;
	case NODE_6:
		if (lf) {
			if (r == EQUALS)
				res = NODE_9;
			else if (r == SUBSET)
				res = NODE_7;
			else if (r == SUPERSET)
				res = NODE_9;
			else
				res = -1;
		}
		else {
			if (r == EQUALS)
				res = NODE_6;
			else if (r == SUBSET)
				res = NODE_7;
			else if (r == SUPERSET)
				res = NODE_6;
			else
				res = -1;
		}
		break;
	case NODE_7:
		if (r == EQUALS)
			res = NODE_7;
		else if (r == SUBSET)
			res = NODE_7;
		else if (r == SUPERSET)
			res = NODE_7;
		else
			res = -1;
		break;
	default:
		res = -1;
	}
	return res;
}

enum node fn(enum relation r, enum node n)
{	
	enum node res;
	//if (p > 0 && e == 0)
	//	res = 15; // estado ficticio, por si todos son 5
	//else
	//	res = -3;
	switch (n) {
		case NODE_1:
			res = (r == NOT_EQUALS)?SHADOWED:REDUNDANCY;
			break;
		case NODE_2:
			res = (r == NOT_EQUALS)?SHADOWED:REDUNDANCY;
			break;
		case NODE_3:
			res = (r == EQUALS)?REDUNDANCY:GENERALIZED;
			break;
		case NODE_4:
			res = (r == NOT_EQUALS)?SHADOWED:REDUNDANCY;
			break;
		case NODE_5:
			res = (r == NOT_EQUALS)?SHADOWED:REDUNDANCY;
			break;
		case NODE_6:
			res = (r == EQUALS)?REDUNDANCY:GENERALIZED;
			break;
		case NODE_7:
			res = NODE_CORRELATED;
			break;
		case NODE_8:
			res = (r == NOT_EQUALS)?SHADOWED:REDUNDANCY;
			break;
		case NODE_9:
			res = (r == EQUALS)?REDUNDANCY:GENERALIZED;
			break;
		case DISJOINT:
			res = DISJOINT;
			break;
		default:
			res = -2;
	}
	return res;
}

void printa(int i, int j, enum node n)// new
{
	switch (n) {
		case DISJOINT:
			printf("R%d y R%d disjuntas.\n", i, j, getNode(n));
			break;
		case SHADOWED:
			printf("Rule %d - rule %d: %s.\n", i, j, getNode(n));
			break;
		case REDUNDANCY:
			printf("Rule %d - rule %d: %s.\n", i, j, getNode(n));
			break;
		case GENERALIZED:
			printf("Rule %d - rule %d: \n", i, j);
			printf("%s.", getNode(n));
			break;
		case NODE_CORRELATED:
			printf("Rule %d - Rule %d: %s.\n", i, j, getNode(n));
			break;
		case PARCIALLY_CORRELATED:
			printf("Rule %d - Rule %d: ", i, j);
			printf("%s.\n", getNode(n));
		default:
			printf("%d,%d\n",n,CORRELATED);
			printf("Error in printa: a = %s.\n", getNode(n));
	}
}

