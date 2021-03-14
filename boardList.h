#include "board.h"

typedef struct nodeList NLIST;
typedef struct nodeEntry NENTRY;

// Double linked list
struct nodeList {
    int length;
    NENTRY *first;
    NENTRY *last;
};

// Node of double linked list
struct nodeEntry {
    NLIST *list;
    CURBOARD *board; 
    NENTRY *next;
    NENTRY *prev;
};

// Create new node entry
NENTRY *newNodeEntry(CURBOARD *s);

// Delete an existing node entry
void deleteNodeEntry(NENTRY *e);

// Create a new node list
NLIST *newNodeList(void);

// Append new board move to end of list
void addNode(NLIST *l, CURBOARD *s);

// Delete a node list and all its entries
void deleteNodeList(NLIST *l);
