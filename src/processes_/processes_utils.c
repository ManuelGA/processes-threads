#include "processes.h"

/**
This function will find the divisors for a long long number and will also allocate some memory along the
way it will then print the ime it took to complete the task
**/
int divisor_calculator(int thread_number, FILE* fp)
{
	struct timeval startingtime, endingtime;
	gettimeofday(&startingtime, 0);

	fprintf(fp, "Worker Process %d has started at %s \n", thread_number, ctime((const time_t*) &startingtime.tv_sec));

	int j;
	long long i=2;

	while(i <= sqrt(DIVISORS_NUMBER))
	{
		int* hello = malloc(sizeof(int) * MEM_ALLOC);

		for(j = 0; j < MEM_ALLOC; j++)
		{
			hello[j] = 0;
		}
		free(hello);

		if(DIVISORS_NUMBER % i == 0)
		{
	    	printf("%lld,",i);


	    	if (i != (DIVISORS_NUMBER / i))
	    	{
	        	printf("%lld,",DIVISORS_NUMBER / i);
	    	}
		}

		i++;
	}

	gettimeofday(&endingtime, 0);

	fprintf(fp, "Worker Process %d has finished at %s \n", thread_number, ctime((const time_t*) &endingtime.tv_sec));

	long total_time = (endingtime.tv_sec - startingtime.tv_sec) *  1000000 + endingtime.tv_usec - startingtime.tv_usec;

	fprintf(fp, "Worker Process %d took a total time of %ld ms\n\n", thread_number, total_time / MIL_SECONDS);

	return 0;
}

/**
This function will copy a file over on the same folder and print the time it took to complete the task
**/
int io_read(int thread_number, FILE* fp)
{


	struct timeval startingtime, endingtime;
	gettimeofday(&startingtime, 0);

	fprintf(fp, "Worker Process %d has started at %s \n", thread_number, ctime((const time_t*) &startingtime.tv_sec));

	FILE *rp = fopen(READ_FILE, "r");
	FILE *wp = fopen(WRITE_FILE, "a+");
	char ch;

	if(rp == NULL)
	{
		perror("Couldn't open read file");
	}

	while( ( ch = fgetc(rp) ) != EOF )
	{
      fprintf(wp, "%c", ch);
  	}

  	fclose(rp);
  	fclose(wp);

	gettimeofday(&endingtime, 0);

	fprintf(fp, "Worker Process %d has finished at %s \n", thread_number, ctime((const time_t*) &endingtime.tv_sec));

	long total_time = (endingtime.tv_sec - startingtime.tv_sec) *  1000000 + endingtime.tv_usec - startingtime.tv_usec;

	fprintf(fp, "Worker Process %d took a total time of %ld ms\n\n", thread_number, total_time / MIL_SECONDS);

	return 0;
}
