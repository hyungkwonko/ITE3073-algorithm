
// Introduction to Algorithm class assignment 3
// perfect hash
// Name : HyungKwon Ko
// Student # : 2014018940

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int size;
struct HashTable *ht_temp;

int find(struct HashTable *ht2, int key, int index) {
    int i = index % ht2->size;
    int j = i;
    int k = 0; // used this instead of boolean 

    struct HashNode *temp = ht2->data[i].node;

    while(k != 1) {
        if(temp ==NULL) { // run if it is not NULL
            i = (i+1) % ht2->size; // assign next index
            temp = ht2->data[i].node;
        } else {
            if(temp->key == key) { // return the index if we find the one
                k = 1;
                return i;
            } else {
                i = (i+1) % ht2->size; // assign next index
                temp = ht2->data[i].node;
            };
        }
        if(i == j ) { // end the loop if it has run one cycle
            k = 1;
            return -1;
        }
    }
}

HashTable* makeHashTable(int size, int* sizeTable) {
    int i = 0;
    int j = 0;
    // dynamic allocation is still confusing to me... so the usage of it might be somewhat inappropriate..
    // but still the code runs well with it
    ht_temp = (struct HashTable*) malloc(size * sizeof(struct HashTable*));
    ht_temp->size = size/3;
    
    for(i=0;i<ht_temp->size; i++) {
        ht_temp[i].data = (struct HashTable*) malloc(size * sizeof(struct HashTable*));
    }
    for(i=0; i<ht_temp->size; i++) {
        ht_temp[i].data->data = (struct HashTable*) malloc(size * sizeof(struct HashTable*));
        ht_temp[i].data->size = sizeTable[i]*sizeTable[i]; // initializing the size of it as double
        for(j=0; j<ht_temp[i].data->size; j++) {
            ht_temp[i].data->data[j].node = (struct HashNode*) malloc(ht_temp[i].data->size * sizeof(struct HashNode*));
            ht_temp[i].data->data[j].node = NULL; // intializing the pointer with NULL
        }
    }
    return ht_temp;
}

void insertHashNode(HashTable* ht, int key, int value) {
    int i = key % ht->size; // simple hash function
    int j = i % ht[i].data->size; // simple hash function for the second table
    int k = 0;
    int t = j; // flag

    struct HashNode *temp = (struct HashNode*) malloc(sizeof(struct HashNode));
    
    temp->key = key;
    temp->value = value;

    if(ht[i].data->data[j].node == NULL) { // put it if it is empty
        ht[i].data->data[j].node = temp;
        k = 1;
    } else {
        while(k != 1) { // allocate next hash value it is already packed
            j = (j+1) % ht[i].data->size;
            if(ht[i].data->data[j].node == NULL) {
                ht[i].data->data[j].node = temp;
                k = 1;
            }
            if(j == t) { // if it runs one cycle, escape
                printf("no room for new key");
                break;
            } 
        }
    }
}

HashNode* findHashNode(HashTable* ht, int key) {
    int i = key % ht->size;
    int j = i % ht[i].data->size;
    
    struct HashTable *ht2 = (struct HashTable*) ht[i].data;
    struct HashTable *tdata = (struct HashTable*) ht2->data; 
    
    int ix = find(ht2, key, i);
    if(ix == -1) {
        return NULL; // ix=-1 means there is no matching key so return NULL then the main.c will cover the rest
    } else {
        struct HashNode *temp = tdata[ix].node;
        return temp; // return the pointer node
    }
}

void deleteHashNode(HashTable* ht, int key) {
    int i = key % ht->size; // the same hash function

    struct HashTable *ht2 = (struct HashTable*) ht[i].data;
    struct HashTable *tdata = (struct HashTable*) ht2->data;

    int ix = find(ht2, key, i);

    struct HashNode *temp = tdata[ix].node;

    if(ix == -1) { // nothing to delete
    } else {
        if(temp->key == key) {
            tdata[ix].node = NULL;
            return;
        } else {
            return;
        }
    }
}

