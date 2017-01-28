#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef int T; 
	typedef struct nod {
	T val; 
	struct nod *leg1;
	struct nod *leg2;
	struct nod *leg4;
     
	} Nod;
	typedef Nod* List;

void creare(List *lst)
	{
         List p,nou,z,q;
         int i,r2=1,r4=1;
         scanf("%d",&i);
         (*lst)=(Nod*)malloc(sizeof(Nod));
		(**lst).val=i;
		scanf("%d",&i);
		p=*lst;
		z=*lst;
		while(i!=0)
		{
                   
                   nou=(Nod*)malloc(sizeof(Nod));
		           (*nou).val=i;
		           (*p).leg1=nou;
		           if(r2==2)
                   {
                            r2=1;
                            (*q).leg2=nou;
                   }
                   
                   if (r4%4==0)
                   {
                             (*z).leg4=nou;
                             z=nou;
                   }
                   r2++;
                   r4++;
		           scanf("%d",&i);
		           q=p;
  
		              
                
		           p=(*p).leg1;
		           
        }
        (*p).leg1=NULL;
	}
	void afisare(List lst)
	{
		while (lst!=NULL)
		{
			printf("%d ",(*lst).val);
			lst=(*lst).leg4;
		}
	}
	void cautare(List lst,int x)
	{
         List p;
         p=lst;
         
    }
int main()
{
    List lst;
    creare(&lst);
    afisare(lst);
    getch();
    return 0;
}
