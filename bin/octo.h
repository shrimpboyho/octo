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
#ifndef OCTO_H
#define OCTO_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

size_t len(char* string){

	char *end = string;
	for(;*end;++end){}
	return (size_t) (end-string);

}

char* makeCopy(char* s){
	
	char* buff = (char*) malloc(len(s) + 1);
	strcpy(buff, s);
	return buff;
}

void* lstrip(char* string){

	if(!string) 
		return string;

	/* Trim off leading whitespace */
	while(isspace(*string)){
		string++;
	}

	return string;

}

void* rstrip(char* string){
	
	/* Trim off trailing whitespace */
	char* end = string + len(string) - 1;
        while (end >= string && isspace(*end))
                end--;
        *(end + 1) = '\0';
	
	return string;

}

void* strip(char* string){

	/* Trim off both leading and trailing whitespace */
	char* lstring = lstrip(string);
	char* finalString = rstrip(lstring);
	
	return finalString;

}

char* slice(char* s, int start, int end, int BYTES){

	/* Create a new identical buffer */
	char* buff = (char*) malloc((end - start) + 2 + BYTES);
	strncpy(buff, s + start, (end - start) + 1);
	*(buff + (end - start) + 1) = '\0';
	return buff;
}

char* toUpperCase(char* s){
	
	char* q = makeCopy(s);
	int i;
	for(i = 0; i < len(q); i++){
		*(q + i) = toupper(*(q + i));
	}

	return q;

}

char* toLowerCase(char* s){

	char* q = makeCopy(s);
	int i;
	for(i = 0; i < len(q); i++){
		*(q + i) = tolower(*(q + i));
	}

	return q;

}

char* intToString(int n){

	int c = (int) log10((double)n) + 1;
	char* b = (char*) malloc(c + 1);
	sprintf(b,"%d",n);
	
	return b;
    
}

int stringToInt(char* s){

	return atoi(s);
	
}

char charAt(char* s, int n){
	
	return *(s + n);
	
}

char* replaceBetween(char* s, int start, int end, char* what){

	char* buffer = malloc(len(s) + len(what));
	*(buffer) = '\0';	
	char* part = slice(s, 0, start - 1, 0);
	strcat(buffer,part);
	strcat(buffer,what);
	char* part2 = slice(s, end, len(s) - 1, 0);
	strcat(buffer, part2);
	free(part);
	free(part2);

	return buffer;

}

