
// Introduction to Algorithm class assignment 3
// perfect hash
// Name : HyungKwon Ko
// Student # : 2014018940

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int size;
struct HashTable *ht_temp;

int find(struct HashNode *ll, int key) { // this finds the index of the value for the given key in the linked list
    int retval = 0;
    struct HashNode *temp = ll; //copy the linked list
    while(temp != NULL) { // run if the temp is not empty
        if(temp->key == key) {
            return retval;
        }
        temp = temp->next; // move to the next spot
        retval++; // index = index + 1
    }
    return -1; // if temp is empty, return -1
}

struct HashNode* get_val(struct HashNode *ll, int find_index) { // get the value at given index
    int i = 0;
    struct HashNode *temp = ll;
    while(i != find_index) { // until i == find_index
        temp = temp->next; // move the pointer
        i++;
    }
    return temp;
}


HashTable* makeHashTable(int size) {
    int i;
    ht_temp = (struct HashTable*) malloc(size * sizeof(struct HashTable*));
    ht_temp->size = size/3;
    // initializing the hash table with NULL
    for(i=0; i<ht_temp->size; i++) {
        ht_temp[i].head = NULL;
        ht_temp[i].tail = NULL;
    }
    printf("Hash Table made!\n");
    return ht_temp;
}

void insertHashNode(HashTable* ht, int key, int value) {
    int i = key % ht->size; // simple hash function
    struct HashNode *new_ll = (struct HashNode*) ht[i].head;
    struct HashNode *new_hn = (struct HashNode*) malloc(sizeof(struct HashNode));
    new_hn->key = key;
    new_hn->value = value;
    new_hn->next = NULL;

    if(new_ll == NULL) {
        ht[i].head = new_hn; // allocate the same element to head and tail
        ht[i].tail = new_hn;
    } else {
        int find_index = find(new_ll, key);
        if(find_index == -1) { // key is not found in the list
            ht[i].tail->next = new_hn;
            ht[i].tail = new_hn;
        } else { // key already exists
            struct HashNode *element = get_val(new_ll, find_index);
            element->value = value;
        }
    }
}

HashNode* findHashNode(HashTable* ht, int key) {
    int i = key % ht->size;
    struct HashNode *ll = (struct HashNode*) ht[i].head;
   
    if(ll == NULL) {
        return NULL; // no element => return NULL
    } else {
        int find_index = find(ll, key);
        if(find_index == -1) {
            return NULL; // no index found == no element => return NULL
        } else {
            struct HashNode *element = get_val(ll, find_index); //find the given element
            return element; // return it
        }
    }
}

void deleteHashNode(HashTable* ht, int key) {
    int i = key % ht->size;
    struct HashNode *ll = (struct HashNode*) ht[i].head;

    if(ll == NULL) { // if ll ==NULL, nothing to delete
        //printf("key doesn't exist\n"); // for checking
    } else {
        int find_index = find(ll, key); // using find function made above
        if(find_index == -1) { // if find_index == NULL, nothing to delete
            //printf("key doesn't exist\n");
        } else {
            struct HashNode *temp = ll;
            if(temp->key == key) { // if we find the element, delete it
                ht[i].head = temp->next;
                //printf("key removed\n");
                return;
            }
            while(temp->next->key != key) { // move until we find it
                temp = temp->next;
            }
            if(ht[i].tail == temp->next) {
                temp->next = NULL;
                ht[i].tail = temp; // make it NULL
            } else {
                temp->next = temp->next->next;
            }
            //printf("key removed\n");
        }
    }

}
