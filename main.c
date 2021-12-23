#include <stdio.h>
#include <string.h>

//#include "huffman.h"

#define SUCCESS 0
#define NOT_ENOUGH_ARGS 1
#define INVALID_COMMAND 2
#define INVALID_FILE_EXT 3

void _help();
int _print_error();
int _enough_param(int n);

int main(int argc, char const *argv[])
{
    if (argc < 2)
        return _print_error(NOT_ENOUGH_ARGS);
    
    int err_msg;

    if(!strcmp(argv[1], "-help"))
        _help();
    else if(!strcmp(argv[1], "-decode"))
    {
        if(!_enough_param)
            err_msg = NOT_ENOUGH_ARGS;

    }
    else if(!strcmp(argv[1], "-encode"))
    {
        
    }
    else
        err_msg = INVALID_COMMAND;
    
    if(err_msg)
        return _print_error(err_msg);

    return SUCCESS;
}

void _help()
{
    printf("Applies simple Huffman encoding and decoding to files.\n");
    printf("Note that [cipher] and [encmsg] must be .txt files and\n");
    printf("name must include .txt extension. [unencfile] and\n");
    printf("need to specify the necessary extension as part of \n");
    printf("their file name.\n\n");
    printf("Commands:\n\t-encode\n\t-decode\n\t-help\n\n");
    printf("Encode: huffman -encode [unencfile] [cipher] [encmsg]\n");
    printf("Encodes text in [unencfile], create cipher and stores\n");
    printf("in [cipher].txt file. Encodes message in [encmsg].txt\n\n");
    printf("Decode: huffman -decode [decodefile] [cipher] [encmsg]\n");
    printf("Decodes message in [encmsg].txt using the [cipher]\n");
    printf("[cipher].txt file and stores in [decodefile]\n\n");
    printf("Help: huffman -help\n");
    printf("Prints the help menu.\n");
}

int _print_error(int e)
{
    fprintf(stderr,"Invalid command. Please use ./huffman -help to\n");
    fprintf(stderr,"get proper usage.\n");
    return e;
}

int _enough_param(int n)
{
    return(n >=2 && n <=5);
}