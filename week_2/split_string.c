#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define len 100

void PrintWords(char * string) {
	//Getting a pointer for the 1st word
	char * word = strtok(string, " ");

	//Printing and getting pointers for the rest
	//Until the end of the string
	while (word != NULL) {
		printf("%s\n", word);
		word = strtok(NULL, " ");
	}
}


int main() {
	char * string = (char *) calloc(len + 1, sizeof(char));

	scanf("%[^\n]", string);

	PrintWords(string);

	free(string);
	return 0;
}