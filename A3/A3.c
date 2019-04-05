/*  
*   Eli-Henry Dykhne
*   0996524
*   03/03/2019
*   A3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <stdbool.h>
#include "A3.h"

//this funcion compares and orders chars alphabetically
int compar(const void *l, const void *r){
    char *a = (char*)l;
    char *b = (char*)r;

    return *a-*b;
}

int comparPair(const void *l, const void *r){
    sortPair *a = (sortPair*)l;
    sortPair *b = (sortPair*)r;

    return strcmp(a->sort, b->sort);
}

//checks if two strings are anagrams by brute force
int bruteAnagram(char *a, char *b){
    int cha[256] = {0};//arrays to hold num occurances per char per string
    int chb[256] = {0};

    for(int i = 0; a[i] != '\0'; i++){
        cha[(int)a[i]]++;
    }
    for(int i = 0; b[i] != '\0'; i++){
        chb[(int)b[i]]++;
    }

    for(int i = 0; i<256; i++){
        if(cha[i] != chb[i]){
            return 0;
        }
    }
    return 1;
}

void doubleSort(sortPair *arr, int length){
    //sorts the individual strings
    for(int i = 0; i<length; i++){
        qsort(arr[i].sort, strlen(arr[i].sort), sizeof(char), compar);
    }
    //sorts the array of strings
    qsort(arr, length, sizeof(sortPair), comparPair);
}

//counts the number of anagrams in a list of strings compared to another string
int numAnagrams(sortPair *arr, char* str, int size, int brute){
    int num = 0;
    char *first = malloc(sizeof(char)*(strlen(str)+1));
    strcpy(first, str);
    qsort(first, strlen(first), sizeof(char), compar);//sorts the one string that will be compared to the rest
    if(brute){
        for(int i = 0; i < size; i++){
            if(bruteAnagram((arr[i]).sort, str)){
                printf("%s\n", (arr[i]).unsort);
                num++;
            } 

        }
    }else{
        int l = 0;
        int r = size-1;
        //binary search
        while (l <= r) { 
            int m = l+(r-l)/2; 
            
            //Check if x at mid 
            if (strcmp((arr[m]).sort, first) == 0){
                //now check either side
                //right
                for(int i = 0; strcmp((arr[i]).sort, first)!=0; i++){
                    if(strcmp((arr[m+i]).sort, first) == 0){
                        printf("%s\n", (arr[m+i]).unsort);
                        num++;
                    }
                }
                //left
                for(int i = 1; strcmp((arr[i]).sort, first)!=0; i++){
                    if(strcmp((arr[m-i]).sort, first) == 0){
                        printf("%s\n", (arr[m-i]).unsort);
                        num++;
                    }
                }
                return num;
            }else if (strcmp((arr[m]).sort, first) < 0){
                //if x bigger
                l = m + 1; 
            }else{
                //If x is smaller
                r = m - 1; 
            } 
        }
    }
    free(first);
    return num;
}

//generates the good suffix table for the boyer moore algorithm
int* boyerMooreTableGenerator(char *word, int wordLen){
    int *bmTable = malloc(sizeof(int)*wordLen+2);
    int i;
    for(int j = 1; j<=wordLen; j++){
        for(i = j; i<wordLen-1+j; i++){
            if(wordLen-i-1 >=0){
                
                /*fwrite(&(word[wordLen-i-1]), j, sizeof(char), stdout);
                printf(",");
                fwrite(&(word[wordLen-j]), j, sizeof(char), stdout);
                printf("\n");
                */
                if(strncmp(&(word[wordLen-i-1]), &(word[wordLen-j]), j)==0){
                    break;
                }
            }else{
                /*fwrite(word, j-(i-wordLen+1), sizeof(char), stdout);
                printf("|");
                fwrite(&(word[wordLen-j+(i-wordLen+1)]), j-(i-wordLen+1), sizeof(char), stdout);
                printf("\n");*/
                if(strncmp(word, &(word[wordLen-j+(i-wordLen+1)]), j-(i-wordLen+1))==0){
                    break;
                }
            }
        }
        //printf("\n");
        bmTable[j] = i-j+1;
    }

    /*for(int j = 1; j<=wordLen; j++){
        printf("%d, %d\n", j, bmTable[j]);
    }*/
    return bmTable;
}


