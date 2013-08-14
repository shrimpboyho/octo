#include <stdio.h>
#include "octo.h"
#include <string.h>
int main( void ){

	printf("Unit testing has begun\n");

	/* len() test */
	char* testy = "BUNZ! ";
	printf("The string \"%s\" is %d characters long.\n", testy, len(testy));
	if(len(testy) == 6) printf("TEST PASSED.\n");

	/* strip() test */
	char buffer2[60] = "       NARC!      ";
	char* testy2 = buffer2;
	printf("The stripped string: \"%s\"\n", strip(testy2));

	/* slice() test */
	char buffer3[60] = "STUFFY!";
	char* testy3 = buffer3;
	printf("The sliced string: \"%s\"\n", slice(testy3, 0, 1));
	
	return 0;
}
