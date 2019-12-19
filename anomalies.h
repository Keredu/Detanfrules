#ifndef _ANOMALIES_H_
#define _ANOMALIES_H_

#include <stdio.h>
#include "rule.h"
#include "cmp.h"
#include "arr.h"
#include "multigraph.h"

void anomalies (struct ruleset);
enum node anomaly(struct rule, struct rule);
enum node nn(enum relation, enum node, int);
enum node fn(enum relation, enum node);
void printa(int, int, enum node);

#endif
