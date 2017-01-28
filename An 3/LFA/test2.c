// Dragu Cristian 332CC
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define arrayLength 20000
#define separators "\'\" ,!?"

struct cuvant{
	char* word;
	int matches;
};
typedef struct cuvant words;

int compare(const void* a, const void* b);
int findWords(char *cuvant, words *cuvinte, int length);
int dist(char *cuv1, char *cuv2);
void sim(words *NR1, int length1, words *NR2, int length2);
void analizeText(char **text1, int N, char **text2, int M);

int main(){

	int N, M, i;
	char **text1, **text2;

	scanf("%d", &N);
	getchar();

	text1 = (char**)malloc(N * sizeof(char*));

	for(i = 0; i < N; i++){
		text1[i] = (char*)malloc(arrayLength);
		fgets(text1[i], arrayLength, stdin);
		text1[i][strlen(text1[i]) - 1] = '\0';
	}

	scanf("%d", &M);
	getchar();

	text2 = (char**)malloc(M * sizeof(char*));

	for(i = 0; i < M; i++){
		text2[i] = (char*)malloc(arrayLength);
		fgets(text2[i], arrayLength, stdin);
		text2[i][strlen(text2[i]) - 1] = '\0';
	}

	analizeText(text1, N, text2, M);

	return 0;
}

int compare(const void* a, const void* b){
	words arg1 = *(const words *)a;
	words arg2 = *(const words *)b;
 
 	if(arg1.matches < arg2.matches) return 1;
 	if(arg1.matches > arg2.matches) return -1;
	if(strcmp(arg1.word, arg2.word) > 0) return 1;
	if(strcmp(arg1.word, arg2.word) < 0) return -1;

	return 0;
}

int findWords(char *cuvant, words *cuvinte, int length){

	int i;

	for(i = 0; i < length; i++)
		if(strcmp(cuvant, cuvinte[i].word) == 0)
			return i;

	return -1;

}

int dist(char *cuv1, char *cuv2){

	int length1 = strlen(cuv1);
	int length2 = strlen(cuv2);
	int lengthmin, lengthmax, sum = 0;

	if(length1 > length2){
		lengthmax = length1;
		lengthmin = length2;
	}
	else{
		lengthmax = length2;
		lengthmin = length1;
	}

	int i;

	for(i = 0; i < lengthmin; i++)
		sum += abs(cuv1[i] - cuv2[i]);

	if(lengthmin == length1){
		for(i = lengthmin; i < lengthmax; i++)
			sum += abs('\0' - cuv2[i]);
	}
	else{
		for(i = lengthmin; i < lengthmax; i++)
			sum += abs(cuv1[i] - '\0');	
	}

	return sum;
}

void sim(words *NR1, int length1, words *NR2, int length2){

	int NR = 0, i;

	if(length1 > length2)
    	NR = length2;
    else
    	NR = length1;

    int similitudine = 0;

    similitudine = 100 * abs(length1 - length2);

    for(i = 0; i < NR; i++){
    	similitudine += (NR1[i].matches + NR2[i].matches) * dist(NR1[i].word, NR2[i].word);
    }

    printf("%d\n", similitudine);

}

void analizeText(char **text1, int N, char **text2, int M){

	int i, length1 = 0, length2 = 0, pozitie;
	char *aux, *p;
	words *NR1, *NR2;

	NR1 = (words*)malloc(N * arrayLength * sizeof(words));
	NR2 = (words*)malloc(M * arrayLength * sizeof(words));

	for(i = 0; i < N; i++){
		aux = strdup(text1[i]);
		p = strtok(aux, separators);
		while(p != NULL){
			if((pozitie = findWords(p, NR1, length1)) != -1){
				NR1[pozitie].matches++;
			}
			else{
				NR1[length1].word = strdup(p);
				NR1[length1].matches = 1;
				length1++;
			}
			p = strtok(NULL, separators);
		}
	}

	for(i = 0; i < M; i++){
		aux = strdup(text2[i]);
		p = strtok(aux, separators);
		while(p != NULL){
			if((pozitie = findWords(p, NR2, length2)) != -1){ 
				NR2[pozitie].matches++;
			}
			else{
				NR2[length2].word = strdup(p);
				NR2[length2].matches = 1;
				length2++;
			}
			p = strtok(NULL, separators);
		}
	}
	qsort(NR1, length1, sizeof(words), compare);

    qsort(NR2, length2, sizeof(words), compare);

    sim(NR1, length1, NR2, length2);

}