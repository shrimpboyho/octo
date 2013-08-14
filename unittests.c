#include <stdio.h>
#include "octo.h"

int main( void ){

	printf("Unit testing has begun\n");

	/* len() test */
	char* testy = "BUNZ! ";
	printf("The string \"%s\" is %d characters long.\n", testy, len(testy));
	if(len(testy) == 6) printf("TEST PASSED.\n");

	/* strip() test*/
	char* testy2 = "       NARC!";
	printf("The stripped string: \"%s\"\n",strip(testy2));
	return 0;
}
