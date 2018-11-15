/* Author: Joseph Webster
 * Date: September 19, 2018
 * Professor: Dr. Daniel Andresen
 * Course: CIS 625 | Concurrent Systems
 * Assignment 2: Parallel Computing (serial code)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

#define NUM_THREADS 4
int global_sum = 0;
int NUM_ITER = 0;

/* Process memory structure */
typedef struct {
  uint32_t virtualMem;
  uint32_t physicalMem;
} processMem_t;

/* Parses through a pointer or file line-by-line */
int parseLine(char *line) {
	// This assumes that a digit will be found and the line ends in " Kb".
	int i = strlen(line);
	const char *p = line;
	while (*p < '0' || *p > '9') p++;
	line[i - 3] = '\0';
	i = atoi(p);
	return i;
}// end parseLine

/* Gets the Process Memory */
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

/* This method will handle the work done and handle pthreads and open_mp */
void DoWork() {
	//const int NUM_ITER = 100000000;
	int i;
	double sum = 0.0, x = 0.0;
	double st = 1.0/((double) NUM_ITER);
  processMem_t myMemory;
	
	for (i = 0; i < NUM_ITER; i++) {
		x = (i + 0.25)*st;
		sum += 4.0/(x*x+1);
	}// end for i	
}// end DoWork

/* Main method runs handles the program */
int main(int argc, char ** argv) {
	struct timeval t1, t2;
	double elapsedTime;
	int numSlots, myVersion = 1;
  processMem_t myMemory;
  //NUM_THREADS = atoi(argv[1]);
  NUM_ITER = atoi(argv[1]);
  int trial_count = atoi(argv[2]);
  
  // get time of day
  gettimeofday(&t1, NULL);
  
  // add work here 
  DoWork();
  
  // get time of day
  gettimeofday(&t2, NULL);
  
  // get the memory used
  GetProcessMemory(&myMemory);

  // Calculate the elapsed time 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
  
  // Print the data
	printf("DATA, %d, %d, %d, %f, %u, %u\n", NUM_THREADS, NUM_ITER, trial_count, elapsedTime, myMemory.virtualMem, myMemory.physicalMem);
	//printf("MEMORY, Virtual (KB), %u, Physical (KB), %u \n", myMem.virtualMem, myMem.physicalMem);
	return 1;
}// end main
