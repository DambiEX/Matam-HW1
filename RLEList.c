/*
 * TODO: code conventions: add {} after EVERY if and and while.
 * TODO: code conventions: make helper functions static? maybe remove Node.h. may take a while.
 */


#include "RLEList.h"
#include "Node.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct node {
    char symbol;
    int repetitions;
    struct node *next;
};

struct RLEList_t { // holds the first node of a chain
    Node first_node;
    int size;
};

Node NodeCreate(char input) {
    Node node = malloc(sizeof(*node));
    if (!node)
    {
        return NULL;
    }
    node->next = NULL;
    node->symbol = input;
    node->repetitions = 1;
    return node;
}

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    if (!list)
    {
        return NULL; //requested error value is NULL
    }
    list->first_node = NodeCreate(EMPTY);
    if (!list->first_node)
    {
        return NULL;
    }
    list->size = 0;
    return list;
}

void RLEListDestroy(RLEList list) {
    if (!list)
    {
        return;
    }
    Node head = list->first_node;
    Node temp;
    while (head->next) {
        temp = head->next;
        free(head);
        head = temp;
    }
    free(head);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char input) {
    if (!list || !input)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    Node last_node = list->first_node;
    while (last_node->next) {
        last_node = last_node->next;
    }

    if (input == last_node->symbol)
    {
        last_node->repetitions++;
    }
    else {
        Node new_node = NodeCreate(input);
        if (!new_node)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        last_node->next = new_node;
    }

    list->size++;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if (!list)
    {
        return NULL_POINTER_ERROR;
    }
    return list->size;
}

RLEListResult NodeCutOff(Node node) {
    if (node->next == NULL)
    {
        return RLE_LIST_ERROR;
    }
    if (node->next->next) //if C exists
    {
        node->next = node->next->next; //A->B --> A->C
    }
    else
    {
        node->next = NULL; // A->NULL
    }
    free(node->next); // B --> NULL
    return RLE_LIST_SUCCESS;
}

Node FindNode(RLEList list, int index) {
    Node node = list->first_node;
    int depth = 0;
    while (node->next->repetitions + depth < index) { // while (sum this far) < index
        // for example: index=0, repetitions=1, depth=0: stops looping
        depth += node->next->repetitions;
        node = node->next;
    }
    return node;
}

RLEListResult RLEListCheckArguments(RLEList list, int index) {
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index >= list->size) // for example: index=0, size=1 is ok. but index=1 size=1 is not ok.
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else
    {
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListRemove(RLEList list, int index) {
    RLEListResult check = RLEListCheckArguments(list, index);
    if (check != RLE_LIST_SUCCESS)
    {
        return check;
    }

    Node node;
    if (index == 0)
    {
        node = list->first_node;
    }
    else
    {
        node = FindNode(list, index - 1); // the node BEFORE the one containing the indexed char
    }

    if (node->repetitions > 1) //if the indexed char is in this node
    {
        node->repetitions--;
    }
    else if (node->next->repetitions > 1) //next node is big
    {
        node->next->repetitions--;
    }
    else if (NodeCutOff(node) == RLE_LIST_ERROR) //next node is size 1
        {
            return RLE_LIST_ERROR;
        }



    list->size--;
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    RLEListResult check = RLEListCheckArguments(list, index);
    if (result)
    {
        *result = check;
    }
    if (check != RLE_LIST_SUCCESS) {
        return CANT_GET;
    }

    Node node = FindNode(list, index);
    return node->symbol;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    Node node = list->first_node;
    while (node->next){
        node->next->symbol = map_function(node->next->symbol);
        node = node->next;
    }
    //node->symbol=map_function(node->symbol);
    return RLE_LIST_SUCCESS;
}

int nodes_amount(RLEList list) {
    Node node = list->first_node;
    int counter = 0;
    while (node->next) {
        counter++;
        node = node->next;
    }
    return counter;
}

int repetitions_amount_of_digits(Node node) {
    int reps = node->repetitions;
    int counter = 0;
    while (reps != 0) {
        reps = reps / 10;
        counter++;
    }
    return counter; //don't know if it will work
}

int total_amount_of_digits(RLEList list) {
    Node node = list->first_node;
    int counter = 0;
    while (node->next) {
        counter += repetitions_amount_of_digits(node);
        node = node->next;
    }
    return counter;
}


char digit_by_index(int repetitions, int index) {
    repetitions = repetitions / (int)(pow(10,index));
    int counter = 0;
    while (repetitions % 10) {
        repetitions--;
        counter++;
    }
    return (char) counter;
}

char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (!list) {
        if (result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    Node node = list->first_node;
    int size = nodes_amount(list);
    char *export = malloc((sizeof(char) * size) + total_amount_of_digits(list) + 1);
    if (!export) {
        return NULL;
    }
    int j = 0;
    while (node->next){
        int i=0;
        char *repetitions= malloc(sizeof(char) * repetitions_amount_of_digits(node));
        if (!repetitions)
            return NULL;
        export[j++] = node->symbol;
        //for example: if node->repetitions=4621, the loop will run 4 times, each time entering the next digit into the string
        while (repetitions[i]) {
            export[j++] = digit_by_index(node->repetitions, i);
            i++;
        }
        free(repetitions);
        export[j++] = '\n';
        node = node->next;
    }
    *result = RLE_LIST_SUCCESS;
    export[size*STRING_LENGTH-1] = EMPTY; //TODO: maybe this line is not needed, maybe wrong index.
    return export;
}

/*
char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (!list) {
        if (result)
            *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    Node node = list->first_node;
    int size = nodes_amount(list);
    char *export = malloc((sizeof(char) * size) + total_amount_of_digits(list) + 1);
    if (!export)
        return NULL;
    export[0]='\0';
    while (node->next){
        sprintf(export+strlen(export),"%c%d\n",node->symbol, node->repetitions);
        node=node->next;
    }
    *result = RLE_LIST_SUCCESS;
    return export;
}
*/

RLEListResult RLEListPrintContent(RLEList list, FILE *destination) {
    if (!list || !destination)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    Node node = list->first_node;
    while (node->next){
        for (int i = 0; i < node->next->repetitions; ++i) {
            fprintf(destination, "%c", node->next->symbol);
        }
        node = node->next;
    }
    return RLE_LIST_SUCCESS;
}
