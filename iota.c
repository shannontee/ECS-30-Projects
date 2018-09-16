/* ECS 30 Homework 1 -- Problem 7
 * Shannon Tee 998067032
 *
 * Original program written: October 12, 2015
 * IOTA -- program that prints a list of numbers from a starting number to ending number, counting by increment
 * 	Inputs: starting number, ending number, and increment
 * 	Outputs: A list of numbers from the starting number to the ending number, counting by increment. Otherwise, an error statement 
 * 	if an error arises given the starting number, ending number, or increment.  
 *
 * Program revised: November 22, 2015  
 * Revisions: Improved the identation inside the main routine to make it easier to read the program. 
 * Added start-of-file comments, paragraph comments, variable declaration comments, and more line comments
 * to make the code more clear for the reader. 
 * 
 */

#include <stdio.h> 

/* 
 * The main routine
 */

int main(void) 
{

	int startingPoint;  	/* Starting point */  
	int endingPoint;	/* Ending Point*/
	int increment;		/* Increment*/
	int x;			/* Counter for while loops*/ 
	
	/* Reads in the desired starting point, ending point, and increment */

	printf("Starting point: ");		
	scanf("%d",&startingPoint);		

	printf("Ending point: ");
	scanf("%d", &endingPoint);

	printf("Increment: ");
	scanf("%d", &increment);

	x = startingPoint;		/* Assigns starting point to x */


	/* Case 1: Starting point is less than ending point and increment is positive. */ 

	if(startingPoint<endingPoint && increment>0){	
		printf("%d",x);					/* Prints the starting number, which is the first number of the list */
		while(x<endingPoint){				/* While loop that runs while x is less than the ending point */
			x = x + increment;			/* Increments x by the increment value */
			if(x>endingPoint){			/* If statement in case increment makes x greater than the ending point */ 
				x = x - increment;		/* De-increments x to its previous value */
				break;
			}
			printf(" %d",x);			/* Prints the next number in the list */
		}
	}


	/* Case 2: Starting point is greater than ending point and increment is negative. */

	else if(startingPoint > endingPoint && increment < 0){   
		printf("%d",x);					/* Prints the starting number, which is the first number of the list */
		while(x>endingPoint){				/* While loop that increments x while it is greater than the ending point */
			x = x + increment;			/* Increments x by the increment value, which is a negative value */
			if(x < endingPoint){ 			/* If statement in case the increment makes x less than the ending point */
				x = x - increment;		/* De-increments x to its previous value */
				break;
			}
			printf(" %d",x);			/* Prints the next number in the list */
		}	
	}	


	/* Case 3: Starting point equals ending point. Prints the starting/ending number and no incrementation occurs. */

	else if(startingPoint == endingPoint){  		 
		printf("%d",x);
	}


	/* Case 4: Increment is equal to zero. */

	else if(increment == 0){  				
		if(startingPoint<endingPoint){						/* Conditions when increment is zero and starting point is less than ending point */
			fprintf(stderr,"Increment must be > 0 if begin < end\n");	/* Prints an error statement */
		}		
		else{									/* Conditions when increment is zero and starting point is greater than ending point */
			fprintf(stderr,"Increment must be < 0 if begin > end\n");	/* Prints an error statement */
		}
		return(1);
	}


	/* Case 5: Error cases which direction of increment does not match with starting and ending points.  */ 

	else{					
		if(increment<0){							/* Conditions when increment is less than zero, but starting point is less than ending point */
			fprintf(stderr, "Increment must be > 0 if begin < end\n");	/* Prints an error statement */
			return(1);
		}
	
		else{									/* Conditions when increment is greater than zero, but starting point is greater than ending point */
			fprintf(stderr, "Increment must be < 0 if begin > end\n");	/* Prints an error statement */
			return(1);
		}	 
	} 

	printf("\n"); 		/* New line after printing the list of numbers */
	return(0);

}
