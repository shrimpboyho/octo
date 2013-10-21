#include "nodes.h"

/* DATABASE STRUCT */

typedef struct db{

	char* name; /* Name of database */
	ID* nextID; /* Pointer to next id */

} DB;

/* generates new database and returns it */
DB* newDB(char* name)
{
	DB* newone = (DB*) malloc(sizeof(DB));
	newone -> name = name;
	newone -> nextID = generateID();
	return newone;
}

/* adds a simple id, value pair to the database */
void addPair(DB* db, char* idName, char* value)
{

	/* if the id list contains only one node */
	if(db -> nextID == NULL)
	{
		db -> nextID -> idName = idName;
		db -> nextID -> value = value;
		/* append another id */
		appendIDs(db -> nextID, 1);
	}
	else
	{
		int index = getIDListLength(db -> nextID) - 1;
		getID(db -> nextID, index) -> idName = idName;
		getID(db -> nextID, index) -> value = value;
		/* append another id */
		appendIDs(db -> nextID, 1);
	}

}