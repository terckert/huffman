#ifndef HUFFMAN_H_
#define HUFFMAN_H_

/**
 * @brief Encodes a given file. Provides the huffman en-
 * code key and encoded message to user.
 * @param infile Filename containing initial messsage
 * @param code Huffman code based on characters in file
 * @param msg Encoded message
 */
void encode(char *infile, char *code, char *msg);

/**
 * @brief Decodes a file using the provided code and saves
 * it to the specified file.
 * @param code Name of the file containing the huffman code
 * @param msg Encoded message
 * @param outfile File to save the code into
 */
void decode(char *code, char *msg, char *outfile);


#endif /* HUFFMAN_H_ */