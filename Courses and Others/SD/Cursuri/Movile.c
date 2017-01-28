#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int stergere(int* v,int* n)
{
    int aux,i=1,x;
    x=v[1];
    v[1]=v[(*n)];
    (*n)--;
    while (i<=(*n))
    {
          if((2*i+1)<=(*n))
          {
                           if (v[i]>=v[2*i+1]&& v[i]>=v[2*i])
                              break;
                           if (v[i]<v[2*i]&&v[2*i+1]<=v[2*i])
                           {
                                           aux=v[i];
                                           v[i]=v[2*i];
                                           v[2*i]=aux;
                                           i=2*i;
                           }
                           else
                           if (v[i]<v[2*i+1]&&v[2*i]<=v[2*i+1])
                           {
                                           aux=v[i];
                                           v[i]=v[2*i+1];
                                           v[2*i+1]=aux;
                                           i=2*i+1;
                                              
                           }
                           
          }
          else
          {
              if (v[i]<v[2*i])
              {
                 aux=v[i];
                 v[i]=v[2*i];
                 v[2*i]=aux;
                 i=2*i;
              }
              if (v[i]>=v[2*i])
                 break;
          }
    //if (i==(*n))
      // break;
    }
    return x;
}
int main()
{
    int i,n,j,v[40],ok,aux,k;
    //scanf("%d",&n);
    n=9;
    v[1]=16;
    v[2]=21;
    v[3]=3;
    v[4]=14;
    v[5]=15;
    v[6]=9;
    v[7]=8;
    v[8]=4;
    v[9]=24;
    for (i=1;i<=n;i++)
    {
        //scanf("%d",&v[i]);
        k=i;
        while (k/2>=1)
        {
              if (v[k]>v[k/2])
              {
                              aux=v[k];
                              v[k]=v[k/2];
                              v[k/2]=aux;
              }
              else
                  break;
              k=k/2;
        }
    }
    printf("\n");
    for (i=1;i<=n;i++)
    {
        printf("%d ",v[i]);
    }
    printf("\n");
    aux=n;
    for (i=1;i<=aux;i++)
    {
        printf("%d ",stergere(v,&n));
        /*for (j=1;j<=n;j++)
        {
            printf("%d ",v[j]);
        }*/
    }
    getch();
    return 0;
    
}
