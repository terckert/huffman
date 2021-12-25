#include "huffman.h"


#define ENC 0
#define DEC 1 

#define SIZE 127

/* NODE DECLARATION AND CREATION */

struct HNODE
{
    struct HNODE *left, *right; // Node children
    char c;                     // Node character
    bool st;                    // True subtree, false character node
    int count;                  // Subtree number, character count
    int tnum;                   // Tree number
};

typedef struct HNODE node;      // Huffman tree node

/**
 * @brief Create a node object
 * 
 * @param c Character value
 * @param cnt Times character has appeared
 * @param tr Whether node is a subtree
 * @return node* 
 */
node* create_node(char c, int cnt, int tn, bool tr)
{
    node *temp = calloc(1, sizeof(node));
    temp->c = c;
    temp->count = cnt;
    temp->tnum = tn;
    temp->st = tr;
    temp->left = temp->right = NULL;
    return temp;
}

/**
 * @brief Node comparison function for sorting. Assumes ascending
 * order.
 * @param lhs Left hand side for comparison
 * @param rhs Right hand side for comparison
 * @return true When comparing two subtrees, compares subtree value. When two
 * character trees, compares count value; if counts are equal, subtrees on right
 * side, otherwise by alphabetical order.
 * @return false When none of the above are true.
 */
bool compare(node* lhs, node* rhs)
{
    if(lhs->st && rhs->st)
    {
        if(lhs->count != rhs->count)
            return lhs->count < rhs->count;
        else
            return lhs->tnum < rhs->tnum;
    }
    else if(lhs->count < rhs->count)
        return true;
    else if(lhs->count == rhs->count)
    {
        if (lhs->st)
            return false;
        else if (rhs->st)
            return true;
        else
            return lhs->c < rhs->c;
    }    
    else
        return false;
    
}

/* PRIVATE MEMBERS */
node *root;

FILE *file_s;           //unencode file
FILE *code_s;           //key for the file
FILE *msg_s;            //encoded file

/* Internal function declarations */

int _open_file(const char *file, const char *code, const char *msg, int flag);
void _close_file();
void _initial_sort(node** arr, int size);
void _fold(node **arr, int size);
void print_table();
void print_table_rec(char *s, node *curr);
/* External function defintions */

int encode(const char *infile, const char *code, const char *msg)
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
        arr[i] = create_node(i, 0, 0, false);
    }

    // Read from file into array to increment counts
    char c = ' ';
    while((fscanf(file_s, "%c", &c)) != EOF)
    {
        arr[(int)c]->count++;
    }

    // Sort array
    _initial_sort(arr, SIZE);

    // Fold array into one node.
    node *temp;
    int count = 0;
    int size = SIZE;
    while (arr[1] != NULL)
    {
        // Create subtree
        temp = create_node('^', (arr[0]->count + arr[1]->count), ++count, true);
        // Assign children
        temp->left = arr[0];
        temp->right = arr[1];
        // Reassign front of array
        arr[0] = temp;
        // Fold and sort array, decrement array size by 1
        _fold(arr, --size);
    }
    // Set tree root after fold
    root = arr[0];
    arr[0] = NULL;
    free(arr);

    print_table();

    _close_file();
    return 0;
}


int decode(const char *outfile, const char *code, const char *msg)
{
    if(!_open_file(outfile, code, msg, DEC))
    {
        fprintf(stderr, "Could not open files.");
        return 4;
    }

    _close_file();
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
int _open_file(const char *file, const char *code, const char *msg, int flag)
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

/**
 * @brief Closes file streams.
 * 
 */
void _close_file()
{
    fclose(file_s);
    fclose(code_s);
    fclose(msg_s);
}


void _initial_sort(node** arr, int size)
{
    node* temp = NULL;
    int smallest = 0;

    // Selection sort
    for(int i = 0; i < size - 1; i++)
    {
        smallest = i;
        for(int j = i+1; j < size; j++)
        {
            if(!compare(arr[smallest], arr[j]))
                smallest = j;
        }
        // Move array elements, if smallest is in correct spot do nothing
        if (smallest != i)
        {
            temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
        }
    }

}


void _fold(node **arr, int size)
{
    // Shift array left by one
    for(int i = 1; i < size; i++)
    {
        arr[i] = arr[i + 1];
    }
    // Assign NULL to last size element
    arr[size + 1] = NULL;
    // Resort array
    _initial_sort(arr, size);
}

void print_table()
{
    char *str = calloc(150, sizeof(char));
    print_table_rec(str, root);
}

void print_table_rec(char *s, node* curr)
{
    if(curr->left)
    {
        char *str = calloc(150, sizeof(char));
        strcat(str,s);
        strcat(str,"0");
        print_table_rec(str, curr->left);
        free(str);
    }
    if(!curr->st)
    {
        fprintf(code_s, "%c %s\n", curr->c, s);
    }
    if(curr->right)
    {
        char *str = calloc(150, sizeof(char));
        strcat(str,s);
        strcat(str,"1");
        print_table_rec(str, curr->right);
        free(str);
    }
}