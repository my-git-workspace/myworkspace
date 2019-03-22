/*
#include <stdio.h>
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> 	// for sleep()

// main function to find the execution time of a C program
int main()
{
	// to store execution time of code
	double time_spent = 0.0;

	clock_t begin = clock();

	// do some stuff here
	sleep(3);

	clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	time_spent = (double)(end - begin) ;

	printf("Time elpased is %f seconds\n", time_spent);

	return 0;
}
*/

/*
#include <stdio.h>
#include <time.h>   	// for time()
#include <unistd.h> 	// for sleep()

// main function to find the execution time of a C program
int main()
{
	time_t begin = time(NULL);

	// do some stuff here
	//sleep(1);
	printf("hello\n");

	time_t end = time(NULL);

	// calculate elapsed time by finding difference (end - begin)
	printf("Time elpased is %ld seconds\n", (end - begin)*1000);

	return 0;
}
*/
/*
#include <stdio.h>
#include <sys/time.h>   // for gettimeofday()
#include <unistd.h> 	// for sleep()

// main function to find the execution time of a C program
int main()
{
	struct timeval start, end;

	gettimeofday(&start, NULL);

	// do some stuff here
	sleep(5);

	gettimeofday(&end, NULL);

	long seconds = (end.tv_sec - start.tv_sec);
	long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

	printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);

	return 0;
}
*/
/*
#include <stdio.h>
#include <time.h>	// for clock_t, clock()
#include <unistd.h>	// for sleep()

#define BILLION  1000000000.0;

// main function to find the execution time of a C program
int main()
{
	struct timespec start, end;

	clock_gettime(CLOCK_REALTIME, &start);

	// do some stuff here
	sleep(3);

	clock_gettime(CLOCK_REALTIME, &end);

	// time_spent = end - start
	double time_spent = (end.tv_sec - start.tv_sec) +
						(end.tv_nsec - start.tv_nsec) / BILLION;

	printf("Time elpased is %f seconds\n", time_spent);

	return 0;
}
*/


#include <stdio.h>
#include <time.h>	// for clock_t, clock()
#include <unistd.h>	// for sleep()
int main()
{

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	//do stuff
	sleep(5);
	//printf("hello\n");
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	unsigned long delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	printf ("mirocseconds: %lu\n", delta_us);
	return 0;
}
