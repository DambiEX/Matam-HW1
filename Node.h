//
// Created by PC on 21/4/2022.
//

#ifndef MAIN_C_NODE_H
#define MAIN_C_NODE_H

#include "RLEList.h"

#define NULL_POINTER_ERROR -1
#define EMPTY '\0'
#define CANT_GET 0
#define SYMBOL_AND_NEW_LINE 2
#define ERROR_MARGIN 255

typedef struct node *Node;

/**
 * NodeCreate: Allocates memory for a new Node.
 *
 * a Node holds the input and the number of repetitions of a character.
 *
 * Note that the user needs to free the memory after usage, with the RLEListDestroy
 * or NodeCutOff functions.
 *
 * @param input - the symbol to be stored in the Node.
 * @return
 * 	NULL if allocations failed.
 * 	A new Node in case of success.
 */
Node NodeCreate(char input);

/**
 * FindNode: Finds the node containing the correct list index.
 *
 * receives a list and an ---appropriate--- index shorter than list size.
 * returns the node that holds the character with the index.
 * example: given: (list = [A10,B10,C10], index = 15), returns B. if index>=20 returns C.
 * is used in: RLEListRemove, RLEListGet.
 *
 * @param list - the RLE list containing the index
 * @param index - the index of the character to be retrieved.
 * @return
 *  The Node in the correct place in the list.
 */
Node FindNode(RLEList list, int index);

/**
 * NodeCutOff: Removes a single node from the chain
 *
 * Receives a node with AT LEAST 1 following node. Otherwise returns error.
 * Disconnects the node AFTER the given argument.
 * Given the list is nodes ABC and A is an argument: A->B->C --> A->C
 *
 * @param node - the Node ---before--- the Node that gets removed.
 */
RLEListResult NodeCutOff(Node node);

/**
 * RLEListCheckArguments: checks if valid parameters were given to a function.
 *
 * @param list - an RLE list.
 * @param index - an index to a character within the list.
 * @return
 *	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 * 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
 * 	RLE_LIST_SUCCESS if a valid index was requested.
 */
RLEListResult RLEListCheckArguments(RLEList list, int index);

/**
 * Unpacks the RLEList and prints it as a regular picture. un-encoded.
 *
 * @param list - RLEList object containing the symbols to be printed.
 * @param destination - *FILE object to receive the printed string.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 *  RLE_LIST_SUCCESS otherwise.
 */
RLEListResult RLEListPrintContent(RLEList list, FILE* destination);

#endif //MAIN_C_NODE_H
