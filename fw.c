#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "hashTable.h"
#include "readWord.h"

/*prototypes of functions */
Node* getMax(HashTable*);

int main(int argc, char* argv[])
{
    /* all variable declarations */
    int opt, numberWords, totalWords, count;
    int index;
    HashTable* ht;
    
    Node* maxNode = NULL;
    char* word = NULL;
    FILE* fPointer = stdin;
    opt = 0; 
    numberWords = 10;
    count = 0;
    totalWords = 0;
    index = 0;

    ht = createHashTable();
    
    /* if opt is not -1 continue */
    while((opt = getopt(argc, argv, "n:")) != -1)
	{
	    switch(opt)
		{
		case 'n':
                /* if argument is NOT a digit print usage error */
			if(isdigit(optarg[0]) == 0)
			{
			printf("Usage: fw [-n num] [ file1 [ file2...] ]\n");
                	exit(EXIT_FAILURE);
			}
			else
			{
			/* print number of words from user */
                   	 numberWords = atoi(optarg);            
			}
			break;
			default:
			/* arguments other than -n*/
			printf("Usage: fw [-n num] [ file1 [ file2...] ]\n");
			exit(EXIT_FAILURE);	
		}
	}

    /* check if arguments are empty */    
    if(optarg == 0)
    {
	/* if no files then stdin */
        if(argv[optind] == NULL)
        {
            /*iterate through stdin and add words to hash table */
            while(!feof(fPointer))
            {
                word = read_one_word(fPointer);
                if(word != NULL)
                {
                   if(add(ht, word, 0))
			{
                 	   totalWords++;
			}
                }
            }
	}
	
	    /* exit program if file pointer is null */
            if(fPointer == NULL)
            {
                perror("Error: File NULL\n");
                exit(EXIT_FAILURE);
            }

    if(argv[optind] != NULL)
    {
	/* iterate through command line arguments */
        for(index = optind; index < argc; index++)
        {
            fPointer = fopen(argv[index], "r");
            
            if(fPointer == NULL)
            {
		continue;
            }
	/* read entire file and add words to hash table */
            while(!feof(fPointer))
            {
                word = read_one_word(fPointer);
                if(word != NULL)
                {
               	 if(add(ht, word, 0))
		 {
			totalWords++;
		 }
                }
            }
        }
    }
        
    }/*arguments are NOT empty */
    else
    {
        if(argv[optind] == NULL)
        {
            printf("No Files\n");
            exit(EXIT_FAILURE);
        }
        /* iterate through all files */       
        for(index = optind; index < argc; index++)
        {

	    /* open files to read from */    
            fPointer = fopen(argv[index], "r");
       
             
	    /* continue if file pointer is null */
            if(fPointer == NULL)
            {
		continue;
            }
	/* iterate through file and add to hash table */
            while(!feof(fPointer))
            {
                word = read_one_word(fPointer);
                if(word == NULL)
                {
                if(add(ht, word, 0))
		{
			totalWords++;
		}
                }
            }
         }
      }
	
   	/* display the top words */
  printf("The top %d words (out of %d) are:\n", numberWords, totalWords);
       
	 /* iterate through the number of words */
         while(count < numberWords)
         {
            maxNode = getMax(ht);
            if((maxNode->frequency) == 0)
            {
                break;
            }
	    printf("%*d %s\n", 9, maxNode->frequency, maxNode->word);
	    maxNode->frequency = 0;
	    count++;
	}
	return 0;
}

   
/* find the max node in the Hash Table */
Node* getMax(HashTable* hashtable)
{
    int i = 0;
    int max = 0;
    Node* maxNode = createNode("", -1);
	/* iterate through entire table */    
 
   for( ; i < TABLE_SIZE; i++)
    {
        Node* newNode = hashtable->nodes[i];
	if(newNode == NULL)
	{
		continue;
	}
	for(;;)
	{
		/* find max node */
		/* compare by frequency then by word */
		if(newNode->frequency > max)
		{
			max = newNode->frequency;
			maxNode = newNode;
		}
		else if(newNode->frequency == max)
		{
			if(strcmp(maxNode->word, newNode->word) < 0)
			{
				maxNode = newNode;
			}
		}
		if(newNode->next == NULL)
		{
			break;
		}
		newNode = newNode->next;
	}				
	
    }
    return maxNode;
}
       
