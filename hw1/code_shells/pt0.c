/* Author: Joseph Webster
 * Date: September 10, 2018
 * Professor: Dr. Daniel Andresen
 * Course: CIS 625 | Concurrent Systems
 * Assignment 1: Optimization Techniques (unoptimized code)
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

/*#define ARRAY_SIZE 8000000*/
#define STRING_SIZE 16

/* char char_array[ARRAY_SIZE][STRING_SIZE]; */
int char_counts[26];

char getRandomChar()
{
	int randNum = 0;
	char randChar = ' ';

	randNum = 26 * (rand() / (RAND_MAX + 1.0)); 	// pick number 0 < # < 25
	randNum = randNum + 97;				// scale to 'a'
	randChar = (char) randNum;

	// printf("%c", randChar);
	return randChar;
}

 /* CODE FROM CHECKMEM */
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
}

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
}
 /* END CODE FROM CHECKMEM */
 
/* CODE FROM MYTIME */

/* END CODE FROM CHECKMEM */

void init_arrays(int size, char ** char_array)
{
  int i, j, randNum; 
  char randChar;

  for ( i = 0; i < size; i++) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
		 char_array[i][j] = getRandomChar();
	}
  }

  for ( i = 0; i < 26; i++ ) {
  	char_counts[i] = 0;
  }
}

// CHANGE THIS
void count_array(int size, char ** char_array)
{
  char theChar;
  int i, j, charLoc;

  for ( i = 0; i < size; i++) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
     theChar = char_array[i][j];
		 charLoc = ((int) theChar) - 97;
		 char_counts[charLoc]++;
	}
  }
}

int print_results()
{
  int i, total = 0;

  for ( i = 0; i < 26; i++ ) {
     total += char_counts[i];
     printf(" %c %d\n", (char) (i + 97), char_counts[i]);
  }
  //printf("\nTotal characters:  %d\n", total);
  
  return total;
}

int main(int argc, char ** argv) {
  char ** charPtrPtr;
	int i, j, size, total_count;
	processMem_t myMem; 
	struct timeval t1, t2;
	double elapsedTime;
	int numSlots, myVersion = 1;
  
  /* grab the size of the array */
  size = atoi(argv[1]);
	
  /* allocate memory for the size of the array */
  charPtrPtr = (char **) malloc(size * sizeof(char *));
  for (i = 0; i < size; i++) {
    charPtrPtr[i] = (char *) malloc(STRING_SIZE * sizeof(char));
  }
  
  /* pass to init_arrays */
  init_arrays(size, charPtrPtr);
  /* Start counter */
  gettimeofday(&t1, NULL);
  /* Count the char in the array */
	count_array(size, charPtrPtr);
  /* get the memory processed/used */
 	GetProcessMemory(&myMem);
  gettimeofday(&t2, NULL);
  /* End counter */

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	total_count = print_results();
  //printf("Memory: vMem %u KB, pMem %u KB\n", myMem.virtualMem, myMem.physicalMem);
  printf("DATA, %d, %s, %f, character count: %d, vMem %u KB, pMem %u KB\n", myVersion, getenv("SLURM_NTASKS"), elapsedTime, total_count, myMem.virtualMem, myMem.physicalMem);
  return 0;
}

