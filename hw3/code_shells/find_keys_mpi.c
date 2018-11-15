/* Author: Joseph Webster
 * Date: October 5th, 2018
 * Professor: Dr. Daniel Andresen
 * Course: CIS 625 | Concurrent Systems
 * Assignment 3: Distributed Computing with MPI
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define max_words 50000 

typedef struct list_item {
	//int id; // id of the word
	int size; // for keeping track of the memory to allocate;
	int count; // the amount of lines containing a match
	int * array;
} List;

/* Global Variables */
int NUM_THREADS;
int max_lines;
char **words, **lines; 
List ** results;
List * local_results;
/* Global Variables */

/* Method Signatures */
double myclock();
void init_array(char *** c, int i, int j);
void read_keys();
void read_lines();
void match_keys(int start, int end);
int compare(const void * p1, const void * p2);
void print_matches();
void init_list(List * list, int s);
void grow_list(List * list, int i);
/* Method Signatures */

/* Methods */
void init_list(List * list, int s) {
	//list->id = id;
	list->size = s;
	list->count = 0;
	if (s != 0) {
		list->array = (int *) malloc(sizeof(int) * list->size);
	}
}// end init_list

void init_array(char *** array, int row, int col) {
	int i;
	char * temp_array = (char *) malloc(row * col * sizeof(char));
	(* array) = (char **) malloc(row * sizeof(char *));

	for (i = 0; i < row; i++) {
		(*array)[i] = &(temp_array[i * col]);
	}
}// end init_array()

void grow_list(List * list, int i) {
	if (list->size == 0) {
		init_list(list, 150);
	}
	
	if (list->count == list->size) {
		list->size *= 2;
		list->array = realloc(list->array, (sizeof(int) * list->size));
	}

	list->array[list->count++] = i;
}// end grow_list

int compare(const void * p1, const void * p2) {
	const char * c1 = (const char *) p1;
	const char * c2 = (const char *) p2;
	return strcmp(c1, c2);
}// end compare()

void read_keys() {
	FILE * fd;
	int nwords, err;

	fd = fopen( "/homes/dan/625/keywords.txt", "r" );
	nwords = -1;
	do {
		err = fscanf( fd, "%[^\n]\n", words[++nwords] );
	} while ( err != EOF && nwords < max_words );
	fclose( fd );

	size_t num = sizeof(words) / sizeof(* words);
	qsort(words, num, sizeof(char *), compare);

}//end read_keys()

void read_lines() {
	FILE * fd;
	int nlines, err;

	// Read in the lines from WIKI_DUMP
	fd = fopen( "/homes/dan/625/wiki_dump.txt", "r" );
	nlines = -1;
	do {
		err = fscanf( fd, "%[^\n]\n", lines[++nlines] );
	} while ( err != EOF && nlines < max_lines);
	fclose( fd );

}// end read_lines()

void match_keys(int start, int end) {
	int i, j;

	for (i = start; i < end; i++) {
		//init_list(&local_results[i - start]);

		for (j = 0; j < max_lines; j++) {
		  if (strstr(lines[j], words[i]) != NULL) {
			grow_list(&local_results[i - start], j);
		  }
		}
	}
}// end match_keys()

double myclock() {
	static time_t t_start = 0;  // Save and subtract off each time
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	if( t_start == 0 ) t_start = ts.tv_sec;
   return (double) (ts.tv_sec - t_start) + ts.tv_nsec * 1.0e-9;
}// end myclock()

void print_matches() {
	int i, j;

	for (i = 0; i < max_words; i++) {
		if (results[i]->count > 0) {
			printf("%s:", words[i]);
			for (j = 0; j < results[i]->count; j++) {
				printf(" %d", results[i]->array[j]);
			}
			printf("\n");
		}
	}
}// end print_matches()
/* Methods */

/* Main */
int main(int argc, char ** argv) {
	int id, i, j, rc, numtasks, rank, start, end, trial, node_count;
	trial = atoi(argv[2]);
	node_count = atoi(argv[3]);
	MPI_Status Status;
	double tstart, ttotal;
	
	tstart = myclock();  // Set the zero time
	tstart = myclock();  // Start the clock

	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf ("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	NUM_THREADS = numtasks;
	max_lines = atoi(argv[1]);
	
	init_array(&lines, max_lines, 2001);
	init_array(&words, max_words, 10);
	//init_array(&local_results, (end - start), 5000);

	if (rank == 0) {
		//init_array(&results, max_words, 5000);
		read_keys();
		read_lines();
	}

	/* ref: https://stackoverflow.com/questions/7864075/using-mpi-bcast-for-mpi-communication */
	MPI_Bcast(&lines[0][0], max_lines * 2001, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&words[0][0], max_words * 10, MPI_CHAR, 0, MPI_COMM_WORLD);

	start = rank * (max_words / NUM_THREADS);
	end = start + (max_words / NUM_THREADS);
	local_results = malloc((end - start) * sizeof(List));
	match_keys(start, end);

	/* ref: http://mpitutorial.com/tutorials/mpi-send-and-receive/ */
	
	if (rank != 0) {
		
		for (i = start; i < end; i++) {
			
			MPI_Send(&local_results[i - start].count, sizeof(int), MPI_INT, 0, i, MPI_COMM_WORLD);
			
			if (local_results[i - start].count != 0) {
				MPI_Send(&(local_results[i - start].array[0]), local_results[i - start].count, MPI_INT, 0, i, MPI_COMM_WORLD);
			}
		}
	}

	else {
		results = malloc(max_words * sizeof(List));
		
		for (i = 0; i < (end - start); i++) {
			results[i] = malloc(sizeof(List));
			init_list(results[i], local_results[i].count);
			
			if (local_results[i].count > 0) {
				results[i]->count = local_results[i].count;
				for (j = 0; j < local_results[i].count; j++) {
					results[i]->array[j] = local_results[i].array[j];
				}
			}
		}
		
		if (NUM_THREADS > 1) {
			for (i = 1; i < NUM_THREADS; i++) {
				int thread_start = i * (max_words / NUM_THREADS);
				int thread_end = thread_start + (max_words / NUM_THREADS);

				for (j = thread_start; j < thread_end; j++) {
					int length;
					results[j] = malloc(sizeof(List));
					MPI_Recv(&length, sizeof(int), MPI_INT, i, j, MPI_COMM_WORLD, &Status);
					init_list(results[j], length);
					
					if (length > 0) {
						results[j]->count = length;
						// may need to allocate memory
						MPI_Recv(&(results[j]->array[0]), length, MPI_INT, i, j, MPI_COMM_WORLD, &Status);
					}
				}
			}
		}
	}// if rank == 0
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		print_matches(); // need to add a if rank == 0 to ensure all results are back to the host
		ttotal = myclock() - tstart;
		printf("DATA: Trial: %d, Line Count: %d, Node Count: %d, Process Count: %d, Elapsed Time: %f\n", trial, node_count, max_lines, NUM_THREADS, ttotal);
	}
	MPI_Finalize();

	return 0;
}// end main()
