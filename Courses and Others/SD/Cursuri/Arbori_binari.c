#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct nod {
	int val;
	struct nod *st;
	struct nod *dr;
} Nod;

typedef Nod* Arb;

void inserare(Arb* arb,int x)
{
	Arb nou;
	if ((*arb)==NULL)
	{
		(*arb)=(Nod*)malloc(sizeof(Nod));
		(**arb).val=x;
		(**arb).st=NULL;
		(**arb).dr=NULL;
	}
	else
	{
		if ((**arb).val==x)
		{
			//printf("Valoarea deja exista");
		}
		else
		{
			if ((**arb).val>x)
			{
				if ((**arb).st==NULL)
				{
					nou=(Nod*)malloc(sizeof(Nod));
					(*nou).val=x;
					(**arb).st=nou;
					(*((**arb).st)).st=NULL;
					(*((**arb).st)).dr=NULL;
				}
				else
				{
					inserare(&((**arb).st),x);
				}
			}
			else
			{
				if ((**arb).dr==NULL)
				{
					nou=(Nod*)malloc(sizeof(Nod));
					(*nou).val=x;
					(**arb).dr=nou;
					(*((**arb).dr)).st=NULL;
					(*((**arb).dr)).dr=NULL;
				}
				else
				{
					inserare(&((**arb).dr),x);
				}
			}
		}
	}
}

void preordine(Arb arb,int pas)
{
	int i;
	if (arb!=NULL)
	{	
		for (i=1;i<=pas;i++)
			printf("\t");
		printf("%d\n",(*arb).val);
		preordine((*arb).st,pas+1);
		preordine((*arb).dr,pas+1);
	}
}
void inordine(Arb arb,int pas)
{
	int i;
	if (arb!=NULL)
	{	
		inordine((*arb).st,pas+1);
		for (i=1;i<=pas;i++)
			printf("\t");
		printf("%d\n",(*arb).val);
		
		inordine((*arb).dr,pas+1);
	}
}

Arb minim(Arb arb)
{
	if (arb==NULL)
		{
			printf("arborele e vid");
		}
	else
	{
		if ((*arb).st==NULL)
			return arb;
		else
			return minim((*arb).st);
	}
}

Arb sterge(Arb *arb,int x)
{
	Arb tmp;
	tmp=(Nod*)malloc(sizeof(Nod));
	if ((*arb)==NULL)
	{
		//printf("Nodul nu a fost gasit");
	}
	else
	{
		if ((**arb).val>x)
		{
			(**arb).st=sterge(&((**arb).st),x);
		}
		else
		{
			if ((**arb).val<x)
				{
					(**arb).dr=sterge(&((**arb).dr),x);
				}
			else
			{
				//am gasit elementul.o luam pe cele3 cazuri
				if (((**arb).st!=NULL)&&((**arb).dr!=NULL))
				{
					tmp=minim((**arb).dr);
					(**arb).val=(*tmp).val;
					(**arb).dr=sterge(&((**arb).dr),x);//la o recitire nu am inteles linia asta de cod..s-ar putea sa trebuiasca sa ramana doar ce e dupa egal.
					
				}
				else
				{
					tmp=(*arb);
					if ((**arb).st!=NULL)
						(*arb)=(**arb).st;
					else
						(*arb)=(**arb).dr;
				free(tmp);
				}
				
			}
		}
	}
return (*arb);
}

Arb find(Arb arb,int x)
{
	if (arb==NULL)
		return NULL;
	else
	{
		if ((*arb).val==x)
		{
			return (arb);
		}
		else
		if ((*arb).val>x)
		{
			return find((*arb).st,x);
		}
		else
		{
			return find((*arb).dr,x);
		}
	}
}

int main()
{
	Arb arb,gas;
	
	int x,i;	 
	arb=NULL;
	srand(time(NULL));
	for (i=1;i<30;i++)
	{
		x=rand();
		x=x%30;
		inserare(&arb,x);
	}
	//inordine(arb,0);
	//printf("\n\n\n");
	gas=find(arb,x);
	if (gas!=NULL)
		printf("%d",(*gas).val);
	//preordine(arb,0);
	sterge(&arb,5);
	//preordine(arb,0);
	return 0;
}
