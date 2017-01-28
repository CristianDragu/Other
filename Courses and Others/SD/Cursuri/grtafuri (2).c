#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void bf(int nod,int a[100][100],int n)
{
     int coada[100],s[100],ic=1,sc=1,i;
     for (i=1;i<=n;i++)
      s[i]=0;
      
     coada[ic]=nod;
      s[nod]=1;
     while(ic<=sc)
     {
                  i=1;
                  while (i<=n)
                  {
                        if (a[coada[ic]][i]!=0 && s[i]==0)
                        {
                           sc++;
                           coada[sc]=i;
                           s[i]=1;
                        }
                        i++;
                  }
                  printf("%d ",coada[ic]);
                  ic++;
     }
}
void df(int nod,int a[100][100],int n,int s[100])
{
     int i,k;
      printf("%d ",nod);
      s[nod]=1;
      for (k=1;k<=n;k++)
          if (a[nod][k]!=0 && s[k]==0)
             df(k,a,n,s);
      
}
void scrie(int i,int t[100])
{
     if (t[i])
        scrie(t[i],t);
     printf("%d ",i);
}

void dijkstra(int nod,int a[100][100],int n)
{
     int d[100],u[100],min,i,t[100];
     for (i=1;i<=n;i++)
      u[i]=0;
      for (i=1;i<=n;i++)
      d[i]=1000;
     d[nod]=0;
     while (1)
     {
           min=30000;
           nod=-1;
           for (i=1;i<=n;i++)
               if (!u[i] && min>d[i])
               {
               		min=d[i];
               		nod=i;
               }
               if (min==30000) break;
               u[nod]=1;
               for (i=1;i<=n;i++)
               if(d[i]>d[nod]+a[nod][i])
               {
                                        d[i]=d[nod]+a[nod][i];
                                        t[i]=nod;
               }
               
     }
     //scrie(4,t);
     for (i=1;i<=n;i++)
      printf("%d ",d[i]);
}


int main()
{
    int s[100],i,j,n,a[100][100];
    n=7;
    for (i=1;i<=n;i++)
      s[i]=0;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            a[i][j]=30000;
            if(i==j) a[i][j]=0;
        }
    }
    a[1][2]=2;
    a[1][4]=5;
    a[2][1]=2;
    a[2][5]=7;
    a[3][5]=4;
    a[4][1]=5;
    a[4][5]=3;
    a[5][2]=7;
    a[5][3]=4;
    a[5][4]=3;
    a[5][6]=6;
    a[5][7]=3;
    a[6][5]=6;
    a[6][7]=2;
    a[7][5]=3;
    a[7][6]=2;
    
    dijkstra(4,a,n);
    printf("\n\n");
    df(4,a,n,s);
    printf("\n\n");
    bf(4,a,n);
    printf("\n\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            printf("%d ",a[i][j]);
            
        }
        printf("\n");
    }
    getch();
    return 0;
}
