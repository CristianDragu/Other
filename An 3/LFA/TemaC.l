%{
	// Dragu Cristian 332CC
	#include <stdio.h>

	/*
	functions = vector de siruri de caractere, ce contine numele functiilor
	length = lungimea vectorului functions
	nrFunc = numarul de functii apelate in interiorul unei functii. Este -1
			doar daca analiza input-ului este la nivelul definitiilor de functii 
			de la inceputul programului.
	*/
	char functions[100][100];
	int length = 0;
	int nrFunc = -1;

	/*Functia addFunc adauga numele unei functii intr-un vector 
	  de siruri*/
	void addFunc(char *s){
		int i;
		for(i = 0; i < strlen(s); i++)
			functions[length][i] = s[i];
		length++;
	}

	/*Verificam daca numele functiei a fost adaugat in vectorul
	  de siruri. Daca exista, se returneaza 0, altfel 1.*/
	int checkFunc(char *s){
		int i;
		for(i = 0; i < length; i++){
			if(strcmp(functions[i], s) == 0)
				return 0;
		}

		return 1;
	}

	/*
	args - folosit pentru identificarea unei liste de argumente
	Prototype - folosit pentru identificarea unui prototip de functie. Exemplu: void func1
	ProtArgs - determina argumentele si continutul unei functii (acolada deschisa). Daca
				Se foloseste {Prototype}/{ProtArgs} se va identifica prototipul functiei ce 
				este urmat de continutul ei. Exemplu: void func1(){
	Un apel de functie poate fi de forma "func1();". Se observa prezenta ";" la final, ceea ce 
	rezulta ca daca identificarea se face si dupa caracterul ";" care trebuie plasat la final 
	de apel, atunci se exclude gasirea if, for, while, ce ar da eroare daca au ";" la final de 
	sintagma.
	*/
%}

litera [a-zA-Z]
functie [a-zA-Z0-9]
args \(.*\)

Prototype {litera}+\ {functie}+
ProtArgs {args}[\ \t\n]*\{
FuncCall {functie}+
FuncArgs {args}\;

%%
{Prototype}/{ProtArgs}	{
							//daca s-au numarat apeluri de functii in interiorul unui corp de functie
							//atunci este afisat acest numar.
							if(nrFunc == 0)
								printf("%d functii apelate\n", nrFunc);
							else if(nrFunc > 0)
								printf("- %d functii apelate\n", nrFunc);
							nrFunc = 0;
							char *p;
							//{Prototype} face match pe o structura de forma "void func1" si trebuie 
							//taiata la spatiu, deoarece ne intereseaza doar numele functiei
							p = strtok(yytext, " ");
							p = strtok(NULL, " ");
							printf("%s:\n\t->", p);
						}

{FuncCall}/{FuncArgs}	{
							//daca ma aflu la inceputul programului la nivelul definitiilor de functii, 
							//adaug functia in vectorul de siruri de caractere.
							if(nrFunc == -1){
								addFunc(yytext);
							}
							//altfel verific daca functia apelata este una care are definitie
							else
								if(checkFunc(yytext) == 0){
									printf("%s ", yytext);
									nrFunc++;
								}
						}

.|\n					{}

<<EOF>> 				{
							//daca am ajuns la final de fisier, verific daca mai am de scris la output si
							//termin analiza
							if(nrFunc == 0)
								printf("%d functii apelate\n", nrFunc);
							else if(nrFunc > 0)
								printf("- %d functii apelate\n", nrFunc);
							yyterminate();
						}
%%

int main(int argc, char **argv){

	FILE *fisier;

	fisier = fopen(*(argv + 1), "r");

	if(!fisier){
		printf("Eroare deschidere fisier!\n");
		exit(1);
	}

	yyin = fisier;
	yylex();

	fclose(yyin);

	return 0;
}