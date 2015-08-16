/*	rank.c	build and sort the linked list for rank

	Project name: TinySearchEngine
	Component name: Query

	This file contains methods to build a list of outputs and rank docNodes
	
	Primary Author:	Pritika Vig
	Date Created:	Aug 2015

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>                          // free, calloc
#include <string.h>                          // strlen, strcpy
#include <stdio.h>	
                          

// ---------------- Local includes  e.g., "file.h"

#include "rank.h"  
#include "hash.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

// ---------------- Public functions


/////////////////////////// Merge Sort the linked list //////////////////////


// implementation modelled after:
// http://www.geeksforgeeks.org/merge-sort-for-linked-list/
// and http://ideone.com/kq0hZP

// returns 0 on successful sort
docRank* mergeSort(docRank *firstHead){

	if (!firstHead){
		return firstHead;
	}

	if (!firstHead->next){
		return firstHead;
	}

	// otherwise merge sort!

	// split the list in two
	docRank *tmp = split(firstHead);

	// sort the first half
	firstHead = mergeSort(firstHead);

	// sort the second half
	tmp = mergeSort(tmp);

	// put them together and return it
	return sort(firstHead, tmp);


}

//sort 
docRank* sort(docRank *a, docRank *b){
	// base case (either are null)
	if (!a){
		return b;
	}
	if (!b){
		return a;
	}

	docRank *tmp;

	// recursively sort 
	if (a->wordCount >= b->wordCount){
		tmp = a;
		tmp->next = sort(a->next, b);
	}
	else
	{
		tmp = b;
		tmp->next = sort(a, b->next);
	}
	
	return(tmp);
}

docRank* split (docRank *head){
	docRank *tmp = head;
	docRank *tmp2 = head;
	while(tmp->next && tmp->next->next){
		tmp = tmp->next->next;
		tmp2 = tmp2->next;
	}

	docRank *tmp3 = tmp2->next;
	tmp2->next = NULL;
	return tmp3;

}

///////////////////////////////////////////////////// functions to print nodes  ////////////////////////////////////////

void printList(wordHead *wNode){
	if (!wNode){
		return;
	}

	if (!wNode->doc){
		return;
	}
	printDoc(wNode->doc);
}

void printDoc(docRank *node){

	docRank *tmpDoc = node;
	while(tmpDoc){
		
		printf("\nDoc Id: %s, rank: %i", tmpDoc->docID, tmpDoc->wordCount);
		tmpDoc=tmpDoc->next;
	 
	}
}

void finalPrint(docRank *first, char *pathToDir){
	if(!first){
		return;
	}

	// print doc name and rank
	docRank *tmp = first;
	while(tmp){
		// find URL and print that too
		printf("Doc ID: %s Rank: %i", tmp->docID, tmp->wordCount);
		// get url
		grabURL(tmp->docID, pathToDir);
		tmp=tmp->next;
	}
	return;
	
}

///////////////////////////////////////////////// function to return word node queried //////////////////////////////////


wordNode* returnWord(char *word, HashTable *Index){
	if (!Index){
		printf("\n No index exists");
		return NULL;
	}

	if (!word){
		printf("\n Not a valid word");
		return NULL;
	}


	// else find and return the word node queried
	unsigned long key = JenkinsHash(word, MAX_HASH_SLOT);

	if (Index->table[key] == NULL){
		return NULL;
	}

	wordNode *tmp = Index->table[key];
	while(tmp){

		// if string matches, return node;
		if (strcmp(tmp->word, word)==0){
			return tmp;
		}

		tmp = tmp->next;
	}
	return NULL;
}

void grabURL(char *docName, char *pathToDir){
	char name[30];
	char string [10000];
    sprintf(name, "%s%s", pathToDir, docName);
    FILE *fp = fopen(name, "r");
    if (fp){
    	fgets(string, 10000, fp);
    	printf(" URL: %s", string);
    }
    fclose(fp);
    return;
}


////////////////////////////////////////////// Functions to create list //////////////////////////////////////

void andToList(wordNode *word, wordHead *head){
	if (!head){
		return;
	}
	if (!word){
		return;
	}

	// if there is no word attached, add all docs!
	if (!head->doc){
		addtoHead(word, head);
		return;
	}


	else{
		docNode *tmpDoc = word->doc;
		docRank *tmpRank = head->doc;
		wordHead *tmpHead;
		tmpHead->doc = NULL;
		

		// else loop through doc nodes
		// loop through listhead hodes

		while(tmpDoc){
			
			while(tmpRank){

				// on a match, increment count
				if(strcmp(tmpDoc->docID, tmpRank->docID)==0){
					tmpRank->wordCount=tmpRank->wordCount + tmpDoc->wordCount;
					// add to a temp list to hold intersection
					printf("added doc: %s", tmpRank->docID);
					tmpRank->next = NULL;
					addRank(tmpRank, tmpHead);

				}

				tmpRank=tmpRank->next;
			}
			tmpDoc=tmpDoc->next;
		}
		// at the end reset the list to the tmp
		head->doc = tmpHead->doc;
		return;
	}

	return;
}

void addtoHead(wordNode *word, wordHead *head){
	if(!head){
		return;
	}
	if(!word){
		return;
	}

	docNode *tmpDoc = word->doc;
	while(tmpDoc){
		// create a docRank Node
		docRank *newNode = malloc(sizeof(newNode));
		newNode->next = NULL;
		newNode->docID = malloc(strlen(tmpDoc->docID)+1);
		strcpy(newNode->docID, tmpDoc->docID);
		newNode->wordCount = tmpDoc->wordCount;
		
		if(!head->doc){
			head->doc=newNode;
		}
		else{
			docRank *tmpRank = head->doc;
			while(tmpRank->next){
				tmpRank=tmpRank->next;
			}
			tmpRank->next = newNode;
		}
		// add it to word head

		tmpDoc=tmpDoc->next;
	}

	return;

}

void addRank(docRank *docR, wordHead *tmpHead){
	if(!tmpHead){
		return;
	}
	if(!docR){
		return;
	}
	if(!tmpHead->doc){
		tmpHead->doc=docR;
		return;
	}
	docRank *tmp = tmpHead->doc;
	while(tmp->next){
		tmp=tmp->next;
	}
	tmp->next = docR;
	return;
}


void mvList(wordHead *tmpList, wordHead *finalList){
	if(!tmpList){
		return;
	}
	if(!finalList){
		return;
	}
	if(finalList->doc == NULL){
		finalList->doc = tmpList->doc;
		tmpList->doc = NULL;
		return;
	}

 return;

	//loop through nodes in tmpList
	// loop through nodes in final list
			// if match, increment final list count
			// else add tmp node to a buffer  list

	// add buffer to end of final list
}



