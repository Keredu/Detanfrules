#ifndef _RULE_H_
#define _RULE_H_

#include <stdio.h>

enum selector {
	TCP, UDP, ARP, ICMP, DHCP, ACTION = 255
};

enum type {
	SINGLETON,RANGE,SET
};

struct field {
	enum selector sel;	
	enum type type;
	union {
		int value;
		struct range {
			int x;
			int y;
		}range;
		struct set {
			int elems[256];
			int size;
		}set;
	};
};

struct rule {
	struct field fields[25];
	int size;
};

struct ruleset {
	struct rule rules[30];
	int size;
};

void printrs(struct ruleset);
void printr(struct rule);
void print_field(struct field);
const char* getSelector(enum selector);
const char* getType(enum type);

#endif
