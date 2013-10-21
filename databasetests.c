#include "database.h"
#include <stdlib.h>
#include <stdio.h>

int main ( void )
{

	DB* bank = newDB("junk");
	printf("Name of db is: %s",bank -> name);
	addPair(bank,'stuff','narc');
	printf("\nSize of db is: %d",getIDListLength(bank -> nextID));
	return 0;
}
