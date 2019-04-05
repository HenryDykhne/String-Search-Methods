/*	
*	Eli-Henry Dykhne
*	0996524
* 	10/02/2019
*	A2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "A3.h"

int main(){
	struct timeb *start = malloc(sizeof(struct timeb));
	struct timeb *stop = malloc(sizeof(struct timeb));
	int i = 0;
	int num;
	int size = 500;
	sortPair *arr = malloc(sizeof(sortPair)*size);
	char *buf;
	char *str = malloc(300);
	FILE *file = fopen("data_4.txt", "r");

	if(file == NULL){
		printf("file not found\n");
		return 0;
	}
	while(fgets(str, 300, file)){
		
		if(str[strlen(str)] == '\n'){
			str[strlen(str)] = '\0';
		}
		buf = strtok(str, " ");
		while(buf && buf[0] != '\n'){
			(arr[i]).unsort = malloc(sizeof(char)*(strlen(buf)+1));
			(arr[i]).sort = malloc(sizeof(char)*(strlen(buf)+1));
			strcpy((arr[i]).unsort, buf);
			strcpy((arr[i]).sort, buf);
			
			buf = strtok(NULL, " ");
			i++;
			if(size<=i){
				size+=500;
				arr = realloc(arr, sizeof(sortPair)*size);
			}
		}
	}

	fclose(file);


	char word[1000];
	printf("Enter a string: ");
	scanf("%s",word);

	

	ftime(start);
	num = numAnagrams(arr, word, i, 1);
	ftime(stop);
	printf("Num nums: %d\nBrute\nNumAnagrams: %d\nTime: %f\n\n", i, num, elapse(stop, start));
	

	ftime(start);
	doubleSort(arr, i);
	ftime(stop);
	printf("Presorted\nTime to sort: %f\n", elapse(stop, start));

	ftime(start);
	num = numAnagrams(arr, word, i, 0);
	ftime(stop);
	printf("NumAnagrams: %d\nTime to search: %f\n", num, elapse(stop, start));

	free(str);
	for(i = i-1; i>=0; i--){
		//printf("%s\n", (arr[i]).sort);
		free(arr[i].sort);
		free(arr[i].unsort);
	}

	free(arr);
	free(start);
	free(stop);

	return 0;
}