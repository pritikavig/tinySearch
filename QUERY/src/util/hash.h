/* ========================================================================== */
/* File: hashIndex.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * This file contains the definitions for a hashtable of urls.
 *
 */
/* ========================================================================== */
#ifndef HASHTABLE_H
#define HASHTABLE_H
// ---------------- Prerequisites e.g., Requires "math.h"

#include <stdio.h>   

// ---------------- Constants
#define MAX_HASH_SLOT 1               // number of "buckets" 10000 

// ---------------- Structures/Types
typedef struct docNode {
	char *docID;
	int wordCount;
	struct docNode *next;
} docNode;

typedef struct wordNode {
    char *word;                               
    struct wordNode *next;              // pointer to next node
    struct docNode *doc; 				// pointer to document
} wordNode;

typedef struct HashTable {
    wordNode *table[MAX_HASH_SLOT];     // actual hashtable
} HashTable;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/*
 * jenkins_hash - Bob Jenkins' one_at_a_time hash function
 * @str: char buffer to hash
 * @mod: desired hash modulus
 *
 * Returns hash(str) % mod. Depends on str being null terminated.
 * Implementation details can be found at:
 *     http://www.burtleburtle.net/bob/hash/doobs.html
 */
unsigned long JenkinsHash(const char *str, unsigned long mod);
void initializeIndex(HashTable *Index);
void printIndex(HashTable *Index);
int addToHash(char *word, char *fileName, HashTable *Index);
void cleanIndex(HashTable *Index);
int hashLookUp(char *word, HashTable *Index);
int addDocs(wordNode *wNode, char* fileName, HashTable *Index);
void printDocs(wordNode *wNode, HashTable *Index);


#endif // HASHTABLE_H
