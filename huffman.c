#include "huffman.h"



struct HNODE
{
    struct NODE *left, *right;
    char c;
    int count;
};


typedef struct hNode node;

void encode(char *infile, char *code, char *msg);


void decode(char *outfile, char *code, char *msg);


void 