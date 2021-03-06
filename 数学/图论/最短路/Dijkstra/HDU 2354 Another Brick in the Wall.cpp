#include <iostream>

using namespace std;


int t, n, m;
char map[21][21];
int cost[1001][1001];
int u, v;
int d[1001];
bool s[1001];

int mincost(int u, int n)
{

    int i;
    for(i = 0; i < n; i++)
    {
        d[i] = cost[u][i];
        s[i] = false;
        //printf("d[%d] = %d\n", i, d[i]);
    }   
    d[u] = 0;
    s[u] = true;

    while(1)
    {
        int Min = 999999;
        int u = -1;

        for(i = 0; i < n; i++)
        {
            if(!s[i] && d[i] < Min)
            {
                Min = d[i];
                u = i;
            }
        }
        if(u == -1)
            break;
        s[u] = true;
        for(i = 0; i < n; i++)
        {
            if(!s[i] && cost[i][u] + d[u] < d[i])
            {
                d[i] = cost[i][u] + d[u];
            }
        }
    }

    int Min = 999999;
    for(i = 0; i < m; i++)
    {
        if(d[(n/m-1)*m + i] < Min)
            Min = d[ (n/m-1)*m + i];
    }
    return Min;
}

int i, j;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n ; i++)
            scanf("%s", map[i]);
        for(i = 0; i <= 600; i++)
            for(j = 0; j <= 600; j++)
                cost[i][j] = 999999;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {                    
                u = i * m + j;
                v = i * m + j + 1;
                if(map[i][j] == map[i][j+1])
                {
                    cost[u][v] = cost[v][u] = 0;
                }else
                    cost[u][v] = cost[v][u] = 1;

                u = i * m + j;
                v = (i+1) * m + j;
                if(map[i][j] == map[i+1][j])
                {
                    cost[u][v] = cost[v][u] = 0;
                }else
                    cost[u][v] = cost[v][u] = 1;
            }
        }
        int Min = 999999;
        for(i = 0; i < m ;i++)
        {
            int ty = mincost(i, n*m);
            if( ty < Min )
                Min = ty;
        }
        printf("%d\n", Min + 1);
    }
}
