#ifndef NODES_H
#define NODES_H

#include <stdio.h>
#include <stdlib.h>

/* Constant defintions */

#define NUM_TYPE 1
#define STRING_TYPE 2
#define ARRAY_TYPE 3
#define BOOL_TYPE 4

/* ID STRUCTURE */

typedef struct id
{

    const char *idName; /* Holds the name of the id */
    char *value; /* Holds value associated to id name */
    int type; /* Holds the type of the value */

    int pos; /* Index of id */
    struct id *nextID; /* Pointer to next id */
    struct db *nextDB; /* Pointer to next db */

} ID;

/* DB STRUCT */

typedef struct db
{

    char *name; /* Name of database */
    ID *nextID; /* Pointer to next id */

} DB;

/* Generates a single id */
ID *generateID();

/* Generates linked ids and returns the first id */
ID *generateIDs(int num);

/* Gets a id at a certain index */
ID *getID(ID *start, int index);

/* Returns the length of a list of ids */
size_t getIDListLength(ID *start);

/* Removes a id at a certain index */
ID *deleteID(ID *start, int index);

/* Appends more ids to the end of the list */
ID *appendIDs(ID *start, int num);

/* Does a safe free() of a single ID as to prevent memory leaks */
void freeID(ID *t);

/* Does a safe free() of a single DB as to prevent memory leaks */
void freeDB(DB *t);

ID *generateID()
{
    ID *newone = (ID *) malloc(sizeof(ID));
    newone -> nextID = NULL;
    return newone;
}

ID *generateIDs(int num)
{
    ID *one = generateID();
    ID *cpy = one;

    int i;

    for (i = 0; i < num - 1; i++)
    {

        ID *next = generateID();
        cpy -> nextID = next;
        cpy -> pos = i;
        cpy = next;

    }

    cpy -> pos = i;
    cpy -> nextID = NULL;

    return one;
}

ID *appendIDs(ID *start, int num)
{
    int indexOfLast = getIDListLength(start) - 1;
    ID *last = getID(start, indexOfLast);
    last -> nextID = generateIDs(num);
}

ID *getID(ID *start, int index)
{
    int i;
    for (i = 0; i < index; i++)
    {
        start = start -> nextID;
    }
    return start;
}

size_t getIDListLength(ID *start)
{
    size_t i = 1;
    while (start -> nextID != NULL)
    {
        start = start -> nextID;
        i++;
    }
    return i;
}

ID *deleteID(ID *start, int index)
{
    if (index > 0)
    {
        ID *f = getID(start, index - 1);
        ID *l = getID(start, index + 1);
        ID *d = getID(start, index);
        f -> nextID = l;
        freeID(d);
        return start;
    }
    if (index == 0)
    {
        ID *up = start -> nextID;
        freeID(start);
        return up;
    }
    if (index + 1 == getIDListLength(start))
    {
        ID *r = getID(start, index);
        ID *c = getID(start, index - 1);
        c -> nextID = NULL;
        freeID(r);
        return start;
    }
}

void freeID(ID *t)
{
    free(t -> value);
    if (t -> nextDB)
        freeDB(t -> nextDB);
    free(t);
}

void freeDB(DB *t)
{
    ID *f = t -> nextID;
    ID *tmp;
    while (f != NULL)
    {
        tmp = f;
        f = f -> nextID;
        freeID(tmp);
    }
}

#endif /* NODES_H */