#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wumbo.h"

int main( void ){

	printf("Wumbo testing has begun\n");

	char* buffer = (char*) malloc(60);
	scanf("%[^\n]", buffer);
	char* answer = WUMBO_parse(buffer);
	printf('Answer: %s', answer);

	return 0;
}
