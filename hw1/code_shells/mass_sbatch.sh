#!/bin/bash

# pt0.sh
for i in 8000 80000 800000 8000000
do 
  # each test case will run 5 times
  for j in 1 2 3 4 5
  do
	   sbatch --constraint=elves --ntasks-per-node=1 --nodes=1 --time=00:05:00 --mem=512M pt0.sh $i
  done
done

# pt0_unrolled.sh
for i in 8000 80000 800000 8000000
do 
  # each test case will run 5 times
  for j in 1 2 3 4 5
  do
	   sbatch --constraint=elves --ntasks-per-node=1 --nodes=1 --time=00:05:00 --mem=512M pt0_unrolled.sh $i
  done
done


# pt0_tiling.sh
for i in 8000 80000 800000 8000000
do 
  # each test case will run 5 times
  for j in 1 2 3 4 5
  do
	   sbatch --constraint=elves --ntasks-per-node=1 --nodes=1 --time=00:05:00 --mem=512M pt0_tiled.sh $i
  done
done
