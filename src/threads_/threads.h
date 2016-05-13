#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>

/*values for testing*/
#define DIVISORS_NUMBER 9223372036854775LL
#define READ_FILE "warandpeace.txt"
#define WRITE_FILE "warandpeace_copy.txt"
#define LOG_FILE "threadlog.txt"
#define NUMBER_THREADS 8
#define IO_THREADS 2
#define MEM_ALLOC 100
#define MIL_SECONDS 1000

/* testing funtions */
void* divisor_calculator(void* ptr);
void* io_read(void* ptr);

/* struct used to be passed to threads */
struct thread_data
{
	int thread_number;
	FILE *fp;
};