void appendChar(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

#endif /* OCTO_H */
#include "nodes.h"
#include "octo.h"

/* memory usage definition (used in malloc()) */
#define DEPTH 20

/* generates new database and returns it */
DB *newDB(char *name)
{
    DB *newone = (DB *) malloc(sizeof(DB));
    newone -> name = name;
    newone -> nextID = generateID();
    return newone;
}

/* adds a simple id, value pair to the database */
void addValue(DB *db, char *idName, char *value, int type)
{

    /* create a copy of the value for the purposes of this library */
    value = makeCopy(value);

    /* if the id list contains only one node */
    if (db -> nextID == NULL)
    {
        db -> nextID -> idName = idName;
        db -> nextID -> value = value;
        db -> nextID -> type = type;
        db -> nextID -> nextDB = NULL;
        /* append another id */
        appendIDs(db -> nextID, 1);
    }
    else
    {
        int index = getIDListLength(db -> nextID) - 1;
        getID(db -> nextID, index) -> idName = idName;
        getID(db -> nextID, index) -> value = value;
        getID(db -> nextID, index) -> type = type;
        getID(db -> nextID, index) -> nextDB = NULL;
        /* append another id */
        appendIDs(db -> nextID, 1);
    }

}

/* adds a simple id, doc pair to the database */
void addDB(DB *db, DB *doc)
{

    /* if the id list contains only one node */
    if (db -> nextID == NULL)
    {
        db -> nextID -> idName = doc -> name;
        db -> nextID -> nextDB = doc;
        /* append another id */
        appendIDs(db -> nextID, 1);
    }
    else
    {
        int index = getIDListLength(db -> nextID) - 1;
        getID(db -> nextID, index) -> idName = doc -> name;
        getID(db -> nextID, index) -> nextDB = doc;
        /* append another id */
        appendIDs(db -> nextID, 1);
    }

}

/* parse a JSON string and build an equivalent internal representation */
void buildFromString(DB *db, char *string)
{
    char *pch;
    printf ("Splitting string \"%s\" into tokens:\n", string);

    pch = strtok (string, ",");
    while (pch != NULL)
    {
        printf ("%s\n", pch);
        pch = strtok (NULL, ",");
    }

    /*
    int i;
    char *currentToken = (char *) malloc(sizeof(char) * 1);
    strcpy(currentToken, "");

    for (i = 0; i < len(string); i++)
    {
        printf("Current token: %s\n", currentToken);

        /* get current characters in JSON string
    char currentChar = charAt(string, i);
    char *currentPos = string + i;

    /* skip any opening parens
    if (currentChar == '{')
    {
        continue;
    }

    /* handle any semicolons
    if (currentChar == ':')
    {

        continue;
    }

    /* make current token memory block 1 byte bigger and append char
    currentToken = (char *) realloc(currentToken, sizeof(char) * (i + 2));
    appendChar(currentToken, currentChar);

    }
    */
}

/* pretty print the database */
void prettyPrint(DB *db)
{
    prettyDB(db, 0);
}

/* Dumps db to a json file */
void dumpDB(DB *db, char *filename)
{
    remove(filename);
    FILE *fp;
    fp = fopen(filename, "a");
    fprintf(fp, "{\n");
    fclose(fp);
    prettyDBToFile(db, filename, 1);
    fp = fopen(filename, "a");
    fprintf(fp, "\n\n}");
    fclose(fp);
}

/* internal recursive printing engine */
void prettyDB(DB *db, int tabs)
{
    /* Set up format string based on tabs*/

    char *formatName = (char *) malloc(sizeof(char) * DEPTH);
    strcpy(formatName, "\n");
    int i;
    for (i = 0; i < tabs; i++)
    {
        appendChar(formatName, '\t');
    }
    appendChar(formatName, '%');
    appendChar(formatName, 's');
    appendChar(formatName, ':');
    appendChar(formatName, '\n');

    printf(formatName, db -> name);
    free(formatName);

    ID *currentID = db -> nextID;
    while (currentID -> nextID != NULL)
    {
        if (currentID -> nextDB != NULL)
        {
            prettyDB(currentID -> nextDB, tabs + 1);
            currentID = currentID -> nextID;
        }
        else
        {
            char *formatStuff = (char *) malloc(sizeof(char) * DEPTH);
            strcpy(formatStuff, "\n");
            for (i = 0; i < (tabs + 1); i++)
            {
                appendChar(formatStuff, '\t');
            }
            appendChar(formatStuff, '%');
            appendChar(formatStuff, 's');
            appendChar(formatStuff, ' ');
            appendChar(formatStuff, ':');
            appendChar(formatStuff, ' ');
            appendChar(formatStuff, '%');
            appendChar(formatStuff, 's');
            appendChar(formatStuff, '\n');
            printf(formatStuff, currentID -> idName, currentID -> value);
            free(formatStuff);
            currentID = currentID -> nextID;
        }

    }
}

/* internal recursive printing engine to file */
void prettyDBToFile(DB *db, char *filename, int tabs)
{
    /* Set up file pointer */

    FILE *fp;
    fp = fopen(filename, "a");

    /* Set up format string based on tabs */

    char *formatName = (char *) malloc(sizeof(char) * DEPTH);
    strcpy(formatName, "\n");
    int i;
    for (i = 0; i < tabs; i++)
    {
        appendChar(formatName, '\t');
    }
    appendChar(formatName, '"');
    appendChar(formatName, '%');
    appendChar(formatName, 's');
    appendChar(formatName, '"');
    appendChar(formatName, ':');
    appendChar(formatName, ' ');
    appendChar(formatName, '{');
    appendChar(formatName, '\n');
    fprintf(fp, formatName, db -> name);
    fclose(fp);
    free(formatName);

    ID *currentID = db -> nextID;
    while (currentID -> nextID != NULL)
    {
        if (currentID -> nextDB != NULL)
        {
            prettyDBToFile(currentID -> nextDB, filename, tabs + 1);
            currentID = currentID -> nextID;
        }
        else
        {
            char *formatStuff = (char *) malloc(sizeof(char) * DEPTH);
            strcpy(formatStuff, "\n");
            for (i = 0; i < (tabs + 1); i++)
            {
                appendChar(formatStuff, '\t');
            }
            appendChar(formatStuff, '"');
            appendChar(formatStuff, '%');
            appendChar(formatStuff, 's');
            appendChar(formatStuff, '"');
            appendChar(formatStuff, ' ');
            appendChar(formatStuff, ':');
            appendChar(formatStuff, ' ');
            if (currentID -> type == STRING_TYPE)
                appendChar(formatStuff, '"');
            appendChar(formatStuff, '%');
            appendChar(formatStuff, 's');
            if (currentID -> type == STRING_TYPE)
                appendChar(formatStuff, '"');
            if (currentID -> nextID -> nextID != NULL)
                appendChar(formatStuff, ',');
            appendChar(formatStuff, '\n');
            fp = fopen(filename, "a");
            fprintf(fp, formatStuff, currentID -> idName, currentID -> value);
            fclose(fp);
            free(formatStuff);
            currentID = currentID -> nextID;
        }

    }
    fp = fopen(filename, "a");
    char *formatStuff = (char *) malloc(sizeof(char) * DEPTH);
    strcpy(formatStuff, "\n");
    for (i = 0; i < (tabs); i++)
    {
        appendChar(formatStuff, '\t');
    }
    appendChar(formatStuff, '}');
    if (tabs > 1)
        appendChar(formatStuff, ',');
    fprintf(fp, formatStuff);
    free(formatStuff);
    fclose(fp);
}

/* scans through the database and deletes a node based on id */
/* TODO: Ensure that there are no memory leaks */
void deleteByID(DB *db, const char *id)
{

    int index = 0;
    int cmp;
    ID *currentID = db -> nextID;
    while (currentID != NULL)
    {
        if (strcmp(currentID -> idName, id) == 0)
        {
            break;
        }
        currentID = currentID -> nextID;
        index++;
    }
    deleteID(db -> nextID, index);

}
#ifndef WUMBO_H
#define WUMBO_H

#include <stdio.h>
#include <stdlib.h>
#include "octo.h"

/* DYNAMIC VECTOR STRUCTURE */

/* Token type constants */

#define NUM 1
#define MUL 2
#define EXP 3
#define DIV 4

/* String literals */

char* MUL_SIGN = "*";
char* DIV_SIGN = "/";
char* EXP_SIGN = "^";

/* Create a ghetto boolean data type */

typedef int bool;
#define TRUE  1
#define FALSE 0

/* NODE STRUCTURE */

typedef struct node
{

    char *tokenValue;
    int tokenType;

    int pos; /* Index of node */
    struct node *next; /* Pointer to next node */

} NODE;

/* Generates a single node */
NODE *generateNode();

/* Generates linked nodes and returns the first node */
NODE *generateNodes(int num);

/* Appends a node at the end of the list */
NODE *appendNode(NODE *start);

/* Gets a node at a certain index */
NODE *getNode(NODE *start, int index);

/* Returns the length of a list of nodes */
size_t getNodeListLength(NODE *start);

/* Removes a node at a certain index */
NODE *deleteNode(NODE *start, int index);

NODE *generateNode()
{
    NODE *newone = (NODE *) malloc(sizeof(NODE));
    newone -> pos = 0;
    newone -> next = NULL;
    return newone;
}

NODE *generateNodes(int num)
{
    NODE *one = generateNode();
    NODE *cpy = one;

    int i;

    for (i = 0; i < num - 1; i++)
    {

        NODE *next = generateNode();
        cpy -> next = next;
        cpy -> pos = i;
        cpy = next;

    }

    cpy -> pos = i;
    cpy -> next = NULL;

    return one;
}

NODE *getNode(NODE *start, int index)
{
    int i;
    for (i = 0; i < index; i++)
    {
        start = start -> next;
    }
    return start;
}

size_t getNodeListLength(NODE *start)
{
    size_t i = 1;
    while (start -> next != NULL)
    {
        start = start -> next;
        if (start == NULL)
            return NULL;
        i++;
    }
    return i;
}

NODE *deleteNode(NODE *start, int index)
{
    if (index + 1 == getNodeListLength(start))
    {
        NODE *r = getNode(start, index);
        NODE *c = getNode(start, index - 1);
        c -> next = NULL;
        free(r);
        return start;
    }
    if (index > 0)
    {
        NODE *f = getNode(start, index - 1);
        NODE *l = getNode(start, index + 1);
        NODE *d = getNode(start, index);
        f -> next = l;
        free(d);
        return start;
    }
    if (index == 0)
    {
        NODE *up = start -> next;
        free(start);
        return up;
    }
}

NODE *appendNode(NODE *start)
{
    int len = getNodeListLength(start);
    NODE *last = getNode(start, len - 1);
    NODE *n = generateNode();
    n -> pos = len;
    n -> next = NULL;
    last -> next = n;
    return n;
}

/* OPERATOR STRUCT */

typedef struct
{

    char add;
    char sub;
    char mul;
    char div;
    char exp;
    char o_paren;
    char c_paren;

} op;

op OPERATORS = {'+', '-', '*', '/', '^', '(', ')'};

/* Better number parser */

double parseNum(char *a, int radix)
{
    double d;
    sscanf(a, "%lf", &d);
    printf("\nConverted string %s to double %lf", a, d);
    return d;
}

char *doubleToString(double thing)
{
    char *str = (char *) malloc(sizeof(char) * 30);
    sprintf(str, "%lf", thing);
    printf("\nConverted double %lf to string %s", thing, str);
    return str;
}

/* Function to remove characters */

void remchars(char *str, char c)
{
    char *pos;
    while (pos = strchr(str, c))
        memmove(pos, pos + 1, strlen(pos));
}

/* OPERATOR FUNCTIONS */

char *wum_add(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) + parseNum(b, 10)));
}
char *wum_sub(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) - parseNum(b, 10)));
}
char *wum_mul(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) * parseNum(b, 10)));
}
char *wum_div(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) / parseNum(b, 10)));
}
char *wum_exp(char *a, char *b)
{
    return doubleToString((pow(parseNum(a, 10), parseNum(b, 10))));
}

