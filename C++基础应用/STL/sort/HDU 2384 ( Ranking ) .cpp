#include <iostream>

using namespace std;


struct problem
{
    int Accepted;
    int Rejected;
    int Time;      //AC时刻
    int SumTime;   //包括罚时
};

struct point
{
    char name[100];
    int hash[20];
    int num;
    problem pro[20];
    int pro_AC_order[20];
    int TimeSum;
}p[200];

int t, n, rank;

int FindNum(char *ch)
{
    int i;
    for(i = 0; i < n; i++)
        if(strcmp(p[i].name, ch) == 0)
            return i;
}

int cmp(const void *a, const void *b)
{
    int i;
    point *c = (point *)a;
    point *d = (point *)b;
    if(c->num != d->num)
        return -(c->num - d->num);
    else if(c->TimeSum != d->TimeSum)
        return c->TimeSum - d->TimeSum;
    else 
    {
        for(i = c->num-1; i >= 0; i--)
        {
            int v = c->pro_AC_order[i];
            int u = d->pro_AC_order[i];

            if(c->pro[v].SumTime != d->pro[u].SumTime)
                return c->pro[v].SumTime - d->pro[u].SumTime;
            else if(c->pro[v].Time != d->pro[u].Time)
                return c->pro[v].Time - d->pro[u].Time;
        }
        return strcmp(c->name, d->name);
    }
    
}
int main()
{
    int i, j;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &rank);
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < 20; j++)
                p[i].hash[j] = 0;
            p[i].num = 0;
            p[i].TimeSum = 0;
            for(j = 0; j < 20; j++)
            {
                p[i].pro[j].Accepted = 0;
                p[i].pro[j].Rejected = 0;
                p[i].pro[j].SumTime = p[i].pro[j].Time = 0;
            }
        }
        for(i = 0; i < n; i++)
            scanf("%s", p[i].name);

        while(rank --)
        {
            char name[23], ti[5], state[20];
            int tt;
            scanf("%d %s %s %s", &tt, name, ti, state);
            int num = FindNum(name);
            if(!p[num].hash[ ti[0]-'A' ])
            {
                if(strcmp(state, "rejected") == 0)
                {
                    p[num].pro[ ti[0]-'A' ].Rejected ++;
                }else
                {
                    p[num].hash[ ti[0]-'A' ] = 1;
                    p[num].pro[ ti[0]-'A' ].Time = tt;
                    p[num].pro_AC_order[ p[num].num++ ] = ti[0] - 'A';
                }
            }
        }

        for(i = 0; i < n; i++)
        {
            int v;
            for(j = 0; j < p[i].num; j++)
            {    
                
                v = p[i].pro_AC_order[j];
                if(j == 0)
                {
                    p[i].pro[v].SumTime = p[i].pro[v].Time + p[i].pro[v].Rejected * 20;
                }else
                {    
                    int u = p[i].pro_AC_order[j-1];
                    p[i].pro[v].SumTime = p[i].pro[v].Time + p[i].pro[v].Rejected * 20;
                    p[i].pro[v].SumTime += p[i].pro[u].SumTime;
                }
            }
            p[i].TimeSum = p[i].pro[v].SumTime;
        }
        qsort(p, n, sizeof(point), cmp);
        int ran = 1;
        for(i = 0; i < n; i++)
        {
            if(i == 0)
            {
                printf("1 %s %d %d\n", p[i].name, p[i].num, p[i].TimeSum);
            }else
            {
                if(p[i].num != p[i-1].num || p[i].TimeSum != p[i-1].TimeSum)
                {
                    printf("%d %s %d %d\n", i+1, p[i].name, p[i].num, p[i].TimeSum);
                    ran = i+1;
                }else
                {
                    for(j = p[i].num-1; j >= 0; j--)
                    {
                        int v = p[i].pro_AC_order[j];
                        int u = p[i-1].pro_AC_order[j];
                        if(p[i].pro[v].SumTime != p[i-1].pro[u].SumTime)
                            break;
                        if(p[i].pro[v].Time != p[i-1].pro[u].Time)
                           break;
                    }

                    if(j == -1)
                    {
                        printf("%d %s %d %d\n", ran, p[i].name, p[i].num, p[i].TimeSum);
                    }else
                    {
                        printf("%d %s %d %d\n", i+1, p[i].name, p[i].num, p[i].TimeSum);
                        ran = i+1;
                    }
                }
            }

        }
        
        /*for(i = 0; i < n; i++)
        {
            printf("%s", p[i].name);
            for(j = 0; j < p[i].num; j++)
            {
                int v = p[i].pro_AC_order[j];
                printf(" %d %d\n", p[i].pro[v].SumTime, p[i].pro[v].Time);
            }
        }*/
    }
}
