#include "database.h"
#include <stdlib.h>
#include <stdio.h>

int main ( void )
{

    /* Create a database */
    DB *bank = newDB("Employees");
    printf("Name of db is: %s", bank -> name);
    addValue(bank, "Daniel", "Programmer", STRING_TYPE);
    addValue(bank, "Kevin", "Hardware", STRING_TYPE);
    
    /* Create another database*/
    DB *money = newDB("Money");
    addValue(money, "Monday", "5", NUM_TYPE);
    addValue(money, "Tuesday", "7", NUM_TYPE);

    /* Shove the money database in the bank */
    addDB(bank,money);

    addValue(bank, "Lark", "Whack", STRING_TYPE);

    /* Pretty print the entire database*/
    prettyPrint(bank);

    /* Dump database contents to json file */
    dumpDB(bank, "bank.json");
    
    //buildFromString(bank, "{narc:j,jew:k}");
    return 0;
}
