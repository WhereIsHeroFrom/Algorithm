#include <iostream>

using namespace std;


int map[20][20];
int Max, m, n;
void dfs(int op, int sum1, int sum2, int sum3, int cur)
{
    int i;
    
    if(op == n + 1)
    {
        //printf("%d %d %d %d\n", sum1, sum2, sum3, cur);
        if(Max == -1 || Max < cur)
            Max = cur;
        return ;
    }
    if(Max == n)
        return;
    dfs(op + 1, sum1, sum2, sum3, cur);
    if(map[1][op] != -1)
    {
        if(sum1 + map[1][op] <= m)
            dfs(op + 1, sum1+ map[1][op], sum2, sum3, cur + 1);
    }
    if(map[2][op] != -1)
    {
        if(sum2 + map[2][op] <= m)
            dfs(op + 1, sum1, sum2+ map[2][op], sum3, cur + 1);
    }
    if(map[3][op] != -1)
    {
        if(sum3 + map[3][op] <= m)
            dfs(op + 1, sum1, sum2, sum3+ map[3][op], cur + 1);
    }
}

int main()
{
    int t, i, j;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        for(i = 1; i <= 3; i++)
        {
            for(j = 1; j <= n; j++)
            {
                scanf("%d", &map[i][j]);
            }
        }
        Max = -1;
        dfs(1, 0, 0, 0, 0);
        printf("%d\n", Max);
    }
}

