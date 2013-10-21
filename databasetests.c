#include "database.h"
#include <stdlib.h>
#include <stdio.h>

int main ( void )
{

    /* Create a database */
    DB *bank = newDB("Employees");
    printf("Name of db is: %s", bank -> name);
    addValue(bank, "Daniel", "Programmer");
    addValue(bank, "Kevin", "Hardware");
    
    /* Create another database*/
    DB *money = newDB("Money");
    addValue(money, "Monday", "5");
    addValue(money, "Tuesday", "7");

    /* Shove the money database in the bank */
    addDB(bank,money);

    /* Pretty print the entire database*/
    prettyPrint(bank);

    /* Dump database contents to json file */
    dumpDB(bank, "bank.db");
    
    //buildFromString(bank, "{narc:j,jew:k}");
    return 0;
}
