//
// Created by PC on 25/4/2022.
//

#ifndef RLELIST_C_ASCIIARTTOOL_H
#define RLELIST_C_ASCIIARTTOOL_H

/**
 * Handles opening a file and errors that can happen while opening.
 *
 * @param source - The original file to be opened.
 * @param destination - The file pointer where the opened file will be.
 * @param flag - READ or WRITE.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
 *  RLE_LIST_ERROR if failed opening the file.
 *  RLE_LIST_SUCCESS if opened the file successfully.
 */
RLEListResult OpenFile (FILE* source, FILE** destination, char flag);

/**
 * Receives a text file and compresses it into an RLE List.
 *
 * @param in_stream - Input FILE* object.
 * @return
 *  An RLEList object containing the text in the file.
 */
RLEList asciiArtRead(FILE* in_stream);

/**
 * Writes the content of a RLEList object to a file.
 *
 * @param list - An RLEList object to be read from.
 * @param out_stream - a FILE* object to receive the unpacked content of the list.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
 *  RLE_LIST_ERROR if failed opening the file.
 *  RLE_LIST_SUCCESS if printed to the file successfully.
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 * Writes an RLEList object to a file in compressed form.
 *
 * @param list - the list to be written into the file.
 * @param out_stream - the file to be written into.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL
 *  RLE_LIST_SUCCESS if written to the file successfully
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

/**
 * Inverts a Node's symbol, changing its whole content at once.
 *
 * @param symbol - a Node's symbol
 * @return
 *  ' ' if the input is '@'
 *  '@' if the input is ' '
 */
char InvertChar(char symbol);

#endif //RLELIST_C_ASCIIARTTOOL_H
