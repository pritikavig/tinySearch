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



// ---------------- Local includes  e.g., "file.h"

#include "rank.h"
#include "hash.h"
#include "file.h"
#include "web.h"

// ---------------- Constant definitions 
#define big 1000

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 



int parseLine(char *buffer, HashTable *wordIndex);
int rebuildIndex(char *fileName, HashTable *wordIndex);
int getWord(char *array, HashTable *Index, char *pathToDir);
/*====================================================================*/

int main(int argc, char* argv[]){

	
	// check command line arguments
	if(argc != 3){
		perror("Incorrect number of arguments");
		return 0;
	}
	// use isFile from library and isdir

	if(IsDir(argv[1]) == 0){
		perror("Arg 2 must be a valid directory. Format: ./example/direc/");
		return 0;
	}

	if(IsFile(argv[2]) == 0){
		perror("Arg 3 must be a valid file.");
		return 0;
	}

  //Welcome message
  printf("Rebuilding Index. Enter AND and OR query strings when you see the <Query> prompt. Query engine will ignore trivial words and only return the top 20 hits.");

	// rebuild index with readFile
	HashTable *Index = malloc(sizeof(HashTable));
  printf("\nRebuilding index ...");
	initializeIndex(Index);
	rebuildIndex(argv[2], Index);
	printf("Rebuilt");

	//printIndex(Index);



	// start taking input from command line. run until quit 
	while(1){
    char line[big];
    char*buffer = malloc(sizeof(char)*big);


		fputs("\n<Query>", stdout);

		// get line 
		// print line back 
		if (fgets(line, big, stdin) != NULL){

			   line[strlen(line)-1]='\0';
         strcpy(buffer, line);
			   getWord(buffer, Index, argv[1]);
		}

		if(feof(stdin)){
			cleanIndex(Index);
      free(buffer);
			free(Index);
        	return 0;
      }
	}

	return 0;

}




int getWord(char *array, HashTable *Index, char *pathToDir){
    const char s[2] = " ";
    char *token;
    int flag = 0; // keeps track of logical operators 0 = AND 1 = OR
    int track = 0;
  

    // make a word head to keep track of tmp list
    wordHead *tmpList = malloc(sizeof(wordHead));
    tmpList->word = "temp";
    tmpList->doc=NULL;

    // make a word head to keep track of final list
    wordHead *finalList = malloc(sizeof(wordHead));
    finalList->word = "final";
    finalList->doc=NULL;
   
  
    token = strtok(array, s);
 
    while(token != NULL)
     {
        
     		char *word = malloc(strlen(token)+1);
     		strcpy(word, token);

    		// check for logical operators
    		if(strcmp(word, "AND")==0){
    			flag = 0;
    		}
    	    else if(strcmp(word, "OR")==0){
    			flag = 1;
    		} else if(strcmp(word, "the") == 0){
          flag = 0;
        } else if(strcmp(word, "it") == 0 || strcmp(word, "what") == 0 || strcmp(word, "how") == 0 || strcmp(word, "why") == 0 || strcmp(word, "a") == 0){
          flag = 0;
        } else if (strcmp(word, "at") == 0 || strcmp(word, "be") == 0 || strcmp(word, "by") == 0){
          flag = 0;
        }

    		// otherwise, find docs!
    		else {
    			//normalize the word
    			NormalizeWord(word);
    			wordNode *tmp = returnWord(word, Index);
          track = track +1;
                if(!tmp){
                  printf("One or more of the words that you entered is not in our index.");
                  return 1;
                }


            	   if(flag == 0)
                 { 
                    if(!tmpList->doc && track > 1){
                      printf("At least one combination of arguments has no intersection\n");
                      return 0;
                    }
                    else{
            			  andToList(tmp, tmpList);   
                    }         			 
            	   }

            	   else
                 {
                    track = 1;
                    mvList(tmpList, finalList);
                    tmpList->doc=NULL;
            		    andToList(tmp, tmpList);
            		    flag = 0;

            	   }

        	}
            token = strtok(NULL, s);
           
            free(word);
     }
    mvList(tmpList, finalList);
    docRank *head = mergeSortID(finalList->doc);    
    combineNodes(head); 
    docRank *newHead = mergeSort(head);   
    finalPrint(newHead, pathToDir);
    if(!head){
      printf("One or more of the words that you entered is not in our index.");
    }
    cleanHead(head);
 
     return 0;
 }












////////////////////////////////// Function to rebuild an index from scratch ////////////////////////////////////


//readLine
// make hashtable out of file
// modelled after code at: http://stackoverflow.com/questions/3081289/how-to-read-a-line-from-a-text-file-in-c-c

int rebuildIndex(char *fileName, HashTable *wordIndex){
   // open the index filename
   FILE *fp = fopen(fileName, "r");

   int size = 2048;  // pick an arbitrary starting size
   int charCount;
   int c;
   char *buffer = (char *)malloc(size);
   int i = 0;

   if(fp){
      do{
         charCount=0;
         

         do {
            c=fgetc(fp);
            if(c != EOF)
            {
              buffer[charCount++] = (char)c; 
            } 
            if(charCount >= size -1)
            {
               size = size*2; // double buffer size to prevent overflows if character count is close to size
               buffer= (char*)realloc(buffer,size);
               // 
            }
         }while(c != EOF && c != '\n');


         buffer[charCount] = 0; // set end for protection

         if(buffer){
            //printf("%i", i);
            i++;

            parseLine(buffer, wordIndex);
         }
      } while (c != EOF);
   }

   fclose(fp);
   free(buffer);

return(0);
}


 int parseLine(char *buffer, HashTable *wordIndex){
   // parse line and add nodes
   const char s[2] = " ";
   char *token = strtok(buffer, s);
   int count = 0;
   char *word;
   char *filename;
   int filecount;

   while (token != NULL){
      
      // add first token to as word node
      // if count = 0 : create word node, increment count
      if(0 == count){
         word = malloc(strlen(token)+1);
         strcpy(word, token);
         
         count = count + 1;


      }
      // else: if count is odd, create doc node, save doc name somewhere, increment count
      else if (count%2){
         filename = malloc(sizeof(token)+1);
         strcpy(filename, token); 
         count = count +1;


      }
      else if(count%2 == 0){
      // else: if count is even, add number to value of doc node saved, set doc name to null, increment count
         
         filecount = atoi(token);
       
         int i = 0;
         
         while ( i < filecount){
            
            addToHash(word, filename, wordIndex);
            i++;
            
         }
         
         count = count +1;
         i = 0;
         free(filename);


      }
      
      // create doc node and add 
      token = strtok(NULL, s);
   }
   
   free(word);
   return(0);
}









