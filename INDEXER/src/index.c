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
 int buildIndex(char *path);
 int saveFile(char *fileName);

 // Global Variables
 HashTable Index;

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
 		testingMode = 1;
 	}



 	//////////////////// build directory and write it to file ////////////////
 	
 		// initialize data structures

 		// create index
 		
 		buildIndex(argv[1]);

 		// write to output
 		saveFile(argv[2]);

 		// clean data
 		cleanHash();

 		//////////////////////////////////////////////////////

 		// continue if testing

 		if (testingMode == 1){

 			// rebuild index from file
 			// readFile(argv[2]);

 			// saveFile(argv[3]);

 			// clean
 			// cleanDynamicList(wordIndex);
 		}


 }


 ////////////////////////////// Helper Functions //////////////////////////////////////


 /*
 * buildIndex
 * takes in a directory of files
 * read files one by one
 * puts files into doc nodes in hastable of word nodes
 */

 int buildIndex(char *path){

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
         // TODO: Open file and make buffer
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
         // TESTING: Print all the words in the file:
         int pos = 0;
 		 char *word;

 
 		 while((pos = GetNextWord(buffer, pos, &word)) > 0) {

 		 	NormalizeWord(word);
         	// do something with word
 		 	

 		 	HashIndexAdd(word, filenames[i]);

 		 	//free(word);
         }
         free(buffer);
         //free(filenames[i]);
      }
      free(filenames);
	}
	
	return(0);
 }


// saveFile
// writes contents of hashtable out to file specified in command line
int saveFile(char *fileName){
	// create file

	FILE *fp = freopen(fileName, "w+", stdout);
	if(fp){
		// loop through and write hash table to file
		PrintIndex();
	}
	else{
		fclose(fp);
		return(1);
	}
	fclose(fp);
	return(0);
}

//readFile
// make hashtable out of file

int readFile(char *fileName){
return(0);
}
