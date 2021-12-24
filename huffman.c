#include "huffman.h"


#define ENC 0
#define DEC 1 

#define SIZE 127

/* NODE DECLARATION AND CREATION */
struct HNODE
{
    struct HNODE *left, *right;
    char c;
    bool st;
    int count;
};


typedef struct HNODE node;

node* create_node(char c, int cnt, bool tr)
{
    node *temp = calloc(1, sizeof(node));
    temp->c = c;
    temp->count = 0;
    temp->st = tr;
    temp->left = temp->right = NULL;
    return temp;
}

/* PRIVATE MEMBERS */
node *root;

FILE *file_s;           //unencode file
FILE *code_s;           //key for the file
FILE *msg_s;            //encoded file

/* Internal function declarations */

int _open_file(char *file, char *code, char *msg, int flag);

/* External function defintions */

int encode(char *infile, char *code, char *msg)
{
    // Open files for read and write. Return error on failure
    if(!_open_file(infile, code, msg, ENC))
    {
        fprintf(stderr, "Could not open files.");
        return 4;
    }
    
    // Node array to store characters for read in and insertion
    node **arr = calloc(SIZE, sizeof(node*));   

    // Assign character value to nodes.
    for(int i = 0; i < SIZE; i++)
    {
        arr[i] = create_node(i, 0, false);
    }

    return 0;
}


int decode(char *outfile, char *code, char *msg)
{
    if(!_open_file(outfile, code, msg, DEC))
    {
        fprintf(stderr, "Could not open files.");
        return 4;
    }
    return 0;
}

/* Internal function definitions */

/**
 * @brief Opens files in needed state for operation
 * 
 * @param file unencoded file
 * @param code cipher
 * @param msg encoded file
 * @param flag tells how to open file
 * @return 0 if failed to open
 * @return 1 if opened successfully 
 */
int _open_file(char *file, char *code, char *msg, int flag)
{
    if (flag == ENC)
    {
        file_s = fopen(file, "r");
        code_s = fopen(code, "w");
        msg_s = fopen(msg, "w");
    }
    else
    {
        file_s = fopen(file, "w");
        code_s = fopen(code, "r");
        msg_s = fopen(msg, "r");
    }
    return (file_s != NULL && code_s != NULL && msg_s != NULL);
}