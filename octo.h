#ifndef OCTO_H
#define OCTO_H

int len(char* string){

	int i = 0;
	while(*string != '\0'){
		i++;
		*string++;
	}
	return i;

}

char* lstrip(char* string){

	if(!string) 
		return;

	/* Trim off leading whitespace */
	while(*string == ' '){
		string++;
	}

	return string;

}

char* tstrip(char* string){
	
	char* end = string + len(string) - 1;
        while (end >= string && *end == ' ')
                end--;
        *(end + 1) = '\0';
	return string;

}

char* strip(char* string){

	char* lstring = lstrip(string);
	char* finalString = tstrip(lstring);
	return finalString;
}

#endif /* OCTO_H */
