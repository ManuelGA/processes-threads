#include "threads.h"

/*
Author : Manuel Gonzales
Basic program to test cpu and io usage with a multithreaded program
2 heavy IO threads + 6 heavy calculations Threads

*/

int main(void)
{	
	/* start time count */
	FILE *fp = fopen(LOG_FILE, "w");
	
	if(fp == NULL)
	{
		perror("Couldn't open log file");
		return 1;
	}

	struct timeval startingtime, endingtime;
	gettimeofday(&startingtime, 0);

	fprintf(fp, "Program has started at %s \n", ctime((const time_t*) &startingtime.tv_sec));
	
	pthread_t threads[NUMBER_THREADS];

	/*create structs for the threads*/
	struct thread_data* threads_data = malloc(NUMBER_THREADS * sizeof(struct thread_data));

	/*set threads data*/
	int i;
	for(i = 0; i < NUMBER_THREADS; i++)
	{
		threads_data[i].thread_number = i + 1;
		threads_data[i].fp = fp;
	}

	for(i = 0; i < NUMBER_THREADS; i++)
	{
		if( i < NUMBER_THREADS - IO_THREADS)
		{
			/*create divisor calculation threads*/
			if(pthread_create( &threads[i], NULL, divisor_calculator, (void*) &threads_data[i]) != 0)	
			{
				perror("Error - pthread_create()\n");
				return 1;
			}
		}
		else
		{
			/*create io read threads*/
			if(pthread_create( &threads[i], NULL, io_read, (void*) &threads_data[i]) != 0)	
			{
				perror("Error - pthread_create()\n");
				return 1;
			}
		}

		printf("Worker Thread %d Created\n", i + 1);
	}
	

	/*wait for threads to finish*/
	for(i = 0; i < NUMBER_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	/* free mem */
	free(threads_data);

	/* get total time*/
	gettimeofday(&endingtime, 0);

	fprintf(fp, "Program has finished at %s \n", ctime((const time_t*) &endingtime.tv_sec));

	long total_time = (endingtime.tv_sec - startingtime.tv_sec) *  1000000 + endingtime.tv_usec - startingtime.tv_usec;

	fprintf(fp, "Threaded Program took a total time of %ld ms\n\n", total_time / MIL_SECONDS);

	printf("Parent Process Exiting\n");

	fclose(fp);
	
	return 0;
}


