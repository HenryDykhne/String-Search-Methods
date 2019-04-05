/*	
*	Eli-Henry Dykhne
*	0996524
* 	04/03/2019
*	A3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "A3.h"

int main(){
	FILE *file = fopen("data_5.txt", "r");
	struct timeb *start = malloc(sizeof(struct timeb));
	struct timeb *stop = malloc(sizeof(struct timeb));
	int num;
	int i = 0;
	int cap = 0;
	int size = 500;
	char buf;
	char *str = malloc(500);
	int shifts;
	//reading in the file char by char
	while(EOF != (buf = fgetc(file))){
		str[i] = buf;
		i++;
		if(size<=i){
			size+=500;
			str = realloc(str, sizeof(char)*size);
		}
	}
	str[i] = '\0';
	str = realloc(str, sizeof(char)*(strlen(str)+1));
	printf("Num Chars: %d\n", i);
	fclose(file);
	
	char word[1000];
	printf("Enter a string: ");
	while((buf = getc(stdin)) != '\n'){
		word[cap] = buf;
		cap++;
	}
	word[cap] = '\0';

	ftime(start);
	num = bruteNumOcurances(str, word, i, strlen(word), &shifts);
	ftime(stop);
	printf("Brute string search\n--------------------------\nNumber of occurances: %d\nNum pattern shifts: %d\nTime: %f\n", num, shifts, elapse(stop, start));
	
	ftime(start);
	num = horspoolNumOcurances(str, word, i, strlen(word), &shifts);
	ftime(stop);
	printf("\n\n\nHorspool string search\n--------------------------\nNumber of occurances: %d\nNum pattern shifts: %d\nTime: %f\n", num, shifts, elapse(stop, start));

	ftime(start);
	num = boyerMooreNumOcurances(str, word, i, strlen(word), &shifts);
	ftime(stop);
	printf("\n\n\nBoyer-Moore string search\n--------------------------\nNumber of occurances: %d\nNum pattern shifts: %d\nTime: %f\n", num, shifts, elapse(stop, start));

	//boyerMooreTableGenerator("BAOBAB", 6);
	free(str);
	free(start);
	free(stop);
	return 0;
}