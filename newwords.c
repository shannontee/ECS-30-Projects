/*
 * ECS 30 Homework 5
 * Shannon Tee 998067032
 *
 * Program written: December 4, 2015
 * WORDS -- Reads in one or more files, sorts the words in the files in ASCII order, and prints each word prefixed with
 * the number of times it appears in the files
 * Inputs: 0 or more file names 
 * Outputs: Words in the files sorted in ASCII order, prefixed with the number of times it appears in the files
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h> 
#include <string.h>

/*
 * Structure for the list
 */

struct words {
	char data[100];		/* Data field; word to be stored */ 
	int repetition;		/* Counts the repetition of the  words in the files */
	struct words *next;	/* Points to the next element in the list */
};				/* NULL pointer if no next element */

/* 
 * Pointer to the first element in the list
 * NULL if there is nothing in the list
 */

struct words *head = NULL; 	

/*
 * Create a new node
 * Initializes two fields
 */ 

struct words *createnode()
{
	struct words *p;	/* Pointer to the new space */
 				
	if((p =(struct words *) malloc(sizeof(struct words))) == NULL){		/* Creates the node */
		return (NULL);							/* Returns NULL if unable to allocate memory */
	}

	p->repetition = 1;	/* Initializes repetition to 1 */
	p->next = NULL;		/* Initializes pointer to NULL */
	return(p);		/* Pointer to the new entity */
}

/*
 * Insert the element that points to into the linked list 
 * Sorts the list when inserting it
 */

struct words *insert(struct words *p)
{
	struct words *temp = head; 	/* Pointer to go down the linked list */
	int value;			/* Return value from string comparison */

	/* Empty list -- puts head at the front */

	if(head == NULL){
		return(p);
	}

	/* If it goes before the first element */

	value = strcmp(p->data,head->data);	/* String compares the word to the word in the first element */
	if(value< 0){				/* If return value of string compare is less than zero, it gets inserted before the first element */
		p->next = head;			/* Inserts before the first element by reassigning where the pointers point to */
		head = p;		
		return(head);
	}
	else if(value == 0){			/* If return value of string compare is 0, the words are the same */
		(head->repetition)++;		/* Increments repetition by 1 */
		return(head);
	}	

	/* If it gets inserted somewhere in the linked list */ 
 
	else{
		while(temp->next != NULL){				/* While loop that runs until temp->next equals NULL */
			value = strcmp(p->data,temp->next->data);	/* String compares the word to the word in the next element*/
			if(value > 0)					/* If return value of strcmp is greater than zero,  advance temp*/
				temp = temp->next;			
			else						
				break;
		}
		if(value==0){								/* If return value of string compare is 0, the words are the same */
			temp->next->repetition = (temp->next->repetition) + 1;		/* Increments repetition by 1 */
		}	
		else{						
			p->next = temp->next;		/* Makes the insertion by assigning temp->next to p->temp and p to temp->next */
			temp->next = p;	
		}
	}
	return(head);		/* Returns the pointer to the head of the list */
}

/* 
 * The main routine
 */

int main (int argc, char *argv[]) 
{
	if(argc == 1){		/* No file names as arguments, exit 0 */
		exit(0);
	}

	int n;			/* Counter for */
	int c;			/* Holds int from fgetc  */
	int lineNum = 1;	/* Counter for line number*/
	int i = 0;		/* Counter for inserting characters into data field */
	struct words *p;	/* Pointer to element for linked list */
	struct words *temp;	/* Pointer used when printing the linked list */

	for(n=1; n<argc; n++){
	
		FILE *fp = fopen(argv[n],"r"); 

		if(fp == NULL){			/* If statement when file that is named cannot be read */
			perror(argv[n]);	/* Print error message with function perror and file name */
			exit(1);
		}
		
		p = createnode();			/* Creates a new node */
		if(p == NULL){				/* If NULL is returned, memory was unable to be allocated */
			while(isalnum(c=fgetc(fp)))	/* Prints error message with word, file name, line number */
				printf("%c",c);
			printf(", file %s, line %d: ran out of memory\n",argv[n],lineNum);
			exit(1);
		}

		while((c=fgetc(fp)) != EOF){				/* While loop that gets each character from the file  until EOF */
			if(isalnum(c)){					/* If loop that runs while the character is alphanumeric */
				p->data[i] = c;				/* Assigns c to p->data */
				i++;					/* Increments i so the next character is assigned to the element in data */
			}
			else if(i>0){
				if(c == '\n'){				/* If the character is a new line, line number is incremented by 1 */
					lineNum++;
				}
				
				head = insert(p);			/* Inserts new element into linked list */
				p=createnode();				/* Creates a new node */
				if(p == NULL){				/* If NULL is returned, memory was unable to be allocated */
					while(isalnum(c=fgetc(fp)))	/* Prints error message with word, file name, line number */
						printf("%c",c);
                        		printf(", file %s, line %d: ran out of memory\n",argv[n],lineNum);
                       			exit(1);
				}
					
				i = 0;		/* Resets i back to zero for the next element */
			}
		}
	}

		/* Prints the linked list-- starts at the head, prints the repetition and data field of each element until temp equals NULL */

		temp = head;
		while(temp!= NULL){						
			printf("%5d %s\n", temp->repetition,temp->data);
			temp = temp->next;
		}

	exit(0);
} 

