/* ========================================================================== */
/* File: file.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 *
 * These functions are provided for the students to simplify the manipulation
 * of files and directories.
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>                          // free, calloc
#include <string.h>                          // strlen, strcpy
#include <stdio.h>							// printf


// ---------------- Local includes  e.g., "file.h"
#include "file.h"                             // file/dir functionality
#include "web.h"							  // web functionality
#include "hashIndex.h"

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
 int buildIndex(char *path, HashTable *Index);
 int saveFile(char *fileName, HashTable *Index);
 int readLine(char *fileName, HashTable *wordIndex);
 int parseLine(char *buffer, HashTable *wordIndex);
 int printing(HashTable *Index);


 /* ============================================================================= */

 int main(int argc, char* argv[]){

 	int testingMode = 0; // testing mode default to 0

 	/////////////////////// check command line arguments //////////////////////
 	// two options: 1: dir with index, index.dat file. 2: dir with index, index.dat file, new_index.dat

 	// check argc (3 or 4)

 	if(argc != 3){
 		if(argc != 4){
 		printf("This program takes 2 or 3 arguments: a valid directory and a file for output. If you input a third option, another output file, the program will test itself.");
 		return(1);
 		}
      testingMode =1;
 	}

 	// check that arg 1 is a valid directory

 	if(0 == IsDir(argv[1])){
 		printf("Argument 1 is not a valid directory.");
 		return(1);
 	}

 	// check to see if arg 2 ends in .dat

 	if(strstr(argv[2], ".dat")==NULL){
 		printf("Argument 2 should be a filename ending in .dat");
 		return(1);
 	}

 	// if argc is 4, check argv[3] and set TESTING

 	if (4 == argc){
 		// check string
 		if(strstr(argv[3], ".dat")==NULL){
 			printf("Argument 3 should be a filename ending in .dat");
 			return(1);
 		}
 		// enable testing mode
 		//testingMode = 1;
 	}



 	//////////////////// build directory and write it to file ////////////////
 	
 		// initialize data structures

 		// create and initialize index
      HashTable *myIndex = malloc(sizeof(HashTable));
      initializeIndex(myIndex);

      if(myIndex){
 		   buildIndex(argv[1], myIndex);





 		   // write to output
 		   saveFile(argv[2], myIndex);

 		   // clean data
 		  // cleanHash(myIndex);
      }


 		//////////////////////////////////////////////////////

 		// continue if testing

 		if (testingMode == 1){
         printf("Entered if statement");
         // create and initialize a new index
         HashTable *reIndex = malloc(sizeof(HashTable));
         initializeIndex(reIndex);


         if(reIndex){
 			// rebuild index from file

 			     readLine(argv[2], reIndex);

 			     //saveFile(argv[3], reIndex);

 			     //cleanHash(reIndex);
         }
 	
   	}

      return(0);

 }


 ////////////////////////////// Helper Functions //////////////////////////////////////


 /*
 * buildIndex
 * takes in a directory of files
 * read files one by one
 * puts files into doc nodes in hastable of word nodes
 */

 int buildIndex(char *path, HashTable *Index){

 	// get files in directory path

 	char **filenames = NULL;
 	int num_files = 0;
 	


 	num_files = GetFilenamesInDir(path, &filenames);
 	if(num_files < 0) 
 	{
    // failed to get any filenames (various reasons)
 	} 
 	else 
 	{

      for(int i = 0; i < num_files; i++) 
      {
         printf("File: %s\n", filenames[i]);

         char name[30];
    	   sprintf(name, "%s%s", path, filenames[i]);
    	 


         // looping through files in index here. 
         // Open file and make buffer
         // modelled after stack overflow: http://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
         char *buffer = NULL;
         FILE *fp = fopen(name, "rb");
         if (fp != NULL){
         	// go to end of file
         	if (fseek(fp, 0L, SEEK_END) == 0){
         		long bufsize = ftell(fp);

         		// allocate memory for source
         		buffer = malloc((sizeof(char) * (bufsize+1)));
         		// go to start of file
         		if (fseek(fp, 0L, SEEK_SET) != 0){}
         		// read into memory
         		size_t newLen = fread(buffer, sizeof(char), bufsize, fp);
         		if(newLen ==0)
         		{
         		fputs("error reading file", stderr);
         		}else{
         			buffer[++newLen]= '\0';
         		}

         	}
         	fclose(fp);

         }
         
         int pos = 0;
 		   char *word;

 
 		 while((pos = GetNextWord(buffer, pos, &word)) > 0) {

 		 	NormalizeWord(word);
         	// do something with word

 		   HashIndexAdd(word, filenames[i], Index);
      
 		 	
         }
         free(buffer);
      }      
	}
   free(filenames);
	
	return(0);
 }


// saveFile
// writes contents of hashtable out to file specified in command line
int saveFile(char *fileName, HashTable *Index){
	// create file

	FILE *fp = freopen(fileName, "w+", stdout);
	if(fp){
		// loop through and write hash table to file
		
      int key = 0;
      while (key < MAX_HASH_SLOT){
         if (Index->table[key] != NULL){
            printf("\n %s", Index->table[key]->word);
            printf(" %s %i", Index->table[key]->doc->docID, Index->table[key]->doc->wordCount);

            if(Index->table[key]->doc->next){
             //  docNode *tmp = Index->table[key]->doc->next;
             //  while(tmp->next != NULL){
             //  printf(" wait theres more ");
               
             //  }
            }
         }
         key++;
      }
	}
	fclose(fp);
   freopen ("/dev/tty", "a", stdout);
	return(0);
}



//readLine
// make hashtable out of file
// modelled after code at: http://stackoverflow.com/questions/3081289/how-to-read-a-line-from-a-text-file-in-c-c

int readLine(char *fileName, HashTable *wordIndex){
   // open the index filename
   FILE *fp = fopen(fileName, "r");

   int size = 2048;  // pick an arbitrary starting size
   int charCount;
   int c;
   char *buffer = (char *)malloc(size);

   if(fp){
      do{
         charCount=0;
         

         do {
            c=fgetc(fp);
            printf("%c", c);
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


         // line is now in buffer DO STUFF
         if(buffer){
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
           
            printf("\n rebuilding hash with word: %s", word);
            HashIndexAdd(word, filename, wordIndex);
            i++;
         }
         
         count = count +1;
         i = 0;

      }
      
      // create doc node and add 
      token = strtok(NULL, s);
   }
   count = 0;
   return(0);
}
