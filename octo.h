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

#endif /* OCTO_H */
