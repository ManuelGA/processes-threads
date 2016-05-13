#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

/*values for testing*/
#define DIVISORS_NUMBER 9223372036854775LL
#define READ_FILE "warandpeace.txt"
#define WRITE_FILE "warandpeace_copy.txt"
#define LOG_FILE "processlog.txt"
#define NUMBER_THREADS 8
#define IO_THREADS 2
#define MEM_ALLOC 100
#define MIL_SECONDS 1000

/*testing functions*/
int divisor_calculator(int thread_num, FILE* fp);
int io_read(int thread_num, FILE* fp);
