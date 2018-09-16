/* ECS 30 -- Homework 3 
 * Shannon Tee 998067032 */

#include <stdio.h>
#include <limits.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int getint (char *inputline, int *value, char **nextchar) {
     
char *token; 
int x;
int val = 0;
char tempString[1024];
long longValue = 0;
int negval=0;

if(inputline == NULL)		// returns -1 if inputline, value, nextchar or *nextchar are NULL, which are considered invalid inputs
	return (-1);
if(value == NULL)
	return (-1);
if(nextchar == NULL)
	return (-1);
else {
	if(*nextchar == NULL)
		return(-1);
} 

int n;				// copies inputline to tempString
int length;
length=strlen(inputline);
for(n=0; n<length ; n++){
	tempString[n] = inputline[n];
}

while(tempString[val]==' '){	// val increments if there are any spaces
	val++;
}

if(tempString[val] == '+' || tempString[val] == '-') {		// first "if loop" if the next character is +/-
	if(tempString[val] == '-')				// stores 1 in negval if negative (used for testing underflow and overflow)
		negval = 1;
	val++;							// increments val if there is +/-	

	if(isdigit(tempString[val])){				// starts "if loop" if next character is digit
		while(isdigit(tempString[val])){		// increments val as long as characters are digits
			val++;
		}		
		if((tempString[val]=='.'&& isdigit(tempString[val+1]))|| (isalpha(tempString[val]))){	// tests for cases such as 123.123 , 123x , 123x123 and returns 0
			*nextchar = &inputline[0];							
			memset(&tempString[0], 0, sizeof(tempString));				// clears the character array of tempString
			return(0);
		}	
		token = strtok(tempString, ",?#.+/ ()=/");	// strtok tempString
		longValue = atol(token);			// converts token from string into long integer
		*value = (int)longValue;			// stores in longValue as an integer
		*nextchar = &inputline[val];

		if(((unsigned)longValue) > INT_MAX && negval == 0){ 		// tests for overflow; compares longValue to INT_MAX if there was + in start of inputline	
			return(2);						// return 2 if does overflow
		}

		if((longValue < INT_MIN) && negval == 1){			// tests for underflow; compares longValue to INT_MIN if there was a - in the start of inputline 
			return(3);						// returns 3 if does underflow
		} 

/* gradebot note: I kept failing test case 8 that tested for underflow. I am not sure what was wrong with my code that gradebot did not like. I am pretty sure my code provided the right outputs when I used gcc. The first two inputs for test case 8 read through, but the third one underflow.
 * My outputs when I gcc: 
 * 	Read integer -214783647; rest of string is ""
 * 	Read integer -214783648; rest of string is ""
 * 	Integer underflow (-ve) -- string is "" 
 * Based on what I interpreted from the problem and other people got, I believe that these are correct. However, I could not figure out why gradebot kept failing that test case.
 * */
	
		memset(&tempString[0], 0, sizeof(tempString)); 	// clears tempString
		return(1);	
	}
}

if(isdigit(tempString[val])){			// "if loop" if there is digits directly after optional white spaces
	while(isdigit(tempString[val])){	// val increments as long as there are digits
		val++;
	}
	if((tempString[val]=='.' && isdigit(tempString[val+1]))|| (isalpha(tempString[val]))){		// tests for cases such as 123.123 , 123x , 123x123 and returns 0
		*nextchar = &inputline[0];								// points to the location of inputline[0]
		memset(&tempString[0], 0, sizeof(tempString));
		return(0);
	}
	
	token = strtok(tempString, ",?#.+/ ()=/");			// strtok tempString
	longValue = atol(token);					// converts token from string to long integer
	*value =(int)longValue;						

	if(((unsigned)longValue) > INT_MAX){				// tests for overflow; in this case INT_MIN does not need to be tested, since - sign is needed in front of INT_MIN
		*nextchar = &inputline[val];
		return (2);						// returns 2 if overflow
	}
	
	*nextchar = &(inputline[val]);					// points to the location after the last digit
	memset(&tempString[0], 0, sizeof(tempString));			// clears tempString
	return(1);
}

*nextchar = &inputline[0];						
memset(&tempString[0], 0, sizeof(tempString));
return(0);

}
