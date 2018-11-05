#!/bin/bash
#SBATCH --constraint=elves
i=$1
j=$2
k=$3
l=$4
module load OpenMPI

mpicc -o find_keys_mpi find_keys_mpi.c
##'i' is the first argument after find_keys_mpi.sh giving the #processes
##sbatch --constraint=elves --ntasks-per-node=1 --nodes=1 --time=00:05:00 --mem=1G find_keys_mpi.sh 1 10000
##'j' is the second argument, giving the max number of lines
mpiexec -np ${i} ./find_keys_mpi ${j} ${k} ${l}