/* LOGICAL FUNCTIONS */

bool isOp(char k)
{
    if (k == OPERATORS.add
            || k == OPERATORS.sub
            || k == OPERATORS.mul
            || k == OPERATORS.div
            || k == OPERATORS.exp
            || k == OPERATORS.o_paren
            || k == OPERATORS.c_paren)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

char *parseNoParen(char *expressionWithSpaces)
{

    printf("\nExpression given to parseNoParen(): %s", expressionWithSpaces);

    // Remove all whitespaces
    remchars(expressionWithSpaces, ' ');
    char *expressionWithoutSpaces = expressionWithSpaces;

    printf("\nExpression no whitespace: %s", expressionWithoutSpaces);

    char *tmpexp = makeCopy(expressionWithoutSpaces);

    // Make the expression buffer bigger
    char *expression = (char *) malloc(sizeof(char) * 100);

    // Append +
    if (charAt(tmpexp, 0) != '-' && charAt(tmpexp, 0) != '+')
        sprintf(expression, "%c%s", '+', tmpexp);
    else
        sprintf(expression, "%s", tmpexp);
    free(expressionWithSpaces);
    free(tmpexp);

    printf("\nExpression With + Signs: %s", expression);

    // Preproccess input (sign shifts)
    int j;
    for (j = 0; j < len(expression); j++)
    {
        if (charAt(expression, j) == '+' && charAt(expression, j + 1) == '+')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '-' && charAt(expression, j + 1) == '-')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '+' && charAt(expression, j + 1) == '-')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '-' && charAt(expression, j + 1) == '+')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
    }

    printf("\nAfter Preproccessor: %s", expression);

    /* Single pass lexer */

    NODE *tokens = generateNode();
    tokens -> tokenValue = NULL;

    int i, k;
    for (i = 0; i < len(expression); i++)
    {

        // multiply sign
        if (charAt(expression, i) == '*')
        {
            printf("\nFound a multiplication sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = MUL_SIGN;
            newone -> tokenType = MUL;
            continue;
        }

        // divide sign
        if (charAt(expression, i) == '/')
        {
            printf("\nFound a division sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = DIV_SIGN;
            newone -> tokenType = DIV;
            continue;
        }

        // exponent sign
        if (charAt(expression, i) == '^')
        {
            printf("\nFound an exponentiation sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = EXP_SIGN;
            newone -> tokenType = EXP;
            continue;
        }

        // any explicitly signed number
        if (charAt(expression, i) == '+' || charAt(expression, i) == '-')
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression, k) == '+' || charAt(expression, k) == '-' || charAt(expression, k) == '*' || charAt(expression, k) == '/' || charAt(expression, k) == '^')
                    break;
            }
            printf("\nFound an explicitly signed number.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = slice(expression, i, k - 1, 100);
            newone -> tokenType = NUM;
            i = k - 1;
            continue;
        }

        // any generic positive number
        else
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression, k) == '+' || charAt(expression, k) == '-' || charAt(expression, k) == '*' || charAt(expression, k) == '/' || charAt(expression, k) == '^')
                    break;
            }
            printf("\nFound a generic positive number.");
            NODE *newone = appendNode(tokens);
            char *buffer = malloc(sizeof(char) * 100);
            sprintf(buffer, "%s%s", "+", slice(expression, i, k, 100));
            newone -> tokenValue = buffer;
            newone -> tokenType = NUM;
            i = k - 1;
            continue;
        }

    }

    /* Print out the lexer tokens */

    tokens = deleteNode(tokens, 0);

    printf("\nFinished Lexing the Input:");
    printf("\nTOKEN\tTYPE");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        printf("\n%s\t%d", getNode(tokens, i) -> tokenValue, getNode(tokens, i) -> tokenType);
    }

    /* begin traversing and simplifying the intermediate representation */

    // exponents
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if (getNode(tokens, i) -> tokenType == EXP && getNode(tokens, i + 1) -> tokenType == NUM && getNode(tokens, i - 1) -> tokenType == NUM)
            {
                printf("\nExponentiating %s and %s", getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i - 1) -> tokenValue = wum_exp(getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i - 1) -> tokenType = NUM;
                deleteNode(tokens, i);
                deleteNode(tokens, i);
                printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                i = -1;
                continue;
            }
        }
    }

    // multiplication and division
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if ((getNode(tokens, i) -> tokenType == MUL || getNode(tokens, i) -> tokenType == DIV) && getNode(tokens, i + 1) -> tokenType == NUM && getNode(tokens, i - 1) -> tokenType == NUM)
            {
                if (getNode(tokens, i) -> tokenType == MUL)
                {
                    
                    /* TODO: Make this compact like the rest of the logic */
                    char* firstNum = getNode(tokens, i - 1) -> tokenValue;
                    char* secondNum = getNode(tokens, i + 1) -> tokenValue;
                    printf("\nMultiplying %s and %s", firstNum, secondNum);
                    getNode(tokens, i - 1) -> tokenValue = wum_mul(firstNum, secondNum);
                    getNode(tokens, i - 1) -> tokenType = NUM;
                    deleteNode(tokens, i);
                    deleteNode(tokens, i);
                    free(firstNum);
                    free(secondNum);
                    printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                    i = -1;
                    continue;
                }
                if (getNode(tokens, i) -> tokenType == DIV)
                {
                    printf("\nDividing: %s and %s", getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                    getNode(tokens, i - 1) -> tokenValue = wum_div(getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                    getNode(tokens, i - 1) -> tokenType = NUM;
                    deleteNode(tokens, i);
                    deleteNode(tokens, i);
                    printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                    i = -1;
                    continue;
                }
            }
        }
    }

    // normal addition
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if (getNode(tokens, i) -> tokenType == NUM && getNode(tokens, i + 1) -> tokenType == NUM)
            {
                printf("\nAdding: %s and %s", getNode(tokens, i) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i) -> tokenValue = wum_add(getNode(tokens, i) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i) -> tokenType = NUM;
                deleteNode(tokens, i + 1);
                printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                i = -1;
                continue;
            }
        }
    }
    // assemble IR back to string

    printf("\nConverting internal representation into a string.");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        printf("\nNEW TOKEN: %s \nNEW TOKEN TYPE: %d", getNode(tokens, i) -> tokenValue, getNode(tokens, i) -> tokenType);
    }

    char *buffy = (char *) malloc(sizeof(char) * 100);
    sprintf(buffy, "");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        sprintf(buffy + strlen(buffy), "%s", getNode(tokens, i) -> tokenValue);
    }

    /* TODO: FREE ALL THE MEMORY USED BY THE NODE LIST */

    return buffy;
}

