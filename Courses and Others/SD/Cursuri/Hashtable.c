#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int a[20][100],b[20][100],i,n,n1,s,j;
    for (i=0;i<20;i++)
    {
        for (j=0;j<20;j++)
        {
            a[i][j]=0;
        }
    }
    for (i=0;i<6;i++)
    {
        s=0;
        scanf("%d",&n);
        n1=n;
        while (n!=0)
        {
              s=s+n%10;
              n=n/10;
        }
        for (j=0;j<100;j++)
        {
            if (a[s%20][j]==0)
            {
               a[s%20][j]=n1;
               break;
            }
        }
    }
    for (i=0;i<20;i++)
    {
        j=0;
        printf("\n");
        while (a[i][j]!=0)
        {
              printf("%d ",a[i][j]);
              j++;
        }
    }
    
    for (i=0;i<20;i++)
    {
        for (j=0;j<20;j++)
        {
            b[i][j]=0;
        }
    }
    printf("\n\n");
    int k;
    for (i=1;i<=6;i++)
    {
        for (j=1;j<=6;j++)
        {
            for(k=0;k<20;k++)
            {
                             if (b[i+j][k]==0)
                             {
                                 b[i+j][k]=i;
                                 b[i+j][k+1]=j;
                                 break;             
                             }
            }
        }
    }
    for (j=1;j<=12;j++)
    {
        i=0;
        printf("\n%d: ",j);
        while (b[j][i]!=0)
        {
              printf(" (%d %d)",b[j][i],b[j][i+1]);
              i=i+2;
        }
    }
    getch();
    return 0;
}
