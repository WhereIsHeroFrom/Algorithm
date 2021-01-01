#include <iostream>
#include <algorithm> 
using namespace std;
int map[51][51];
int visit[51];
int pre[51];
int n, k, a[51];
int dfs(int t)
{
    int i;
    int buf;
    for(i = 0; i < n;i++)
    {
        if(map[t][i] && !visit[i])
        {
            visit[i]=1;
            buf=pre[i];
            pre[i]=t;
            if(buf==-1||dfs(buf))
                return 1;
            pre[i]=buf;


        }
    }
    return 0;
}
int Max;
int i, j;
int main()
{
    while(scanf("%d%d", &n, &k) != EOF)
    {
        if(!n && !k)
            break;
        memset(map, 0, sizeof(map));
        memset(pre, -1, sizeof(pre));
        for(i = 0;i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        sort(a, a+n);
        
        for(i = 0; i < n; i++)
        {
            for(j = i+1;j < n; j++)
            {
                if(a[j] % a[i] == 0 && a[j]/a[i] == k)
                {
                    map[j][i] = map[i][j] = 1;
                }
            }
        }
        Max = 0;
        for(i = 0; i < n; i++)
        {
            memset(visit, 0, sizeof(visit));
            if(dfs(i))Max++;
        }
        printf("%d\n", Max/2);

    }
}

