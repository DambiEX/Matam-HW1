//TODO: figure out if some "->" need to be replaced by "."

#include "RLEList.h"
#include <stdlib.h>
#define NULL_POINTER_ERROR -1

typedef struct node{
    char data;
    int repeats;
    struct node* next;
} *Node;

struct RLEList_t{
    Node first_node;
    int size;
};

Node NodeCreate(char value){
    Node node = malloc(sizeof(*node));
    if (!node)
        return NULL;
    node->next = NULL;
    node->data = value;
    node->repeats = 1;
    return node;
}

RLEList RLEListCreate(){
    RLEList list = malloc(sizeof(*list));
    if (!list)
        return NULL;
    list->first_node = NodeCreate('\0');
    if (!list->first_node)
        return NULL;
    list->size = 0;
    return list;
}

void NodesRecursiveDestroy(Node node){
    if (node->next)
        NodesRecursiveDestroy(node->next);
    free(node);
}

void RLEListDestroy(RLEList list){
    if (!list)
        return;
    if (list->first_node)
        NodesRecursiveDestroy(list->first_node);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value){
    if (!list || !value)
        return RLE_LIST_NULL_ARGUMENT;

    Node last_node = list->first_node;
    while (last_node->next){
        last_node = last_node->next;
    }

    if (value == last_node->data){
        last_node->repeats++;
    }

    else{
    Node new_node = NodeCreate(value);
    if (!new_node)
        return RLE_LIST_OUT_OF_MEMORY;
    last_node->next = new_node;
    }

    list->size++;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    if (!list)
        return NULL_POINTER_ERROR;
    return list->size;
}

void NodeSever(Node node){
    /*
     * "Sever" means "Cut"
     * disconnects the node AFTER the given argument.
     * given the list is nodes ABC and A is an argument: A->B->C --> A->C
     */
    if (node->next->next) //if C exists
        node->next = node->next->next; //A->B --> A->C
    free(node->next); // B --> NULL
}

Node FindNode(RLEList list, int index){
    /*
     * returns the node that holds the character with the index.
     * example: given: (list = [A10,B10,C10], index = 15), returns B. if index>=20 returns C.
     * is used in: RLEListRemove, RLEListGet.
     */
    Node node = list->first_node;
    int depth = 0;
    while (node->next->repeats + depth < index){ // while (sum this far) < index
        // for example: index=0, repeats=1, depth=0: stops looping
        depth += node->next->repeats;
        node = node->next;
    }
    return node;
}

RLEListResult RLEListCheckArguments(RLEList list, int index){
    if (!list || !index)
        return RLE_LIST_NULL_ARGUMENT;
    if (index >= list->size) // for example: index=0, size=1 is ok. but index=1 size=1 is not ok.
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    else
        return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index){
    RLEListResult check = RLEListCheckArguments(list, index);
    if (check != RLE_LIST_SUCCESS)
        return check;

    Node node = FindNode(list, index);
    if (node->next->repeats < 2)
        NodeSever(node);
    else
        node->next->repeats--;

    list->size--;
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    RLEListResult check = RLEListCheckArguments(list, index);
    if (result)
        *result = check;
    if (check != RLE_LIST_SUCCESS)
    {
        return 0;
    }

    Node node = FindNode(list, index);
    return node->data;
}
