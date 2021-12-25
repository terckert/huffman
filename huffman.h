#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Encodes a given file. Provides the huffman en-
 * code key and encoded message to user. Returns 0 on
 * @param infile Filename containing initial messsage
 * @param code Huffman code based on characters in file
 * @param msg Encoded message
 * @return 0 on success
 * @return 4 on failure, could not open file
 */
int encode(const char *infile, const char *code, const char *msg);

/**
 * @brief Decodes a file using the provided code and saves
 * it to the specified file.
 * @param code Name of the file containing the huffman code
 * @param msg Encoded message
 * @param outfile File to save the code into
 * @return 0 on success
 */
int decode(const char *code, const char *msg, const char *outfile);


#endif /* HUFFMAN_H_ */