
// introduction to algorithm class assignment 3
// hash table
// Name : HyungKwon Ko
// Student # : 2014018940

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int j = 0;
int size;
struct HashTable *ht_temp;

HashTable* makeHashTable(int size) {
    int i;
    ht_temp = (struct HashTable*) malloc(size * sizeof(struct HashTable*));
    ht_temp->size = size/3;

    // initializing the table
    for (i=0; i<ht_temp->size; i++) {
        ht_temp[i].data = NULL;
        ht_temp[i].flag = 0;
        //printf("ht_temp[i].flag: %d\n", ht_temp[i].flag);
    }
    
    return ht_temp;
}

void insertHashNode(HashTable* ht, int key, int value)
{
    int i = key % ht->size;
    struct HashNode *new_hn = (struct HashNode*) malloc(sizeof(struct HashNode));
    new_hn->key = key;
    new_hn->value = value;
    
    while(ht[i].flag == 1) { // run until we find the empty spot
        if(ht[i].data->key == key) { // if the same value already exists, we simply update it to the new one
            ht[i].data->value = value;
            return;
        }
        i = (i+1) % ht->size; // since we are doing linear probing, move one step to the right  
    }
    //if flag == 0 or 2
    ht[i].flag = 1; // notation that spot is filled with given data
    ht[i].data = new_hn; // substitution
}

HashNode* findHashNode(HashTable* ht, int key) {
    int index = key % ht->size;
    int i = index;
    while(ht[i].flag != 0) { 
        if(ht[i].flag == 1 && ht[i].data->key == key) {
            //j++;
            //printf("%d found\n", j); // we can see the progress
            return ht[i].data;
        } else if(ht[i].flag == 2){
            i = (i+1) % ht->size; // move it to the next step until we find one
            if(i == index) {
                return NULL;
            }
            continue;
        }
        
        i = (i+1) % ht->size; // move it to the next step until we find one
        
        if(i == index) { //  key doesn't exist -> return NULL
            //j++;
            //printf("%d found\n", j); // to see the progress
            return NULL;
        }
    }
    return NULL;
}

void deleteHashNode(HashTable* ht, int key) {
    int index = key % ht->size;
    int i = index;
    while(ht[i].flag != 0) {
        if((ht[i].flag == 1) && (ht[i].data->key == key)) {
            ht[i].flag = 2; // change the status of given spot
            ht[i].data = NULL; // delete the data
            //j++;
            //printf("%d deleted\n", j); // to see the progress
            return;
        }
        i = (i+1) % ht->size; // follow the same trajectory as above to find the spot given data exists
        
        if(i == index) { // key doesn't exist -> return NULL
            break;
        }
    }
}
