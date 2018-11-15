#!/bin/bash

gcc -o parallel_origin parallel_origin.c
gcc -o parallel_omp parallel_omp.c -fopenmp
gcc -o parallel_pthreads parallel_pthreads.c -pthread

# 'parallel_origin'
# NUM_ITER - atoi(argv[1])
for i in 100000000 200000000 300000000 400000000
do
  # 10 iterations of each thread count; trial_count = atoi(argv[2])
	for j in 1 2 3 4 5 6 7 8 9 10
	do
	# parallel_origin
		sbatch --constraint=elves --ntasks-per-node=4 --nodes=1 --time=00:05:00 --mem=512M --partition=ksu-gen-reserved.q,batch.q parallel_origin.sh ${i} ${j}
	done
done 

# 'parallel_omp'
# NUM_THREADS
for i in 2 4 8 16
do 
  # NUM_ITER increments
  for j in 100000000 200000000 300000000 400000000
  do
    # 10 iterations for each thread count and 
    for k in 1 2 3 4 5 6 7 8 9 10
    do
      sbatch --constraint=elves --ntasks-per-node=4 --nodes=1 --time=00:05:00 --mem=512M --partition=ksu-gen-reserved.q,batch.q parallel_omp.sh ${i} ${j} ${k}
    done
  done
done

# 'parallel_pthreads'
# NUM_THREADS
for i in 2 4 8 16
do 
  # NUM_ITER increments
  for j in 100000000 200000000 300000000 400000000
  do
    # 10 iterations for each thread count and 
    for k in 1 2 3 4 5 6 7 8 9 10
    do
      sbatch --constraint=elves --ntasks-per-node=4 --nodes=1 --time=00:05:00 --mem=512M --partition=ksu-gen-reserved.q,batch.q parallel_pthreads.sh ${i} ${j} ${k}
    done
  done
done