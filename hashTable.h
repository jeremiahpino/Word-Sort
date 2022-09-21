#ifndef HASHTABLE
#define HASHTABLE
#define TABLE_SIZE 100000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char* word;
    int frequency;
    int search;
    struct Node* next;
};
typedef struct Node Node;

struct HashTable
{
    Node** nodes;
};
typedef struct HashTable HashTable;

/* function prototypes */

/* generates hashcode for a new word */
unsigned long hashcode(char* newWord);

/* creates the Hash Table */
HashTable* createHashTable(void);

/* allocates memory for new node */
Node* createNode(char* newWord, int freq);

/* adds a node to the Hash Table */
int add(HashTable* hashtable, char* newWord, int freq);

/* print contents of Hash Table */
void printTable(HashTable* hashtable);

#endif

