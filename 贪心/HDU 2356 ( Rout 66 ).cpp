#include<iostream>
#include<cmath>

using namespace std;

struct node
{
    int D;
    int J;
    int S;
}f[2000];

int n;

int cmp(const void *a,const void *b)
{
    return (*(node *)a).D - (*(node *)b).D;
}

int ch(int st)
{
    int i, F, B;
    double ER;
    for(i=1; i<=n; i++)
    {
        F=st*f[i].D, B=f[i].J*f[i].S*f[i].S;
        if(F <= B)
            return 0;

        ER=1.0 - B*1.0/F;

        ER=((st*1.0)*ER + 0.50);

        st = (int)ER;
    }
    return 1;
}

int main()
{
    int t;
    int i;
    int st;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i = 1; i <= n; i++)
        {
            scanf("%d %d %d",&f[i].D,&f[i].J,&f[i].S);
        }

        scanf("%d", &st);

        qsort(f+1,n,sizeof(f[0]),cmp);    

        f[0].D = 0;

        for(i = n; i >= 1; i--)
            f[i].D -= f[i-1].D;

        if(ch(st))
            printf("ROUT!\n");
        else
            printf("RETREAT!\n");
    }
    return 0;
}
