#include <stdio.h>
#include "../headers/octo.h"
#include <string.h>
#include <math.h>
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
	printf("The sliced string: \"%s\"\n", slice(testy3, 1, 4, 0));
	
	/* makeCopy() test */
	char buffer4[60] = "I AM THE walrus.";
	char* testy4 = buffer4;
	printf("A copy of the string: \"%s\"\n", makeCopy(testy4));

	/* toUpperCase() test */
	char buffer5[60] = "I AM THE walrus.";
	char* testy5 = buffer5;
	printf("A uppercase version of the string: \"%s\"\n", toUpperCase(testy5));

	/* toLowerCase() test */
	char buffer6[60] = "I AM THE walrus.";
	char* testy6 = buffer6;
	printf("A lowercase version of the string: \"%s\"\n", toLowerCase(testy6));

	/* replaceBetween() test */
	char buffer7[60] = "The Hello World Code!";
	char* testy7 = replaceBetween(buffer7,5,8,"jjj");
	printf("replaceBetween() test: \"%s\"\n",testy7);

	return 0;
}
