#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

typedef int T; 
	typedef struct nod {
	T val; 
	struct nod *leg; 
	} Nod;
	typedef Nod* List;
	
	void inserare(List *lst,int x)
	{
		List p,nou;
		nou=(Nod*)malloc(sizeof(Nod));
		(*nou).val=x;
		if (x<(**lst).val)
		{
			(*nou).leg=*lst;
			*lst=nou;
		}
		else
		{
			p=*lst;
			while((*p).leg!=NULL && (*((*p).leg)).val<x)
			p=(*p).leg;
			(*nou).leg=(*p).leg;
			(*p).leg=nou;
		}
	}
	void creare(List *lst)
	{
         int i;
         scanf("%d",&i);
		(*lst)=(Nod*)malloc(sizeof(Nod));
		(**lst).val=i;
		scanf("%d",&i);
		while(i!=0)
		{
                   inserare(lst,i);
		           scanf("%d",&i);
        }
	}
	void afisare(List lst)
	{
		while (lst!=NULL)
		{
			printf("%d ",(*lst).val);
			lst=(*lst).leg;
		}
	}
	void stergere(List *lst,int x)
	{
         List p;
         if ((**lst).val==x)
         *lst=(**lst).leg;
         else
         {
         p=lst;
         while((*p).leg!=NULL && (*((*p).leg)).val!=x)
         p=(*p).leg;
         if ((*p).leg!=NULL)
            (*p).leg=(*((*p).leg)).leg;
            
         }
    }
    void poz(List lst,int x)
    {
         List p;
         p=lst;
         int i=0;
         while (p!=NULL)
         {
         i++;
         if ((*p).val==x)
          printf("\n%d",i);
          p=(*p).leg;
         }
    }
    void circ(List lst,int n)
    {
         int r=1;
         List p,q;
         p=lst;
         q=lst;
         while ((*q).leg!=NULL)
         q=(*q).leg;
         (*q).leg=lst;
         
         while ((*p).leg!=p)
         {
               r++;
               q=p;
               p=(*p).leg;
               if (r==n)
               {
                        r=0;
                        printf("%d",(*p).val);
                        (*q).leg=(*p).leg;     
               }
               
               
         }
         printf("%d",(*p).val);
         
    }
int main()
{
	List lst;
	creare(&lst);
	//inserare(lst,4);
	afisare(lst);
	//stergere(&lst,1);
	printf("\n");
	afisare(lst);
	printf("\n");
	poz(lst,4);
	printf("\n");
	circ(lst,2);
	getch();
	return 0;
	
}
