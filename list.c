/* ========================================================================== */
/* File: list.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Pritika Vig
 * Date: June 2015
 *
 * Linked List Methods
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>  
#include <stdlib.h>                          // malloc

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "list.h"							// List structures

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes




// initialize head and tail to be null
 int initList(){

		toVisit.head = NULL;
		toVisit.tail=NULL;
		return(0);
								 
 }



// add page to linked list of pages to visit

void listAdd(WebPage *page){
	ListNode *newNode = malloc(sizeof(ListNode));
	


	if(!page){
		return;
	}

	if(!newNode){
		return;
	}

	newNode->page=page;

	if(!toVisit.tail){
		toVisit.tail=newNode;
		toVisit.head=newNode;
	}
	else{
		toVisit.tail->next = newNode;
		newNode->prev = toVisit.tail;
		toVisit.tail = newNode;
	}

	return;

}




//pop out a web page from the beginning
WebPage* listRemove(){
	WebPage *page;
	ListNode *tempNode;

	if(!toVisit.head){
		return NULL;
	}


	tempNode = toVisit.head;
	page = tempNode->page;
	toVisit.head = tempNode->next; 
	
	if(tempNode->next == toVisit.tail){
		toVisit.tail=toVisit.head;
	}
	
	if(!toVisit.head){
		toVisit.tail=NULL;
	}
	if(toVisit.head){
		toVisit.head->prev = NULL;
	}



	free(tempNode);
	return page;
	
}






