/* ========================================================================== */
/* File: hashIndex.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * Author: Pritika Vig
 * Date: Aug 2015
 *
 * Hash Table Methods 
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>                          // mlloc

// ---------------- Local includes  e.g., "file.h"
#include "hash.h"                       // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
 void cleanDocs(wordNode *node);


// Initialize Index
void initializeIndex(HashTable *Index){
    unsigned long key =0;
    while(key <= MAX_HASH_SLOT) {
        Index->table[key]=NULL;
        key = key +1;
    }

    return;

}

// Hash Function

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

void printIndex(HashTable *Index){
    unsigned long key = 0;

    while(key <= MAX_HASH_SLOT)
    {
        if(Index->table[key])
        {
            

            wordNode *tmpNode = Index->table[key];
            while(tmpNode->next != NULL)
            {
                printf("\n%s", tmpNode->word);
                printDocs(tmpNode, Index);
                tmpNode=tmpNode->next;
                
            }
          
            printf("\n%s", tmpNode->word);
            printDocs(tmpNode, Index);

            
        }
        key++;
    }

    return;
}

// add to hashtable
// 0 if already added
// 1 if adding here
// 3 if allocation error

int addToHash(char *word, char *fileName, HashTable *Index){
    // get key 
    unsigned long key = JenkinsHash(word, MAX_HASH_SLOT);



    // if word is in hashtable, add doc and return 
    if(hashLookUp(word, Index) == 0){

        // get word doc
        if(strcmp(Index->table[key]->word, word) == 0){
            addDocs(Index->table[key], fileName, Index);
            return 0;
        }

        wordNode *tmp = Index->table[key];
        while(tmp){
            if(strcmp(tmp->word, word) == 0){
                addDocs(tmp, fileName, Index);
            }
            tmp= tmp->next;
        }
       return 0;
    }

/////////////////////////////////////////////////////////////////////////////////////
    // create node
    wordNode *node = malloc(sizeof(wordNode));
    node->word = malloc(strlen(word)+1);
    strcpy(node->word, word);
    node->next = NULL;
    node->doc = NULL;


    if(!node){
      
        return 3;
    }

    if(Index->table[key] == NULL){
        
        Index->table[key] = node;
        addDocs(Index->table[key], fileName, Index);
        return 1;
    }

    // if hashtable new word 
    if(hashLookUp(word, Index) == 1){
        
        if(Index->table[key]){
            wordNode *tmpNode = Index->table[key];
            while(tmpNode->next != NULL){
                tmpNode=tmpNode->next;
            }

            tmpNode->next = node;
            addDocs(tmpNode->next, fileName, Index);
            return 1;
        }
    }


return 0;

}

// hashtable look up
// return 0 if found

int hashLookUp(char *word, HashTable *Index){
    unsigned long key = JenkinsHash(word, MAX_HASH_SLOT);
    
    if(Index->table[key] == NULL){
        return 1;
    }

    if(Index->table[key] != NULL){
     
        // loop through and string compare
        wordNode *tmp = Index->table[key];
        while(tmp){
            if(strcmp(word, tmp->word) == 0){
                
                return 0;
            }
            tmp = tmp->next;
        }
    }

    return 1;
}


////////////////////////////////


void cleanIndex(HashTable *Index){
    unsigned long key = 0;

    while(key <= MAX_HASH_SLOT){
        if(Index->table[key]){

            wordNode *tmpNode = Index->table[key];
            while(tmpNode->next != NULL)
            {
                cleanDocs(tmpNode);
                free(tmpNode->word);
                free(tmpNode);
                tmpNode=tmpNode->next;
                
            }
            cleanDocs(tmpNode);
            free(tmpNode->word);
            free(tmpNode);
        }

        key++;
    }
}

void cleanDocs(wordNode *node){
    if(!node){
        return;
    }

    if(node->doc == NULL){
        return;
    }

    docNode *tmp = node->doc;
    while(tmp){
        free(tmp->docID);
        free(tmp);
        tmp=tmp->next;
    }
    return;

}


////////////////////////////////////////// DOC NODE FUNCTIONS /////////////////////////////////////////////////////////////

int addDocs(wordNode *wNode, char* fileName, HashTable *Index){

    if(!Index){
        return 3;
    }

    // if the doc is in the list, increment count
    if(wNode->doc != NULL){

        docNode *tmp = wNode->doc;
        while(tmp != NULL){
            if(strcmp(tmp->docID, fileName) == 0){
                tmp->wordCount = tmp->wordCount + 1;
                return 1;
            }
            tmp = tmp->next;
        }

    }


    // if the doc is not in the list, create it
    docNode *newNode = malloc(sizeof(docNode));
    newNode->docID = malloc(strlen(fileName)+1);
    strcpy(newNode->docID, fileName);
    newNode->wordCount = (int) 1;
    newNode->next = NULL;


    if(newNode){
        // if there are no doc nodes on this word, add the doc node
         if(wNode->doc == NULL){
            wNode->doc = newNode;
            return 0;
        }

    // otherwise loop to the end

        docNode *tmp = wNode->doc;
        while(tmp->next != NULL){
            tmp=tmp->next;
        }
        tmp->next = newNode;
        return 0;
    }

return 1;


}

void printDocs(wordNode *wNode, HashTable *Index){
    if(!wNode){
        return;
    }

    if(wNode->doc == NULL){
        return;
    }

    docNode *tmp = wNode->doc;
    while(tmp){
        printf(" %s %i", tmp->docID, tmp->wordCount);
        tmp=tmp->next;
    }
    return;
}



