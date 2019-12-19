#ifndef _CMP_H_
#define _CMP_H_

#include <stdio.h>
#include <stdlib.h>
#include "rule.h"
#include "multigraph.h"

int cmp(struct rule, struct rule, enum relation *);
enum relation frel(struct rule, struct rule, int, int);
int findmax(int *, int);
int findmin(int *, int);

#endif
