/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author: Pritika Vig
 * Date: July 2015
 *
 * Input: URL, Directory, Depth Integer
 *
 * Command line options: None
 *
 * Output: None -  html files in dir
 *
 * Error Conditions:
 *
 * Special Considerations:
    -lcurl

    check for memory leaks:
    valgrind --leak-check=full crawler "http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/C_(programming_language).html" lab4/ 1

    // Test url: http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/C_(programming_language).html
 *
 */
/* ========================================================================== */
// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>                           // printf
#include <sys/stat.h>                        // isdir
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>                       // curl functionality
#include <string.h>                          // strncmpr

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality
#include "utils.h"                           // utility stuffs

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
int isValidURL(char * URL);
int isDirec(char * dir);
int writePage(WebPage *page, char *dir, int x);
int crawlPage(WebPage *page);
int saveCrawl();
void cleanup();

// Global:
HashTable URLSVisited;
List toVisit;
/* ========================================================================== */






int main(int argc, char* argv[])
{

    ////////////////////////////////// check command line arguments /////////////////////////
    if (argc != 4){
        printf("Crawl needs three arguments: a valid URL, a directory, and an integer for maximum depth of crawl.");
        return(1);
    }

    // check that last argument is an integer less than or equal to three
    if(atoi(argv[3]) < 0 || atoi(argv[3]) > MAX_DEPTH){
        printf("Argument 3 needs to be an integer for maximum depth. Maximum depth should not be greater than 4. ");
        return(1);
    }

    // check that second argument is a directory
    if ( (int) isDirec(argv[2]) != 0){
        printf("\nProblem with Directory. Quitting. \n");
        return(1);
    }
    // check that first argument is a URL and within our domain

    if ( (int) isValidURL(argv[1]) != 0){
        printf("\nURL is not within our specified domain. Quitting.\n");
        return(1);
    }


    //////////////////////////////////////////////////////////////////////////////////////////
    


    // Variables
    int max_depth = atoi(argv[3]);
    int fileCounter = 1;
    char *dir = argv[2];
    initList();
    
   

    // init curl
    curl_global_init(CURL_GLOBAL_ALL);

    // setup seed page
    WebPage *page = calloc(1, sizeof(WebPage));
    page->url = (char*) malloc(strlen(argv[1])+1);
    strcpy(page->url, argv[1]);
    page->depth = 0;

    //Print output in STATUS_LOG mode
    if(STATUS_LOG == 1){
        printf("\nSeed URL: %s", page->url);
    }
    
    // get seed webpage
    GetWebPage(page);

    // write seed file & update counter
    writePage(page, dir, fileCounter);
    fileCounter=fileCounter+1;
  

    // add seed page to hashtable
    HashTableAdd(page->url);

    if (max_depth != 0)
    {
    crawlPage(page);
   
    saveCrawl(dir, fileCounter, max_depth);
    }
    // cleanup curl
    curl_global_cleanup();


    //// FREE STUFF
    // cleanup memory
    cleanup();
    


    return(0);
}




/////////////////////////////////////////////////////////////Helpler Functions///////////////////////////////////////////////
// check that  argument is a URL and within our domain
// return 1 if invalid
// return 0 if valid

int isValidURL(char * URL){
    int i;
    i = strncmp(URL, URL_PREFIX, 41);
    if( i != 0 ){
        return(1);
    }
    return(0);
}

// check that  argument is a directory that exists

int isDirec(char * dir){
        
    struct stat s;
    int err = stat(dir, &s);
    if(-1 ==err )
    {
       printf("Problem with Dir");
       return(1);
    }
    else{
        if(S_ISDIR(s.st_mode))
        {
            return(0);
        }
        else
        {
            printf("Something exists, but it's not a dir :(");
            return(1);
            
        }
    }
}

// write page to file in directory
// return 0 on success
// return 1 on no write
int writePage(WebPage *page, char *dir, int x){
   
    char name[30];
    sprintf(name, "%s%i", dir, x);
    FILE *fp = fopen(name, "ab+");
    if(fp){
        fputs(page->url, fp);
        fprintf(fp, "\nDepth: %i\n", page->depth);
        fputs(page->html, fp);
        fclose(fp);

        return(0);
    }
    if (fp == NULL){
        fprintf(stderr, "Error opening.");
        return(1);
    }

    return(0);
  }

// Get the next Url, Normalize it, check to see if it's in the linked list, add it to list

int crawlPage(WebPage *page){
    int pos =0;
    char *result = NULL;

    //STATUS_LOG mode print log
    if(STATUS_LOG == 1){
        printf("\n\nParsing page for urls: %s", page->url);
    }

    while (pos != -1){
        pos = GetNextURL(page->html, pos, page->url, &result);
        // normalize URL
        NormalizeURL(result);
        // check to see if it's in the domain
        if(isValidURL(result) == 0)
        {
        // check to see if it's in hash table
        
        int visited = HashTableLookUp(result);
       
        if (visited == 1){

            // get new depth value
            int newDepth = page->depth +1;
            // create web struct
                WebPage *newPage = calloc(1, sizeof(WebPage));
                newPage->url = (char*) malloc(strlen(result)+1);
                strcpy(newPage->url, result);
                newPage->depth = newDepth;

            //STATUS_LOG mode print log
            if(STATUS_LOG == 1){
                printf("\nFound url: %s", newPage->url);
            }
            // add to linked list
                listAdd(newPage); 
            // Add to hash table
                HashTableAdd(newPage->url); 
                
        }

      }
        
    }  
    
    return(1);
}

// Loop through linked list and save all pages to directory 
int saveCrawl(char *dir, int fileCounter, int max_depth){

// for page in linked list: 
    WebPage *page;
    
    while(toVisit.head){
         page = listRemove();
         int status = GetWebPage(page);
         //sleep(1);
      
         if (status == 1 )
         {
            writePage(page, dir, fileCounter);
            fileCounter= fileCounter+1;
         // get next page
         // crawl until depth 
            if(page->depth < max_depth)
            {
                crawlPage(page);
            }  
            free(page->html);
            free(page);
            page->html=NULL;
            page=NULL;
        }

    }

    return 0;   
 }

// Cleanup memory

 void cleanup(){
    //free the hash table
    cleanHash();         

 }