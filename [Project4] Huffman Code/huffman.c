
// Introduction to Algorithm class assignment 4
// huffman coding
// Name : HyungKwon Ko
// Student # : 2014018940

#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// allocate encoded value
// work recursively to cover all the nodes in the list
void traverse(struct huffman_node *root, char code[], int cp, char *code_map[], int code_size_map[]) {
    // checkpoint
    assert(cp <= 256);
    if(root->left == NULL) {
        // another checkpoint
        assert(root->right == NULL);
        // dynamic allocation
        code_map[root->c] = (char*)malloc(sizeof(char)*((cp-1)/8+1));
        code_size_map[root->c] = cp;
        // memory copy
        memcpy(code_map[root->c], code, ((cp-1)/8+1));
        // printout coded character
        printf("%c: ", root->c);
        for(int i=0; i<cp; i++) {
            // printout (i)th bit in code
            printf("%d", GET_BIT(code, i));
        }
        printf("\n");
        return;
    }
    assert(root->right != NULL);
    // reset (cp)th bit in code
    RESET_BIT(code, cp);
    // go down to the list and do it recursively
    traverse(root->left, code, cp+1, code_map, code_size_map);
    // set (cp)th bit in code
    SET_BIT(code, cp);
    // the same process
    traverse(root->right, code, cp+1, code_map, code_size_map);
}

/**
  Encode string to bit array using huffman coding algorithm

  @param[in]	src				Source raw string
  @param[in]	src_byte_size	Length of source string, in bytes
  @param[out]	dst_tree		Root node of huffman tree
  @param[out]	dst				Destination encoded bit array
  @return Length of encoded bit array, in bits (e.g. 0100 => 4)
*/
int encode_huffman(char *src, int src_byte_size,
		struct huffman_node **dst_tree, char *dst){
	// TODO: Implement Me
    // will consider 256 character that can be expresses by ASCII code
    struct huffman_node *node_map[256] = {NULL, };
    // max = 256 like above
    struct huffman_node *nodes[256];
    int code_size_map[256] = {0, };
    char *code_map[256] = {NULL, };
    int cnt_node = 0; // this will count the number of unique chars in the string
    int chosen = 0;
    // buffer is set as 32 to cover 32 bit long binary system
    char buf[32];
    int dst_bit_size = 0;
    for(int i=0; i<src_byte_size; i++) {
        //checkpoint
        assert(src[i] >= 0 && src[i] < 256);
        // use list instead of min heap
        if(node_map[src[i]] == NULL) {
            node_map[src[i]] = (struct huffman_node*) malloc(sizeof(struct huffman_node));
            node_map[src[i]]->left = node_map[src[i]]->right = NULL;
            // put character into the list1 one by one
            node_map[src[i]]->c = src[i];
            // initialize frequency with 0
            node_map[src[i]]->freq = 0;
            // (x=num of unique chars) many storage will be used
            nodes[cnt_node++] = node_map[src[i]];
            //printf("node_map[src[i]]->c: %c\n", node_map[src[i]]->c);
            //printf("src[i]: %d\n", src[i]);
            //printf("%s\n", src);
        }
        // ramp up frequency as it appears
        node_map[src[i]]->freq++;
    }
    // another checkpoint
    assert(cnt_node <= 256);

    // make huffman structure
    for(int i=0; i<cnt_node-1; i++) { // run cnt_node-1 times
        // two node will be merged into one with summed frequency
        struct huffman_node *first = NULL;
        struct huffman_node *second = NULL;
        for (int j=0; j<cnt_node; j++) {
            if(nodes[j] != NULL) {
                if(first == NULL || first->freq > nodes[j]->freq){
                    first = nodes[j];
                    chosen = j;
                }
            }
        }
        // erase the chosen node
        nodes[chosen] = NULL;
        // do the same process like above
        for (int j=0; j<cnt_node; j++) {
            if(nodes[j] != NULL) {
                if(second == NULL || second->freq > nodes[j]->freq) {
                    second = nodes[j];
                    chosen = j;
                }
            }
        }
        nodes[chosen] = (struct huffman_node *)malloc(sizeof(struct huffman_node));
        nodes[chosen]->c = '\0'; // this is not important
        nodes[chosen]->freq = first->freq + second->freq; // summed freq
        nodes[chosen]->left = first; // left node(huffman structure)
        nodes[chosen]->right = second; // right node
    }
    // now we allocate the encoded value
    traverse(nodes[chosen], buf, 0, code_map, code_size_map);
    *dst_tree = nodes[chosen];
    // run (src_byte_size=total length of string) times
    for(int i=0; i<src_byte_size; i++) {
        for(int j=0; j<code_size_map[src[i]]; j++) { // 
            if(GET_BIT(code_map[src[i]], j)) {
                SET_BIT(dst, dst_bit_size);
            } else {
                RESET_BIT(dst, dst_bit_size);
            }
            dst_bit_size++; // count the size of the encoded data
        }
    }
    return dst_bit_size; // return to check the efficiency    
}

/**
  Decode bit array to string using huffman coding algorithm

  @param[in]	src				Source bit array
  @param[in]	src_bit_size	Length of bit array, in bits
  @param[in]	dst_tree		Root node of huffman tree
  @param[out]	dst				Destination string
  @return Length of decoded string, in bytes
*/
int decode_huffman(char *src, int src_bit_size,
		struct huffman_node *dst_tree, char *dst){
	// TODO: Implement Me
    int dst_size = 0;
    struct huffman_node *node = dst_tree;
    // run it as long as the size of the encoded bit array
    for(int i=0; i<src_bit_size; i++) {
        if(node->left == NULL) {
            dst[dst_size++] = node->c;
            node = dst_tree;
        }
        if(GET_BIT(src,i) == 0) { // work if it is 0
            node = node->left; // go to the left node
        } else { // work if it is 1(else)
            node = node->right; // go to the right node
        }
    }
    dst[dst_size++] = node->c;
    return dst_size; // return to check the efficiency
}
