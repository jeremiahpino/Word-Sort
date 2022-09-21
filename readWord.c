#include "readWord.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define HUNK 50

char* read_one_word(FILE* file)
{
    int i = 0;
	char* charArray = (char*)malloc(HUNK * sizeof(char));
	int c = 0;
	int size = HUNK;
		
    if(charArray == NULL)	/* check if character array was allocated */
	{
    	perror("Error: \n");
		exit(EXIT_FAILURE);
	}
    
    /* check for alphabetic character and EOF */	
	while((isalpha(c = getc(file))) && c != EOF) 
	{
		if(i == size - 2)
		{
		 size += HUNK;
         /* check if charArray was reallocated */
		 charArray = (char*)realloc(charArray, (size) * sizeof(char));
		 
		 if(charArray == NULL)
		 {
			perror("Error: \n");
			exit(EXIT_FAILURE);
		 }
		}
        /* read character and save it as lower case */
		c = tolower(c);
		charArray[i] = c;
		i++;
        
	}
	charArray[i] = '\0';
    if(c == EOF && i == 0)
    {
        charArray = NULL;
    }
	return charArray; /* return character array */
}

/* DEBUG SECTION
int main ()
{
	FILE* fPointer = stdin;
	char* word = NULL;	
	int count = 0;
	
	while(!feof(fPointer))
	{	
		word = read_one_word(fPointer);
	        count++; 
		printf("%s\n", word);
	}
    
    printf("Total Words: %d\n", count);
	fclose(fPointer);
	return 0;
}

*/		
