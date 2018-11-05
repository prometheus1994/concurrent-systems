#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <omp.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

// Global Variables
int NUM_THREADS;
double global_sum = 0;
int NUM_ITER = 0;

typedef struct {
  uint32_t virtualMem;
  uint32_t physicalMem;
} processMem_t;

int parseLine(char *line) {
	// This assumes that a digit will be found and the line ends in " Kb".
	int i = strlen(line);
	const char *p = line;
	while (*p < '0' || *p > '9') p++;
	line[i - 3] = '\0';
	i = atoi(p);
	return i;
}// end parseLine

void GetProcessMemory(processMem_t* processMem) {
	FILE *file = fopen("/proc/self/status", "r");
	char line[128];

	while (fgets(line, 128, file) != NULL) {
		//printf("%s", line);
		if (strncmp(line, "VmSize:", 7) == 0) {
			processMem->virtualMem = parseLine(line);
		}

		if (strncmp(line, "VmRSS:", 6) == 0) {
			processMem->physicalMem = parseLine(line);
		}
	}
	fclose(file);
}// end GetProcessMemory

void DoWork(int myID) {
	double st = 1.0/((double) NUM_ITER);
  int start = myID * (NUM_ITER / NUM_THREADS);
  int end = start + (NUM_ITER / NUM_THREADS);
	int i = 0;
  double x = 0.0;
  double local_sum = 0.0;
  
	// declares the passed in variables and their addresses as local to this thread and unalterable to other threads.
  #pragma omp private(myID, local_sum, start_position, end_position, i, x, st)
	for (i = start; i < end; i++) {
		x = (i + 0.25)*st;
		local_sum += 4.0/(x*x+1);
	}// end for i	
 
  // locks the behavior/activity inside of it from other threads until global_sum has been completed updated.
  #pragma omp critical
  {
    global_sum += local_sum;
  }
}// end DoWork

int main(int argc, char ** argv) {
	struct timeval t1, t2;
	double elapsedTime;
	int numSlots, myVersion = 1;
  processMem_t myMemory;
  NUM_THREADS = atoi(argv[1]);
  NUM_ITER = atoi(argv[2]);
  int trial_count = atoi(argv[3]);
  omp_set_num_threads(NUM_THREADS);
   
  gettimeofday(&t1, NULL);// get time of day

  // open omp to start a parallel thread
  #pragma omp parallel 
  {
    DoWork(omp_get_thread_num());
  }
  
  gettimeofday(&t2, NULL);// get time of day
  GetProcessMemory(&myMemory);// get the memory used

  // Calculate the elapsed time 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
  
	printf("DATA, %d, %d, %d, %f, %u, %u\n", NUM_THREADS, NUM_ITER, trial_count, elapsedTime, myMemory.virtualMem, myMemory.physicalMem);
	
	return 0;
}// end main
