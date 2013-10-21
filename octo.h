#ifndef OCTO_H
#define OCTO_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

size_t len(char* string){

	char *end = string;
	for(;*end;++end){}
	return (size_t) (end-string);

}

char* makeCopy(char* s){
	
	char* buff = (char*) malloc(len(s) + 1);
	strcpy(buff, s);
	return buff;
}

void* lstrip(char* string){

	if(!string) 
		return string;

	/* Trim off leading whitespace */
	while(isspace(*string)){
		string++;
	}

	return string;

}

void* rstrip(char* string){
	
	/* Trim off trailing whitespace */
	char* end = string + len(string) - 1;
        while (end >= string && isspace(*end))
                end--;
        *(end + 1) = '\0';
	
	return string;

}

void* strip(char* string){

	/* Trim off both leading and trailing whitespace */
	char* lstring = lstrip(string);
	char* finalString = rstrip(lstring);
	
	return finalString;

}

char* slice(char* s, int start, int end){

	/* Create a new identical buffer */
	char* buff = (char*) malloc((end - start) + 2);
	strncpy(buff, s + start, (end - start) + 1);
	*(buff + (end - start) + 1) = '\0';
	return buff;
}

char* toUpperCase(char* s){
	
	char* q = makeCopy(s);
	int i;
	for(i = 0; i < len(q); i++){
		*(q + i) = toupper(*(q + i));
	}

	return q;

}

char* toLowerCase(char* s){

	char* q = makeCopy(s);
	int i;
	for(i = 0; i < len(q); i++){
		*(q + i) = tolower(*(q + i));
	}

	return q;

}

char* intToString(int n){

	int c = (int) log10((double)n) + 1;
	char* b = (char*) malloc(c + 1);
	sprintf(b,"%d",n);
	
	return b;
    
}

int stringToInt(char* s){

	return atoi(s);
	
}

char charAt(char* s, int n){
	
	return *(s + n);
	
}

char* replaceBetween(char* s, int start, int end, char* what){

	char* buffer = malloc(len(s) + len(what));
	*(buffer) = '\0';	
	char* part = slice(s, 0, start - 1);
	strcat(buffer,part);
	strcat(buffer,what);
	char* part2 = slice(s, end, len(s) - 1);
	strcat(buffer, part2);
	free(part);
	free(part2);

	return buffer;

}

void appendChar(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

#endif /* OCTO_H */
