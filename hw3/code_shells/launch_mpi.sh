#!/bin/bash

## Trial
for x in 1 2 3 4 5
do
	sbatch --constraint=elves --nodes=1 --ntasks-per-node=1 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 1 1000 ${x} 1
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=1 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 2 1000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=2 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 1000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=4 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 1000 ${x} 2
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=1 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 1000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=2 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 1000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=4 --mem=1G --time=00:03:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 16 1000 ${x} 4
done

for x in 1 2 3 4 5
do
	sbatch --constraint=elves --nodes=1 --ntasks-per-node=1 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 1 10000 ${x} 1
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=1 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 2 10000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=2 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 10000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=4 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 10000 ${x} 2
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=1 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 10000 ${x} 4 
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=2 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 10000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=4 --mem=2G --time=00:30:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 16 10000 ${x} 4
done

for x in 1 2 3 4 5
do
	sbatch --constraint=elves --nodes=1 --ntasks-per-node=1 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 1 100000 ${x} 1
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=1 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 2 100000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=2 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 100000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=4 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 100000 ${x} 2
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=1 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 100000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=2 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 100000 ${x} 4
	## this failed, maybe needs more memory?
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=4 --mem=4G --time=03:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 16 100000 ${x} 4
done

for x in 1 2 3 4 5
do
	sbatch --constraint=elves --nodes=1 --ntasks-per-node=1 --mem=12G --time=18:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 1 1000000 ${x} 1
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=1 --mem=12G --time=12:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 2 1000000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=2 --mem=12G --time=12:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 1000000 ${x} 2
	sbatch --constraint=elves --nodes=2 --ntasks-per-node=4 --mem=12G --time=08:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 1000000 ${x} 2
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=1 --mem=12G --time=08:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 4 1000000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=2 --mem=12G --time=08:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 8 1000000 ${x} 4
	sbatch --constraint=elves --nodes=4 --ntasks-per-node=4 --mem=12G --time=08:00:00 --partition=ksu-gen-reserved.q,batch.q find_keys_mpi.sh 16 1000000 ${x} 4
done