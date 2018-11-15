#!/bin/bash
i=$1
j=$2
k=$3
l=$4
m=$5

module load OpenMPI
mpiexec -np ${i} ./pt1 ${j} ${k} ${l} ${m}