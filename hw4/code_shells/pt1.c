/* Authors: William Van Cleve, Thomas Rolston, Joseph Webster
 * Date: November 18, 2018
 * Professor: Dr. Daniel Andresen
 * Course: CIS 625 | Concurrent Systems
 * Assignment 4 Part 2: Hybrid Computing
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

int _start_x, _end_x;
int _num_nodes;
int _num_cores;
int _num_threads;

/*
* Gets the starting index for a given rank.
*/
int get_start(int id) {
  int block_size, remainder, base_start, start;
  
  block_size = (_end_x - _start_x) / (_num_nodes * _num_threads); // Gets block size
  remainder = (_end_x - _start_x) % (_num_nodes * _num_threads); // Gets remainder if any (Remainders will be assigned starting from thread 0 then thread 1 and so on)
  base_start = id * block_size; // Default start with no remainders
  start = ((remainder == 0)
    ? (base_start)
    : ((id < remainder) ? (base_start + id) : (base_start + remainder))); // Adjust start postion based on remainders
    
  return start;
} // end get_start

/*
* Gets the ending index for a given rank.
*/
int get_end(int id, int start) {
  int block_size, remainder, end;
  
  block_size = (_end_x - _start_x) / (_num_nodes * _num_threads); // Gets block size
  remainder = (_end_x - _start_x) % (_num_nodes * _num_threads); // Gets remainder if any (Remainders will be assigned starting from thread 0 then thread 1 and so on)
  end = ((remainder == 0 || id >= remainder)
    ? (start + block_size)
    : (start + block_size + 1)); // Gets end position from start postion and remainders

  return end;
} // end get_end

double function(double x)
{
  return cos(x)+(pow(fabs(6.0-x), 2.0/15.0))+2*(pow(fabs(5.0-x), 4.0/35.0));
}

int main(int argc, char *argv[]) {
  /* Setup timer */
  struct timeval t1, t2;
  double elapsed_time;
  gettimeofday(&t1, NULL); // Get start time
  
  /* Setup program */
  int j, thread_id, thread_start, thread_end;
  int *positions;
  double i, result, local_min, global_min;
  double *local_mins;
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
  omp_set_num_threads(_num_threads); // Set number of threads
  if (rank == 0)
  {
    _start_x = atoi(argv[3]); // Save starting x value
    _end_x = atoi(argv[4]); // Save ending x value
  }
  
  /* Broadcast starting and ending x positions */
  positions = malloc(2 * sizeof(int));
  if (rank == 0)
  {
    positions[0] = _start_x;
    positions[1] = _end_x;
  }
  MPI_Bcast(&positions[0], 2, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank != 0)
  {
    _start_x = positions[0];
    _end_x = positions[1];
  }
  
  /* Thread calculations */
  local_mins = malloc(_num_threads * sizeof(double));
  #pragma omp parallel private(i, thread_id, thread_start, thread_end, local_min, result)
  {
    thread_id = omp_get_thread_num();
    thread_start = get_start((rank * _num_threads) + thread_id);
    thread_end = get_end((rank * _num_threads) + thread_id, thread_start);
    
    for (i = 0; i < (thread_end - thread_start); i+=.01)
    {
      result = function(thread_start + i);
      if (i == 0) local_min = result;
      else
      {
        if (result < local_min) local_min = result;
      }
    }
    
    local_mins[thread_id] = local_min; // Save min to min array
  }
  
  /* Collect thread calculations */
  local_min = local_mins[0]; // Start min
  for (j = 1; j < _num_threads; j++)
  {
    if (local_mins[j] < local_min) local_min = local_mins[j]; // Replace min
  }
  MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD); // Get smallest minimum
  
  /* Collect thread calculations and format output */
  if (rank == 0)
  {
    /* Format output */
    gettimeofday(&t2, NULL); // Get final time
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0; // Get elapsed time from sec to ms
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0; // Add elapsed time in us to ms
    printf("DATA, pt1, %d, %d, %d, %f, %E", _num_nodes, _num_cores, _num_threads, elapsed_time, global_min); // Print output
  }
  
  /* Finalize program */
  MPI_Finalize(); // Finalize MPI
  return 0;
} // end main