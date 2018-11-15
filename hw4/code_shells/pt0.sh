#!/bin/bash
i=$1
j=$2
k=$3
l=$4
m=$5
n=$6
o=$7

module load OpenMPI
mpiexec -np ${i} ./pt0 ${j} ${k} ${l} ${m} ${n} ${o}