//generates the bad match table for the horspool algorithm
int *horspoolTableGenarator(char *word, int wordLen){
    int *hTable = malloc(sizeof(int)*256);
    for(int i = 0; i<256; i++){
        hTable[i] = wordLen;
    }

    for(int i = 0; i<wordLen-1; i++){
        hTable[(int)word[i]] = wordLen - i - 1;
    }

    

    return hTable;
}

//counts the number of occurances of a string within another string using the boyer moore algorithm,
int boyerMooreNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts){
    int occurances = 0;
    (*shifts) = 0;
    int *hTable;
    int *bmTable;
    char first;
    int dist;
    int k;

    hTable = horspoolTableGenarator(word, wordLen);
    bmTable = boyerMooreTableGenerator(word, wordLen);
    /*for(int i = 0; i<=wordLen; i++){
        printf("%d\n", bmTable[i]);
    }
    printf("\n");
    for(int i = 0; i<256; i++){
        printf("%d\n", hTable[i]);
    }*/
    for(int i = 0; i < strLen-wordLen+1; i++){
        occurances++; 
        (*shifts)++;
        first = str[i+wordLen-1];
        k = 0;
        for(int j = wordLen-1; j >=0; j--){
            
            if(str[i+j] != word[j]){
                dist = 1;
                occurances--;
                if((int)first<256 &&(int)first>=0){
                    
                    if(k==0){
                        dist = hTable[(int)first];
                    }else{
                        dist = hTable[(int)first]-k;
                        //printf("dist = %d\n", dist);
                        if(bmTable[k]>dist){
                            dist = bmTable[k];
                        }
                    }

                }else{
                    
                    dist=wordLen;
                    
                }

                
                dist--;
                
                i+=dist;
                break;
            }
            k++;
        }
        if(k == wordLen){
            i+=bmTable[k]-1;
            //(*shifts)++;
            //printf("%d\n", bmTable[k]);
        }
        
    }

    free(hTable);
    free(bmTable);
    return occurances;
}

//counts the number of occurances of a string in another string using the horspool algorithm
int horspoolNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts){
    int occurances = 0;
    (*shifts) = 0;
    int *hTable;
    char first;
    int j;

    hTable = horspoolTableGenarator(word, wordLen);

    for(int i = 0; i < strLen-wordLen+1; i++){
        occurances++; 
        
        first = str[i+wordLen-1];
        int k = 0;
        for(j = wordLen-1; j >=0; j--){
            if(str[i+j] != word[j]){
                occurances--;
                if((int)first<256 &&(int)first>=0){
                    if(hTable[(int)first]>1){
                        i+=hTable[(int)first]-1;//-(wordLen-1-j);
                    }
                    
                }else{
                    if(wordLen>1){
                        i+=wordLen-1;//-(wordLen-1-j);
                    }
                    
                }
                
                
                //printf("%c, %d, %d\n", first, (int)first, hTable[(int)first]);
                (*shifts)++;
                break;
            }
            k++;
        }
        if(k == wordLen){
            i+=hTable[(int)first]-1;
            (*shifts)++;
            //printf("%d\n", hTable[(int)first]);
        }
    }

    free(hTable);
    return occurances;
}

//counts the number of occurances of a stirng in another string using brute force.
int bruteNumOcurances(char *str, char*word, int strLen, int wordLen, int *shifts){
    *shifts = 0;
    int occurances = 0;
    for(int i = 0; i < strLen-wordLen+1; i++){
        occurances++; 
        (*shifts)++;
        for(int j = 0; j < wordLen; j++){
            if(str[i+j] != word[j]){
                occurances--;
                break;
            }
        }
    }
    return occurances;
}

//calculates amount of elapsed time.
double elapse(struct timeb *stop, struct timeb *start){
	return (double)((double)(stop->time*1000 + (double)stop->millitm) - (double)(start->time*1000 + (double)start->millitm))/(double)1000;
}