#ifndef NODES_H
#define NODES_H

#include <stdio.h>
#include <stdlib.h>
 
/* NODE STRUCTURE */
 
typedef struct node{
 
    char* thing;
    
    int pos; /* Index of node */
    struct node* next; /* Pointer to next node */
 
} NODE;
 
/* Generates a single node */ 
NODE* generateNode();
 
/* Generates linked nodes and returns the first node */
NODE* generateNodes(int num);
 
/* Gets a node at a certain index */
NODE* getNode(NODE* start, int index);
 
/* Returns the length of a list of nodes */
size_t getNodeListLength(NODE* start);
 
NODE* generateNode()
{
    return (NODE*) malloc(sizeof(NODE));
}
 
NODE* generateNodes(int num)
{
    NODE* one = generateNode();
    NODE* cpy = one;
    
    int i;
    
    for(i = 0; i < num - 1; i++){
 
        NODE* next = generateNode();
        cpy -> next = next;
        cpy -> pos = i;
        cpy = next;
 
    }
 
    cpy -> pos = i;
    cpy -> next = NULL;
 
    return one;
}
 
NODE* getNode(NODE* start, int index)
{
    int i;
    for(i = 0; i < index; i++){
        start = start -> next;
    }
    return start;
}
 
size_t getNodeListLength(NODE* start)
{
    size_t i;
    while(start -> next != NULL){
        start = start -> next;
        i++;
    }
    return i - 1;
}

#endif /* NODES_H */
