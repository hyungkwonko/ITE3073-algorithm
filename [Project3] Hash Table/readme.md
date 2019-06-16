## Project3

I coded the simple hash with linear probing and the perfect hash. I also coded the simple hash with chaining.

<br>

## Simple Hash Code
First, in simple hash code, there are four functions which are makeHashTable, insertHashNode, findHashNode, deleteHashNode. Each one works as its name implies.

<br>

1. makeHashTable: I initialized the hash table with null and 0 values. There are two variables, data and flag. Data consists of key and value. Flag is to check the status of the given space. Flag can have 0, 1, 2. 0 means there have been no data. 1 means there are data right now. 2 means there was data before (but now it is empty).
2. insertHashNode: with given key and value, inserts the value in the empty spot. If the spot is not empty, find the next spot using linear probing. Hash function is the simple modulo function which is key % size of list
3. findHashNode: find the hash node. Run while it is empty(flag == 0). Allocate another hash value(move one step to the right which is just +1) if the key is different at given space.
4. deleteHashNode: run while it is empty. If the key matches, delete the value. If there is no such key exists, simply return NULL.

<br>

## Perfect Hash Code
Second in perfect hash code, there are 5 functions which are find, makeHashTable, insertHashNode, findHashNode, deleteHashNode.

1. find: find the index of the given second list where the key matches. Escape the loop when it runs one cycle with ix=-1.
2. makeHashTable: there are two variables size, HashTable and HashNode. We need to initialize it with each size and NULL value.
3. insertHashNode: we use simple hash function like above. If the second list is empty, put it in the spot with the index that second hash function mades. If there already exists a value, we perform the hash function for another index.
4. findHashNode: if the second list is empty, return NULL, if it is not, search it using the second hash function. If there is no such key matches, return NULL. Else, return the value.
5. deleteHashNode: use the same hash function. Find the index of the second list where the key matches and then delete the value.

<br>

## Analysis

- Simple Hash with linear probing small input took 0.000017 seconds.
- Simple Hash with linear probing large input took 0.188477 seconds. 

- Perfect Hash with small input took 0.000016 seconds.
- Perfect Hash with large input took 0.012809 seconds.

- Simple Hash with Chaining small input took 0.000009 seconds.
- Simple Hash with Chaining large input took 0.005359 seconds. 

By this result, we can find that the outcome is accordance with what we have learned. Perfect hash is faster than simple hash with linear probing. It seems like the power of using it will be compelling as the size of the input grows. But the chaining was more powerful than perfect hash in my case.
