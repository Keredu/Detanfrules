#include "rule.h"

void printrs(struct ruleset rs)
{
	int i;
	printf("Ruleset:\n");
	for (i = 0; i < rs.size; i++) {
		printf("\tRule %d:\n", i);
		printr(rs.rules[i]);
		if (i < rs.size - 1)		
			printf("\n");
	}
}

void printr(struct rule r)
{
	int i;
	for(i = 0; i < r.size; i++) {
		struct field f = r.fields[i];
		printf("\tField %d: ",i);
		print_field(f);
	}
	printf("\tRulesize = %d\n", r.size);
}

void print_field(struct field f)
{
	int i;
	printf("selector = %s, type = %s, ", getSelector(f.sel), getType(f.type));
	if (f.type == SINGLETON)
		printf("value = %d\n", f.value);
	else if (f.type == RANGE)
		printf("[x,y] = [%d,%d]\n", f.range.x, f.range.y);
	else if (f.type == SET) {
		printf("elems = [");
		for (i = 0; i < f.set.size - 1; i++)
			printf("%d, ", f.set.elems[i]);
		printf("%d], setsize = %d\n", f.set.elems[i], f.set.size);
	} else
		printf("Incorrect type\n");
}

const char* getSelector (enum selector sel)
{
	switch (sel) {
		case TCP: return "TCP";
		case UDP: return "UDP";
		case ARP: return "ARP";
		case ICMP: return "ICMP";
		case DHCP: return "DHCP";
		case ACTION: return "ACTION";
		default: return "Error in getSelector";
	}
}

const char* getType (enum type t)
{
	switch (t) {
		case SINGLETON: return "SINGLETON";
		case RANGE: return "RANGE";
		case SET: return "SET";
		default: return "Error in getType";
	}
}
