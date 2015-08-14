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

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

// ---------------- Public functions

int helloWorld(char *input){
	printf("Hello Wolrd");
	return 1;
}

/*
* Function to add a doc to a word linked list 
*/

int addDocToWord(docRank *dNode, wordHead *wNode){
	if (!dNode){
		return 1;
	}

	if (!wNode){
		return 1;
	}
	// if there is nothing on the end of that word, add the doc and return
	if (wNode->doc == NULL){
		wNode->doc = dNode;
		return 0;
	}

	// else add node to the end
	docRank *tmpDoc = wNode->doc;
	while(tmpDoc->next){
		// skip matches
		if (strcmp(tmpDoc->docID, dNode->docID) == 0){
			return 2;
		}

		tmpDoc=tmpDoc->next;
	}

	tmpDoc->next = dNode;
	dNode->next = NULL;
	return 0;

}
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

///////////////////////////////////////////////////// End rank functions ////////////////////////////////////////

void printList(wordHead *wNode){
	if (!wNode){
		return;
	}

	if (!wNode->doc){
		return;
	}
	printDocs(wNode->doc);
}

void printDocs(docRank *node){

	docRank *tmpDoc = node;
	while(tmpDoc){
		
		printf("\nDoc Id: %s, rank: %i", tmpDoc->docID, tmpDoc->wordCount);
		tmpDoc=tmpDoc->next;
	 
	}
}

///////////////////////////////////////////////// FUNCTIONS TO TEST DELETE //////////////////////////////////













