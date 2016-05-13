#include "processes.h"

/*
Author : Manuel Gonzales
Basic program to test cpu and io usage with a milti processes program
2 heavy IO processes + 6 heavy calculations processes

*/
int main(void)
{
	/*start time count */
	FILE* fp = fopen(LOG_FILE, "w");
	
	if(fp == NULL)
	{
		perror("Couldn't open log file");
		return 1;
	}	

	struct timeval startingtime, endingtime;
	gettimeofday(&startingtime, 0);

	fprintf(fp, "Program has started at %s \n", ctime((const time_t*) &startingtime.tv_sec));

	pid_t pid;
	pid_t childpid = 0;

	int i;	

	/** create processes and start*/
	for(i = 0; i < NUMBER_THREADS; i++)
	{
		if(i < NUMBER_THREADS - IO_THREADS)
		{
			if((childpid = fork()) <= 0)
			{
				divisor_calculator(i + 1, fp);
				exit(0);
			}
		}
		else
		{
			if((childpid = fork()) <= 0)
			{
				io_read(i + 1, fp);
				exit(0);
			}
		}

		printf("Worker Process %d Created\n", i+1);

	}

	/** wait for all child processes to finish*/
	while ((pid = wait(NULL)))
	{
   		if (errno == ECHILD)
   		{
    		break;
    	}
   	}

   	/* get total time */
   	gettimeofday(&endingtime, 0);

	fprintf(fp, "Program has finished at %s \n", ctime((const time_t*) &endingtime.tv_sec));

	long total_time = (endingtime.tv_sec - startingtime.tv_sec) *  1000000 + endingtime.tv_usec - startingtime.tv_usec;

	fprintf(fp, "Processes Program took a total time of %ld ms\n\n", total_time / MIL_SECONDS);

   	printf("All Processes have Finished\n");
   	
   	fclose(fp);

   	exit(0);

}
