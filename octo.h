#ifndef OCTO_H
#define OCTO_H

#include <stdlib.h>
#include <string.h>

int len(char* string){

	char *end = string;
	for(;*end;++end){}
	return (size_t) (end-string);

}

char* makeCopy(char* s){
	
	char* buff = (char*) malloc(len(s) + 1);
	strcpy(buff, s);
	return buff;
}

char* lstrip(char* string){

	if(!string) 
		return string;

	/* Trim off leading whitespace */
	while(isspace(*string)){
		string++;
	}

	return string;

}

char* rstrip(char* string){
	
	/* Trim off trailing whitespace */
	char* end = string + len(string) - 1;
        while (end >= string && isspace(*end))
                end--;
        *(end + 1) = '\0';
	
	return string;

}

char* strip(char* string){

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

#endif /* OCTO_H */
