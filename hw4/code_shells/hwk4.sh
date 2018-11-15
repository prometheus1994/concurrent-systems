#!/bin/bash

for i in 1 2 4
do
  for j in 1 2 4 8 16
  do
    for k in 1 2 3 4 5 6 7 8 9 10
    do
      sleep .5
      sbatch --constraint=elves --ntasks-per-node=$j --nodes=$i --time=00:03:00 --mem=1G pt0.sh $i $j $j 0 0 40000 40000
      sbatch --constraint=elves --ntasks-per-node=$j --nodes=$i --time=00:03:00 --mem=1G pt1.sh $i $j $j 0 3000000
    done
  done
done