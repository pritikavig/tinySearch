/* 	rank.h


	Project name: Tiny Search Engine
	Component name: Query

	This file contains functions from rank.c
	
	Primary Author:	Pritika Vig
	Date Created:	Aug 2015
	
======================================================================*/
// do not remove any of these sections, even if they are empty

#ifndef INC_FILE_H
#define INC_FILE_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "hash.h"

// ---------------- Constants

// ---------------- Structures/Types

typedef struct docRank {
	char *docID;
	int wordCount;
	struct docRank *next;
} docRank;

typedef struct wordHead {
	char *word;
	struct docRank *doc;
	struct wordHead *next;
} wordHead;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

int helloWorld(char *input);
void printList(wordHead *wNode);
docRank* split (docRank *head);
docRank* sort(docRank *a, docRank *b);
docRank* mergeSort(docRank *firstHead);
int addDocToWord(docRank *dNode, wordHead *wNode);
void printDoc(docRank *node);
wordNode* returnWord(char *word, HashTable *Index);
wordHead* addToList(wordNode *wNode, wordHead *head);
void grabURL(char *docName, char *pathToDir);
void finalPrint(docRank *first, char *pathToDir);




#endif // INC_FILE_H
