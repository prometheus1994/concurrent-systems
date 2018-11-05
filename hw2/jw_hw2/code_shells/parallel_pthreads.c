#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

pthread_mutex_t mutex_sum;
int NUM_THREADS;
double global_sum = 0.0;
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
void * DoWork(int * idPtr) {

  int start = ((int) idPtr) * (NUM_ITER / NUM_THREADS);
  int end = start + (NUM_ITER / NUM_THREADS);
	int i;
	double local_sum = 0.0, x = 0.0;
	double st = 1.0/((double) NUM_ITER);
  processMem_t myMemory;
	
	for (i = start; i < end; i++) {
		x = (i + 0.25)*st;
		local_sum += 4.0/(x*x+1);
	}// end for i	
 
  /* Locks access to the global_sum*/
  pthread_mutex_lock (&mutex_sum);
  global_sum += local_sum;
  pthread_mutex_unlock (&mutex_sum);
  /* global_sum access unlocked */
  
  /* We have to kill the current thread as it's no longer needed */
  pthread_exit(NULL);
  
}// end DoWork

/* Main method runs handles the program */
int main(int argc, char ** argv) {
	struct timeval t1, t2;
	double elapsedTime;
	int i, check, numSlots, myVersion = 1;
  processMem_t myMemory;
  NUM_THREADS = atoi(argv[1]);
  NUM_ITER = atoi(argv[2]);
  int trial_count = atoi(argv[3]);
  
	//pthread stuff
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attribute;
	void * status;
 
  // Create a thread detached attribute & a new thread
	pthread_attr_init(&attribute);
	pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);
	gettimeofday(&t1, NULL);
	pthread_mutex_init(&mutex_sum, NULL);
	for (i = 0; i < NUM_THREADS; i++ ) {
    check = pthread_create(&threads[i], &attribute, DoWork, (void *) i);
    if (check) {
      printf("Return code from pthread_create(): %d\n", check);
		  exit(-1);
    }
	}
	
	// Release/destory the thread attribute
	pthread_attr_destroy(&attribute);
	for(i=0; i < NUM_THREADS; i++) {
    check = pthread_join(threads[i], &status);
	  if (check) {
		  printf("Return code from pthread_join(): %d\n", check);
		  exit(-1);
	  }
	}
 
	gettimeofday(&t2, NULL);
  GetProcessMemory(&myMemory);
  // Calculate the elapsed time & display stats 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
 
	printf("DATA, %d, %d, %d, %f, %u, %u\n", NUM_THREADS, NUM_ITER, trial_count, elapsedTime, myMemory.virtualMem, myMemory.physicalMem);
  pthread_mutex_destroy(&mutex_sum);
  pthread_exit(NULL);
  
	return 0;
}// end main
