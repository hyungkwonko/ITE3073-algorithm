
// Introduction to Algorithm class assignment 4
// huffman coding
// Name: HyungKwon Ko
// Student #: 2014018940


#ifndef __huffman_h__
#define __huffman_h__

struct huffman_node{
	// TODO: Implement me
    char c;
    int freq;
    struct huffman_node* left;
    struct huffman_node* right;
};

/**
  Bit manipulation macros.
*/
// Get y-th bit in the buffer pointed by x
#define GET_BIT(x, y) (((x)[(y)/8] & (1 << (7 - ((y)%8)))) != 0)
// Set y-th bit in the buffer pointed by x
#define SET_BIT(x, y) do{\
	(x)[(y)/8] |= (1 << (7 - ((y)%8)));\
}while(0)
// Reset y-th bit in the buffer pointed by x
#define RESET_BIT(x, y) do{\
	(x)[(y)/8] &= (~(1 << (7 - ((y)%8))));\
}while(0)

int encode_huffman(char *src, int src_byte_size, struct huffman_node **dst_tree, char *dst);
int decode_huffman(char *src, int src_bit_size, struct huffman_node *dst_tree, char *dst);
#endif /* __huffman_h__ */
