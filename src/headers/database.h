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
