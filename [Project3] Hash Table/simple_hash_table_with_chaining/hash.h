#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

/* TODO: Implement your own node and hash table if needed */
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    int size;
    struct HashNode *head; // pointing the first element of the list
    struct HashNode *tail; // pointint the last element of the list
} HashTable;

/* Support those below interfaces (used in main.c) */
HashTable* makeHashTable(int size);
void insertHashNode(HashTable* ht, int key, int value);
HashNode* findHashNode(HashTable* ht, int key);
void deleteHashNode(HashTable* ht, int key);

#endif /* __HASHTABLE_H__ */
