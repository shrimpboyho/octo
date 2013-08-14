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

	return "THIS IS NOT IMPLEMENTED YET";

}

char* strip(char* string){

	char* lstring = lstrip(string);
	char* finalString = tstrip(lstring);
	return lstring;
}

#endif /* OCTO_H */
