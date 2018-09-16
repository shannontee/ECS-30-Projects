/* ECS 30 Homework 4 -- Problem 6 
 * Shannon Tee -- 998067032
 * Original program written: November 20, 2015 
 * 
 * FIBS -- takes in an integer and prints the first n Fibonacci numbers by calling a function that computes it iteratively and 
 * another that computes it recursively. The two routines are compared based on the time to computate the Fibonacci sequence.
 *
 * Inputs: an integer, n
 * Outputs: Sequence of Fibonacci numbers found iteratively and recursively and the time computation for each method
 * Errors: usage (wrong number of arguments), non-positive integer input, invalid argument (doesn't begin with an integer)
 *
 */

#include <stdio.h> 
#include <sys/time.h>
#include <ctype.h>
#include <stdlib.h>

/* 
 * Interative function -- computes the fibonacci sequence iteratively
 */

int iterfib(int n){
	int fib1 = 0; 	/* First number in the Fibonacci sequence */	
	int fib2 = 1; 	/* Second number in the Fibonacci sequence */
	int i;		/* Counter in for loop */
	int fib3;	/* Value of the addition of the two previous numbers */

	if(n==1){				/* Returns 0 if n == 1 */
		return(0);		
	}

	if(n==2){				/* Returns 1 if n == 2 */
		return(1);
	}	

	if(n>2){				
   		 for(i=2; i<n; i++){		/* For loop that runs until n */
                	fib3 = fib1 + fib2;	/* Adds the two previous numbers in the sequence */
			fib1 = fib2;		/* Reassigns variables to find the next number */
                	fib2 = fib3;
        	}	
	}
	return (fib2);				/* Returns the ith Fibonacci number */
}

/* 
 * Recursive function -- computes the fibonacci sequence recursively 
 */

int recfib(int n){
	if(n==1){				/* Base case if n==1 */ 
		return (0);
	}
	if(n==2){				/* Base case if n==2 */
		return(1);
	}
	return(recfib(n-1)+recfib(n-2));	/* Function recusively calls itself */
} 

/* 
 * Timing functions that are in the file "timeit.o"
 */

struct timeval *gettime(void);					/* Function that obtains the current time */
double timediff(struct timeval *t1, struct timeval *t2);	/* Function that returns the difference between the two times in seconds*/

/* 
 * the main routine
 */

int main (int argc, char *argv[])
{
	if(argc!=2){								/* Checks the the number of arguments */
                fprintf(stderr, "Usage: %s number\n", argv[0]);			/* Prints out error message if number of arguments is not 2 */
                return (1);
        }

	if(*argv[1]=='-' || *argv[1]=='0'){					/* Checks for non-positive integer inputs */
                fprintf(stderr,"Argument must be a positive integer\n");	/* Prints out an error message if the input is non-positive */
                return(1);
        }

	if(!isdigit(*argv[1])){							/* Checks for invalid arguments such as those that do not begin with an integer */
                fprintf(stderr, "%s not an integer\n", argv[1]);		/* Prints out an error message if there is an invalid argument */
                return(1);
        }

	int iterative;		/* Value returned from iterative Fibonacci function*/
	int recursive;		/* Value returned from recursive Fibonacci function*/
	double TimeIter; 	/* Time to run the iterative Fibonacci function */
	double TimeRec;		/* Time to run the recursive Fibonacci function */
	int i;			/* Counter in the for loop */
	int n;			/* n Fibonacci numbers for the sequence*/
	n = atoi(argv[1]);	/* Converts the input into an integer */
	

	struct timeval TimeIterBegin, TimeIterEnd; 		/* Time before and after iterative Fibonacci function */
	TimeIterBegin = *gettime();				/* Record the time before iterfib function */

	printf("Iterative: ");
	for(i=1; i<=n; i++){					/* For loop that runs from 1 to the n Fibonacci number */
		iterative = iterfib(i);				/* Calls the function for the ith number */
		printf(" %d", iterative);			/* Prints the ith Fibonacci number returned from the iterfib function */
	}
	printf("\n");
		
	iterative = iterfib(n);
	TimeIterEnd = *gettime();				/* Record the time after iterfib function */
	TimeIter = timediff(&TimeIterBegin,&TimeIterEnd);	/* Compute the difference between the times */


        struct timeval TimeRecBegin, TimeRecEnd;		/* Time before and after recursive Fibonacci function */
        TimeRecBegin = *gettime();				/* Record the time before recfib function */
        
	printf("Recursive: ");
        for(i=1; i<=n; i++){					/* For loop that runs from 1 to the n Fibonacci number */
                recursive = recfib(i);				/* Calls the function for the ith number */
                printf(" %d", recursive);			/* Prints the ith Fibonacci number returned from the recfib function */
        }
        printf("\n");

        TimeRecEnd = *gettime();				/* Record the time after recfib function*/
        TimeRec = timediff(&TimeRecBegin,&TimeRecEnd);		/* Compute the difference between the times */

	printf("Iterative timing: %12.6f\n",TimeIter); 		/* Prints the time to compute the Fibonacci sequence iteratively */
	printf("Recursive timing: %12.6f\n",TimeRec);		/* Prints the time to compute the Fibonacci sequence recursively */

	return (0);
}


 
