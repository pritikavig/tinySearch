/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Pritika Vig
 * Date: June 2015
 *
 * Hash Table Methods 
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>                          // mlloc

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "hashtable.h"                       // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

unsigned long JenkinsHash(const char *str, unsigned long mod)
{
    size_t len = strlen(str);
    unsigned long hash, i;

    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}

// Add to the hash table
// 1 if node just got added
// 0 if was already in table


int HashTableAdd(char * url){

    //create a new Hash Table node
    HashTableNode *newNode = malloc(sizeof(HashTableNode));
    newNode->url = (char*) malloc(strlen(url)+1);
    newNode->url = url;
    newNode->next = malloc(sizeof(HashTableNode));
    newNode->next = NULL;

   
    // create a temp node
    HashTableNode *tempNode = malloc(sizeof(HashTableNode));
    tempNode->url = (char*) malloc(strlen(url)+1000);
    tempNode->next = malloc(sizeof(HashTableNode));


    // get key
   
    unsigned long key = JenkinsHash(url, MAX_HASH_SLOT);
 


    //check if it's in Hashtable, if it's not add it
    if(URLSVisited.table[key] == NULL){
        URLSVisited.table[key] = newNode;
        
        return(1);
    }

    //else add it to the end of the list
    else{

        //get the last item at that key and add to the next
        tempNode = URLSVisited.table[key];

        while(tempNode->next != NULL){
            
            if(strcmp(url, tempNode->url) == 0)
            {
                
                return(0);
            }

            tempNode=tempNode->next; 

        }
        
        tempNode->next=newNode;
        
    }
    
    return(1);
}

// Lookup to see if entry is in hashtable 
// returns 0 if its a match
// returns 1 if no match
int HashTableLookUp(char * url){
    //get key
    unsigned long key = JenkinsHash(url, MAX_HASH_SLOT);
    

    //if there is a node at the key
    if(URLSVisited.table[key] != NULL){
        
       //while it node has next
        HashTableNode *tempNode = malloc(sizeof(HashTableNode));
        tempNode->url = (char*) malloc(strlen(url)+1000);
        tempNode->next = malloc(sizeof(HashTableNode));
        tempNode=URLSVisited.table[key];
        tempNode->next=URLSVisited.table[key]->next;
      

        //check everything in the bin
        while(tempNode->next != NULL){
            

            //compare node urls, return 0 on match 
            if(strcmp(url, tempNode->url) == 0){

                return(0);
            }
            
            tempNode=tempNode->next;

        }
        //check last node in list
        if(strcmp(url, tempNode->url) == 0){          
                return(0);
            }       
    }    


    return(1);

}

// Clean the hashtable

void cleanHash(){
    // loop through each hash slot
    unsigned long hashkey = 0;

    while (hashkey < MAX_HASH_SLOT){

        if(!URLSVisited.table[hashkey])
        {
            hashkey = hashkey +1;
        }
        else if(URLSVisited.table[hashkey])
        {
        // free the first node in the bin
        HashTableNode *node = URLSVisited.table[hashkey];
        free(node);
        node = NULL;
        hashkey = hashkey +1; 
        }

    }

}





