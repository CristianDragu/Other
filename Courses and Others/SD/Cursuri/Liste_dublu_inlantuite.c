#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef int T; 
	typedef struct nod {
	T val; 
	struct nod *next;
	struct nod *prev; 
	
	} Nod;
	typedef Nod* List;
	
	void inserare(List *first,List *last,int x)
	{
		List p,nou;
		nou=(Nod*)malloc(sizeof(Nod));
		(*nou).val=x;
		if (x<(**first).val)
		{
			(*nou).next=*first;
			*first=nou;
		}
		else
		{
			p=*first;
			while((*p).next!=NULL && (*((*p).next)).val<x)
			p=(*p).next;
			(*nou).next=(*p).next;
			(*p).next=nou;
		}
	}
	
	void creare(List *first, List *last)
	{
         int i;
         List r;
         scanf("%d",&i);
		(*first)=(Nod*)malloc(sizeof(Nod));
		(**first).val=i;
		*last=*first;
		scanf("%d",&i);
		while(i!=0)
		{
                   inserare(first,last,i);
		           scanf("%d",&i);
        }
        *last=*first;
        while ((**last).next!=NULL)
        {
        printf("%d ",(**last).val);
        (*last)=(**last).next;
    	}
	}
int main()
{
	List first, last;
	creare(&first,&last);
	//printf("%d %d",(*first).val,(*last).val);
	getch();
	return 0;
}

