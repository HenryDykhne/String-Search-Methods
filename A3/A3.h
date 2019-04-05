/*  
*   Eli-Henry Dykhne
*   0996524
*   10/02/2019
*   A2
*/

#ifndef A3_H
#define A3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

typedef struct sortPair{
    char * unsort;
    char * sort;
} sortPair;

int compar(const void *l, const void *r);

int comparPair(const void *l, const void *r);

void doubleSort(sortPair *arr, int length);

int numAnagrams(sortPair *arr, char* str, int size, int brute);

int bruteAnagram(char *a, char *b);

int* boyerMooreTableGenerator(char *word, int wordLen);

int boyerMooreNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts);

int horspoolNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts);

int bruteNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts);

double elapse(struct timeb *stop, struct timeb *start);

#endif  