/* Main parser */
double WUMBO_parse(char *expression)
{
    char *finexpression = makeCopy(expression);
    while (strchr(finexpression, '(') != NULL)
    {
        printf("Expression: %s\n", finexpression);
        int startPoint = strchr(finexpression, '(') - finexpression;
        printf("Start point: %d\n", startPoint);
        int endPoint;
        int i;
        for (i = startPoint + 1; i < len(expression); i++)
        {
            if (charAt(finexpression, i) == OPERATORS.o_paren)
            {
                startPoint = i;
            }
            if (charAt(finexpression, i) == OPERATORS.c_paren)
            {
                endPoint = i;
                break;
            }
        }
        char *subsec = slice(finexpression, startPoint, endPoint + 1, 0); // the sub expression with the parenthesis (2 + 3)
        printf("\nSubsection: %s", subsec);
        char *subsecnoparen = slice(finexpression, startPoint + 1, endPoint - 1, 0);// strip away parenthesis
        free(subsec);
        printf("\nSubsection after stripping parenthesis: %s", subsecnoparen);
        char *subsecsim = parseNoParen(subsecnoparen);
        char *temp = finexpression;
        finexpression = replaceBetween(finexpression, startPoint, endPoint + 1, subsecsim);
        free(temp);
    }
    finexpression = parseNoParen(finexpression);
    double answer = parseNum(finexpression, 10);
    free(finexpression);
    return answer;
};

#endif /* WUMBO_H */
