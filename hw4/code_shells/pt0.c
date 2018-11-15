/* Authors: William Van Cleve, Thomas Rolston, Joseph Webster
 * Date: November 18, 2018
 * Professor: Dr. Daniel Andresen
 * Course: CIS 625 | Concurrent Systems
 * Assignment 4 Part 1: Hybrid Computing
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "mpi.h"
#include <omp.h>
#include <math.h>

#define _SIZE 0.00001
#define _PI 3.14159265

int _start_x, _start_y, _end_x, _end_y;
int _num_nodes;
int _num_cores;
int _num_threads;

/*
* Gets the starting index for a given rank.
*/
int get_start(int rank) {
  int block_size, remainder, base_start, start;
  
  block_size = (_end_x - _start_x) / (_num_nodes * _num_threads); // Gets block size
  remainder = (_end_x - _start_x) % (_num_nodes * _num_threads); // Gets remainder if any (Remainders will be assigned starting from thread 0 then thread 1 and so on)
  base_start = rank * block_size; // Default start with no remainders
  start = ((remainder == 0)
    ? (base_start)
    : ((rank < remainder) ? (base_start + rank) : (base_start + remainder))); // Adjust start postion based on remainders
    
  return start;
} // end get_start

/*
* Gets the ending index for a given rank.
*/
int get_end(int rank, int start) {
  int block_size, remainder, end;
  
  block_size = (_end_x - _start_x) / (_num_nodes * _num_threads); // Gets block size
  remainder = (_end_x - _start_x) % (_num_nodes * _num_threads); // Gets remainder if any (Remainders will be assigned starting from thread 0 then thread 1 and so on)
  end = ((remainder == 0 || rank >= remainder)
    ? (start + block_size)
    : (start + block_size + 1)); // Gets end position from start postion and remainders

  return end;
} // end get_end

double function(double x, double y)
{
  return -cos(x)*sin(y)*exp(-((x - _PI)*(x - _PI) + (y - _PI)*(y - _PI)));
}

int main(int argc, char *argv[]) {
  /* Setup timer */
  struct timeval t1, t2;
  double elapsed_time;
  gettimeofday(&t1, NULL); // Get start time
  
  /* Setup program */
  int i, j, thread_id, thread_start, thread_end;
  double size, local_volume, global_volume;
  double *local_volumes;
	int rc, nnodes, rank;
	MPI_Status status;

  /* Start MPI */
  rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
	  printf ("Error starting MPI program. Terminating.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  } // end if

  /* Get MPI values */
  MPI_Comm_size(MPI_COMM_WORLD, &nnodes); // Get number of nodes
  _num_nodes = nnodes; // Save number of nodes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get rank of current node

  /* Initialize values */
  _num_cores = atoi(argv[1]); // Save number of cores
  _num_threads = atoi(argv[2]); // Save number of threads
  omp_set_num_threads(_num_threads);
  _start_x = atoi(argv[3]); // Save starting x value
  _start_y = atoi(argv[4]); // Save starting y value
  _end_x = atoi(argv[5]); // Save ending x value
  _end_y = atoi(argv[6]); // Save ending y value
  
  /* Thread calculations */
  local_volumes = malloc(_num_threads * sizeof(double));
  #pragma omp parallel private(i, j, thread_start, thread_end, local_volume)
  {
    thread_id = omp_get_thread_num();
    thread_start = get_start((rank * _num_threads) + thread_id);
    thread_end = get_end((rank * _num_threads) + thread_id, thread_start);
    
    for (i = thread_start; i < thread_end; i++)
    {
      for (j = _start_y; j < _end_y; j++)
        local_volume += _SIZE * _SIZE * function(_start_x + i*_SIZE, _start_y + j*_SIZE);
    }
    
    local_volumes[thread_id] = local_volume; // Save volume to volume array
  }
  
  /* Collect thread calculations */
  local_volume = local_volumes[0]; // Start volume
  for (i = 1; i < _num_threads; i++)
  {
    local_volume += local_volumes[i]; // Sum thread volumes
  }
  free(local_volumes);
  MPI_Reduce(&local_volume, &global_volume, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); // Sum node volumes
  
  /* Collect thread calculations and format output */
  if (rank == 0)
  {
    /* Format output */
    gettimeofday(&t2, NULL); // Get final time
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0; // Get elapsed time from sec to ms
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0; // Add elapsed time in us to ms
    printf("DATA, pt0, %d, %d, %d, %f, %E", _num_nodes, _num_cores, _num_threads, elapsed_time, global_volume); // Print output
  }
  
  /* Finalize program */
  MPI_Finalize(); // Finalize MPI
  return 0;
} // end main