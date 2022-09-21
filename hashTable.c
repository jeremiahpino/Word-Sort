#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "readWord.h"

/* hashcode function to give each word an index */
unsigned long hashcode(char* newWord) 
{
    unsigned long hash = 5381;
    int c;
    
    while((c = *newWord++)) /* checks if c becomes NULL */
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE; /* return index into hash */
}

/* create Hash Table */
HashTable* createHashTable(void)
{
    int i = 0;

    /* allocate memory for new Hash Table */
    HashTable *hashtable = (HashTable*)malloc(1 * sizeof(HashTable));
    
    /* allocate memory for node pointers */
    hashtable->nodes = (Node**)malloc(sizeof(Node) * TABLE_SIZE);
    
    for(; i < TABLE_SIZE; i++)
    {
        hashtable->nodes[i] = NULL;
    }
    
    return hashtable;
} 

/* creates and allocates memory for new node */
Node* createNode(char* newWord, int freq)
{
    /* allocates new memory for new Node */
    Node* pNode = (Node*)malloc(sizeof(pNode));
    
    if(pNode == NULL)   /*check if node is NULL */
    {
        perror("Error: \n");
        exit(EXIT_FAILURE);
    }
   
    /* assign values to Node */
    pNode->word = strdup(newWord); 
    pNode->frequency = freq + 1; 
    pNode->search = 0;
    pNode->next = NULL;

    return pNode;
} 

/* add a node to the Hash Table */
int add(HashTable* hashtable, char* newWord, int freq)
{
    Node* newNode = NULL;
    Node* previousNode = NULL;
   
    int long index = hashcode(newWord);

    /* assign Node with spot in HashTable */
    newNode = hashtable->nodes[index]; /*assign pointer at index to newNode */

    if(newNode == NULL)
    {
        hashtable->nodes[index] = createNode(newWord, freq);
        return 1; 
    }

    while(newNode != NULL) /* while newNode is NOT NULL loop */
    {
        /* if two words are equal increment frequency */
        if(strcmp(newNode->word, newWord) == 0) 
        {
            int newFreq = newNode->frequency + 1;
            newNode->frequency = newFreq;
            return 0;
        }
        /* assign newNode with previousNode next pointer */
        previousNode = newNode; 
        newNode = previousNode->next;
    }
    
    previousNode->next = createNode(newWord, freq);
	return 1;
}


void freeNode(Node* node)
{
    /* free a node */
    free(node->word);
    free(node);
}

void freeTable(HashTable* ht)
{
    Node* current = NULL;
    int i;
    i = 0;
    /* iterate through table and free it */    
    for( ; i < TABLE_SIZE; i++)
    {
        current = ht->nodes[i];
        if(current == NULL)
        {
            continue;
        }
        while(current != NULL)
        {
        ht->nodes[i] = ht->nodes[i]->next;
        free(current);
        }
    }

}
               
/* print Hash Table */
void printTable(HashTable* hashtable)
{
    int i = 0;
    /* go through nodes and print their contents */
    for(; i < TABLE_SIZE; i++)
    {
        Node* newNode = hashtable->nodes[i];

        if(newNode == NULL)
        {
            continue;   
        }
        
        printf("%4d: ", i);
        
        for(;;)
        {
            printf("%s = %d ", newNode->word, newNode->frequency);
            
            if(newNode->next == NULL)
            {
                break;
            }
            newNode = newNode->next;
        }
        printf("\n");
    } 
}

/* DEBUG SECTION
Node* getMax(HashTable* hashtable)
{  
    int i, max;
    Node* maxNode;
    Node* newNode = NULL;
    i = 0;  
    max = 0;

    for( ; i < TABLE_SIZE; i++)
    {
        newNode = hashtable->nodes[i];
	if(newNode == NULL)
	{
		continue;
	}
	for(;;)
	{
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


int main()
{
    int count;
    HashTable* ht;
    Node* maxNode = NULL;
    count = 0;
    ht = createHashTable();

    add(ht, "this", 0);
    add(ht, "will", 0);
    add(ht, "read", 0);
    add(ht, "one", 0);

    printTable(ht);

    while(count < 4)
    {
         maxNode = getMax(ht);
         printf("Node: %s #:%d S:%d \n", maxNode->word,
         maxNode->frequency, maxNode->search);
	maxNode->frequency = 0;
         count++;
    }
    
    return 0;
}
*/

