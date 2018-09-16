/* ECS 30 Homework 2 -- Problem 7
 * Shannon Tee 998067032
 *
 * Original program written: October 27, 2015
 * WORDS -- Reads in a sring from standard input and prints its line number and each word of the input line on an individual line.
 * Input: String input line
 * Output: Individual lines with the line number and each word of the string
 * 
 * Program revised: November 22, 2015
 * Revisions: Improved the style of the program by adding more indentation in the main routine. 
 * Added start-of-file comments, variable declaration comments, and more line comments to make it easier
 * to read and understand the program. Also changed one of the variable names to make it more clear.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>

/*
 * Macros
 */

#define BUFFERSIZE 100 	/* Maximum character number for input line */

/*
 * The main routine
 */

int main(void) 
{

	char *token;			/* Pointer to the token */
	char buffer[BUFFERSIZE];	/* Input line */
	int lineNumber = 1; 		/* Line number, initialized to 1 */
	int x;				/* Counter for for loop */
	int length;			/* Length of input line */

	while(fgets(buffer,BUFFERSIZE,stdin) != NULL){			/* Reads in the input line */
		length = strlen(buffer);				/* Obtains the length of the input line */
		for(x=0; x < length; x++){				/* For loops that runs through each character in the input line */
			if(!isalnum(buffer[x])){			/* If statement that replaces all non-alphanumeric characters in the input line with '?' */
				buffer[x]='?';
			}
		}
		token = strtok (buffer , "?");				/* Tokenizes the input line given the delimiter '?' and gets the first token in the string */
		while(token != NULL){					/* While loop that tokenizes the rest of the string */
			printf("%d\t%s\n",lineNumber, token);	 	/* Prints the line number followed by the token */
			token = strtok(NULL, "?");			/* Gets the rest of the tokens in the string */
		}

		lineNumber++; 		/* Increments line number */
	}

	return(0);
} 


