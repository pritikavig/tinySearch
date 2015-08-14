/*	query.c	command line query interface

	Project name: TinySearchEngine
	Component name:	Query

	This file contains the user interface to query documents crawled and indexed by part 1 and 2 of this lab.
	
	Primary Author:	Pritika Vig
	Date Created: Aug 2015	

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 

	Command line arguments:
		run with: query <index.dat file> <path to crawler dir>
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>

#include <stdlib.h>                          // free, calloc
#include <string.h>                          // strlen, strcpy
#include <stdio.h>							// printf
//#include <./../../util/hash.h>
//#include <../util/file.h>
//#include <../util/web.h>
//#include <../util/common.h>
#include <dirent.h> 						// loop through files in dir
#include "rank.h"


// ---------------- Local includes  e.g., "file.h"

// ---------------- Constant definitions 
#define big 1000

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

void printURL(char *docName, char *pathToDir);
void grabURL(char *docName, char *pathToDir);
/*====================================================================*/

int main(int argc, char* argv[]){


	// check command line arguments
	if(argc != 3){
		perror("Incorrect number of arguments");
		return 1;
	}
	// use isFile from library and isdir




	// rebuild index with readFile

	// TEST merge sort

	if (argc == 3){
		// head word node
		char *word = "the";
		wordHead *head = malloc(sizeof(wordHead));
		head->word = word;
		head->doc = NULL;

		// create some docs and add them to a list
		char *ID = "document1";
		int count = 5;
		docRank *node = malloc(sizeof(docRank));
		node->docID = ID;
		node->wordCount = count;
		node->next=NULL;


		addDocToWord(node, head);


		// create some docs and add them to a list
		char *ID1 = "document2";
		int count1 = 7;
		docRank *node1 = malloc(sizeof(docRank));
		node1->docID = ID1;
		node1->wordCount = count1;
		node1->next=NULL;

	
		addDocToWord(node1, head);


		// create some docs and add them to a list
		char *ID3 = "document3";
		int count3 = 3;
		docRank *node3 = malloc(sizeof(docRank));
		node3->docID = ID3;
		node3->wordCount = count3;
		node3->next=NULL;

		addDocToWord(node3, head);


		char *ID4 = "document4";
		int count4 = 10;
		docRank *node4 = malloc(sizeof(docRank));
		node4->docID = ID4;
		node4->wordCount = count4;
		node4->next=NULL;


		addDocToWord(node4, head);

		printList(head);

		docRank *newDoc = mergeSort(head->doc);
		printf("\nsorted");
		printDocs(newDoc);


		printf("\n\n Testing dir function");
		char *name = "hi";
		printURL(name, argv[1]);

		return 0;
	}


	// start taking input from command line. run until quit 
	while(1){
		char *line = malloc(sizeof(char) * big);
		// print "query"
		fputs("<Query>", stdout);

      
		// get line 
		// print line back 
		if (fgets(line, big, stdin) != NULL){

         fputs(line, stdout);

         // V0: 
         // parse word by word
         // normalize word
         //look words up in hashtable 
         // create a big linked list
         // sort results
         // print top 20 + urls

         // todo: write the parse word by word/ normalize word
		}


		if(feof(stdin)){
         return 0;
      }
		
	}

	return 0;

}

	// loop through files in directory
	// while files in directory
	// strcmpr docname, path/filename
	//print out the first line of the file
void printURL(char *docName, char *pathToDir)
{
	DIR *dirp = opendir(pathToDir);
	if (!dirp){
		printf("Error opening directory");
		return;
	}
	struct dirent *dp;
	while ((dp = readdir(dirp)) != NULL){
		if(strcmp(dp->d_name, docName) == 0){
			closedir(dirp);
			printf("\n%s == %s", docName, dp->d_name);
			// function to print first line
			grabURL(docName, pathToDir);
			return;
		}
	}
	closedir(dirp);
	printf("File not in directory");
	return;
}

void grabURL(char *docName, char *pathToDir){
	char name[30];
	char string [10000];
    sprintf(name, "%s%s", pathToDir, docName);
    FILE *fp = fopen(name, "r");
    if (fp){
    	fgets(string, 10000, fp);
    	fputs(string, stdout);
    }
    fclose(fp);
}






