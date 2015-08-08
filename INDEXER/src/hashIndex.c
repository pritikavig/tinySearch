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
#include "hashIndex.h"                       // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes




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


// HashIndexAdd
//returns 1 on problem
int HashIndexAdd(char *word, char *docName, HashTable *Index){
                
    int added = HashIndexLookUp(word, Index);
    unsigned long key = JenkinsHash(word, MAX_HASH_SLOT);



    // WORD IS NOT ALREADY IN INDEX
    if (added == 0){
       
        // create word node & add it
        wordNode *node = malloc(sizeof(wordNode));
        
        node->word = word;
        node->next;
        node->next = NULL;
        

        // dont worry about collisons for now
        wordNode *tempNode = Index->table[key];
        if (tempNode == NULL){
            Index->table[key] = node;
        }

        // CHECK FOR KEY COLLISIONS
        else{
          
            while(tempNode->next!=NULL){
                tempNode=tempNode->next;
            }
            tempNode->next = node;
        }

        addDocNode(node, docName);
        

      
        return(0);
    }

    if (added ==1){
            wordNode *tmp = Index->table[key];
        // add doc node to word node 
            addDocNode(tmp, docName);
           
            return(0);
    }
    
    return(1);     

}



// hashIndexLookUp
// returns 1 if word is in index
// returns 0 if not
int HashIndexLookUp(char *word, HashTable *Index){
	// if word is in index, return 1
	unsigned long hashkey = JenkinsHash(word, MAX_HASH_SLOT);


	if(Index->table[hashkey] != NULL){
		// if the word node matches the word return 1
        wordNode *node = Index->table[hashkey];
        while (node != NULL){

            // compare strings
            if(strcmp(word, node->word) == 0){
               
                
                return(1);
            }

            node = node->next;
        }
		
	}
	// else return 0
    
	return(0);
}
// clean Hash table
// clean all allocated data
void cleanHash(HashTable *Index){
        unsigned long key =0;

        while(key <= MAX_HASH_SLOT) {
            if(Index->table[key] != NULL){
                wordNode *tmpNode = Index->table[key];
                wordNode *nextNode;
                if(tmpNode->next != NULL){
                    nextNode = tmpNode->next;
                    //clearDocs(tmpNode);
                    free(tmpNode);
                    tmpNode=nextNode;
                    
                }
                //clearDocs(tmpNode);
                free(tmpNode);

            }

            key = key +1;
        }
}

void clearDocs(wordNode *wNode){
        if(wNode->doc != NULL){
        docNode *tmpDoc = wNode->doc;
        docNode *nextDoc;
        while(tmpDoc->next != NULL){
            nextDoc = tmpDoc->next;
            //free(tmpDoc->docID);
            free(tmpDoc);
            tmpDoc=nextDoc;
        }
        //free(tmpDoc->docID);
        free(tmpDoc);

    }

}

int addDocNode(wordNode *wordNode, char* docName){
    // go through docs in wordnode, if doc there, increment count and return
    if(wordNode->doc != NULL){
        // check all doc nodes for a match
        docNode *tmpDoc = wordNode->doc;
        while(tmpDoc != NULL){
            // compare words
             if(strcmp(docName, tmpDoc->docID) == 0){
               
                tmpDoc->wordCount = tmpDoc->wordCount +1;
                return(1);
            }

            tmpDoc=tmpDoc->next;
        }
    }

        // if doc not there, create doc node


        
        docNode *node = malloc(sizeof(docNode));
        node->docID = malloc(strlen(docName)+1);
        node->docID = docName;
        node->wordCount = (int) 1;
        node->next = malloc(sizeof(docNode));
        node->next = NULL;

        if (wordNode->doc == NULL){
            wordNode->doc = node;
            return(1);
        }else{
            docNode *tmp = wordNode->doc;
            while(tmp->next != NULL){
                tmp=tmp->next;
            }
            tmp->next=node;
            return(1);
        }


    return(0);
}

void PrintIndex(HashTable *Index){
        unsigned long key =0;

        while(key <= MAX_HASH_SLOT){
        
        if(Index->table[key] != NULL){
            wordNode *tmpNode = Index->table[key];
            while(tmpNode->next != NULL){
                printf("\n%s", tmpNode->next);
                PrintDocs(tmpNode->next);
                tmpNode=tmpNode->next;
                
            }
            printf("\n%s", tmpNode->word);
            PrintDocs(tmpNode);

        }

        key = key +1;
        }
}

// print out any docs attached to a word node
void PrintDocs(wordNode *wNode){
    if(wNode->doc != NULL){
        docNode *tmpDoc = wNode->doc;
        while(tmpDoc->next != NULL){
            printf(" %s %i", tmpDoc->docID, tmpDoc->wordCount);
            tmpDoc=tmpDoc->next;
        }
        printf(" %s %i", tmpDoc->docID, tmpDoc->wordCount);
    }
}










