#include "boardList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create a new node entry
static NENTRY *newNodeEntry(CURBOARD *s)
{
    NENTRY = *e;
    e = malloc(sizeof(NENTRY));
    if (!e)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    e->list = NULL;
    e->next = NULL;
    e->prev = NULL;
    e->board = s;
    return e;
}

// delete a node entry
void deleteNodeEntry(NENTRY *e)
{
    CURBOARD *s;
    s = e->board;
    free(s);
    return s;
}

// create a new node list
NLIST *newNodeList(void)
{
    NLIST *l;
    l = malloc(sizeof(NLIST));
    if (!l)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    l->length = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

// append new board move to end of list
void addNode(NLIST *l, CURBOARD *s) 
{
    NENTRY *e = NULL;
    e = newNodeEntry(s);
    if (l->last)
    {
        e->list = l;
        e->next = NULL;
        e->prev = l->last;
        l->last->next = e;
        l->last = e;
    }
    else
    {
        e->list = l;
        e->next = NULL;
        e->prev = NULL;
        l->first = e;
        l->last = e;
    }
    l->length++;
}

// delete a node list and all its entries
void deleteNodeList(NLIST *l)
{
    NENTRY *e, *n;
    CURBOARD *s;
    e = l->first;
    while (e)
    {
        n = e->next;
        s = deleteNodeEntry(e);
        deleteBoard(s);
        e = n;
    }
    free(l);
}
