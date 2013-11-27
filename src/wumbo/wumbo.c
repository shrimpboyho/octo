#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../headers/wumbo.h"

int main( void ){

	printf("Wumbo testing has begun\n");

	char* buffer = (char*) malloc(60);
	scanf("%[^\n]", buffer);
	double answer = WUMBO_parse(buffer);
	printf("\nAnswer: %lf\n", answer);

	return 0;
}
