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

char* strip(char* string){
	
	/* Trim off leading whitespace */
	while(*string == ' '){
		string++;
	}

	/*TODO: Trim off trailing whitespace*/

	return string;

}

#endif /* OCTO_H */
