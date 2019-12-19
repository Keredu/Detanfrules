#! /bin/bash

mkdir -p test
gcc rule.c testRule.c -o ./test/testRule
gcc rule.c cmp.c testCmp.c arr.c multigraph.c -o ./test/testCmp
gcc rule.c anomalies.c cmp.c arr.c testAnomalies.c multigraph.c -o ./test/testAnomalies
cd test
./testRule
echo "==================================================================="
./testCmp
echo "==================================================================="
./testAnomalies

 

