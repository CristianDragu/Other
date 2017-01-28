#include <stdio.h>
#include <stdlib.h>
//algoritmul lui prim pe liste de adiacenta (pe vectori nu liste)
// si sortare topologica
void prim(int n,int p,int m[100][100], int c[100][100])
{
     int v[100],i,j,min1,min2,nr=0,r,arc1,arc2;
     for (j=0;j<=n;j++)
         v[j]=0;
    printf("Arcele care se vor pastra din graful initial sunt:");
     while (nr!=n-1)
     {
           min1=10000;
           min2=10000;
           v[p]=1;
           for (r=0;r<=n;r++)
           if (v[r]==1)
           {
           		 i=1;
            	while (c[r][i]!=0)
            	{
                  
                	  if (c[r][i]<min1 && v[m[r][i]]==0)
                  	{
                    	        min1=c[r][i];
                        	    min2=m[r][i];
                        	    arc1=r;
                        	    arc2=m[r][i];
                  	}
                  	i++;
            	}
           }
            	nr++;
            	p=min2;
            	printf("\n	%d - %d",arc1,arc2);
     }
}

void DFS(int p,int m[100][100],int v[100],int a[100][100],int r,int *q)
{
	//nodul din care s-a pornit la inceput
	int i=1;
	v[p]=1;
	a[r][(*q)]=p;
	(*q)++;
	while (m[p][i]!=0)
	{
		if (v[m[p][i]]==0)
			DFS(m[p][i],m,v,a,r,q);
			i++;
	}
}
void sortare_topologica(int n,int m[100][100])//merge doar pe graf orientat si aciclic pt a putea stabili o ordine
{//consta in parcurgeri in adancime pornind din primul nod nevizitat, punand intr-o stiva nodurile din care se pleaca(radacinile subarborilor)
//afisarea se face la golirea stivei cand se afiseaza nodul scos si nodurile vizitate prin parcurgerea pornita din el.(se refac parcurgerile)
//aseaza nodurile in asa fel incat pentru orice muchie (u,v), u sa apara inaintea lui v !!
	int v[100],i,j,a[100][100],k,q;
	
	for (j=0;j<=n;j++)
	{
         v[j]=0;
        // a[j][0]=j;
    }
    for (j=1;j<=n;j++)
    {
    	if (v[j]==0)
    		{//se porneste parcurgerea din j
    			
    			q=0;
    			DFS(j,m,v,a,j,&q);
    		}
    }
    
	/*for (i=1;i<=n;i++)
	{
		k=0;
		while (a[i][k]!=0)
		{
			printf("%d ",a[i][k]);
			k++;
		}
		printf("\n");
	}*/
	printf("\n\n Nodurile sortate:    ");
    for (j=n;j>0;j--)
    {
    	i=0;
    	while (a[j][i]!=0)
    	{
    		printf("%d ",a[j][i]);
    		i++;
   		}
   	}
}
int main()
{
    int m[100][100],c[100][100],i,j,n;
    for (i=1;i<=7;i++)
    {
        m[i][0]=i;
        
    }
    for (i=1;i<=7;i++)
        for (j=1;j<=7;j++)
        {
            m[i][j]=0;
            c[i][j]=0;
        }
        //Testul 1 (de la tabla)
    
    n=7;
	m[1][1]=2;
    m[1][2]=3;
    m[2][1]=4;
    m[3][1]=4;
    m[4][1]=5;
    m[4][2]=6;
    m[6][1]=7;
    m[7][1]=5;
    c[1][1]=1;
    c[1][2]=3;
    c[2][1]=4;
    c[3][1]=3;
    c[4][1]=4;
    c[4][2]=2;
    c[6][1]=2;
    c[7][1]=3;
    
    //Testul 2 (doar pt sortare topologica)
    /*n=6;
    m[1][1]=3;
    m[2][1]=1;
    m[2][2]=4;
    m[4][1]=5;
    m[5][1]=1;
	m[6][1]=3;
    m[6][2]=4;*/
    
    prim(7,1,m,c);
    sortare_topologica(n,m);
    
    getch();
    return 0;
}
