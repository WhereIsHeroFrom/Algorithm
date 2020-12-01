#include <iostream>

using namespace std;

struct point
{
    int u;
    int v;
    int value;
}p[300000];
int t;
int top;
int dis[20001];
int m, n, a, b, c, d, i;

void bellman()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        int flag = 0;
        for(j = 0; j < top; j++)
        {
            if(dis[ p[j].u] + p[j].value < dis[p[j].v])
            {
                flag = 1;
                dis[p[j].v] = dis[ p[j].u] + p[j].value;
                //printf("%d %d\n", p[j].v, dis[p[j].v]);
            }
        }
        if(!flag)
            return;
    } 
}
int main()
{
    int s = 1;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        memset(dis, 0, sizeof(dis));
        for(i = 0; i < n; i++)
            scanf("%d", &dis[i]);
        top = 0;
            
        while(m--)
        {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            p[top].u = a;
            p[top].v = b;
            p[top].value = c;
            
            top++;
            
            p[top].u = b;
            p[top].v = a;
            p[top].value = d;
            top++;
        }
        bellman();
        int Max = -1;
        int u = -1;
        for(i = 0; i < n; i++)
        {
            //printf("%d\n", dis[i]);
            if(dis[i] > Max )
            {
                Max = dis[i];
                u = i;
            }
        }
        printf("Scenario #%d:\n", s++);
        printf("%d\n\n", u);
        
    }
}
