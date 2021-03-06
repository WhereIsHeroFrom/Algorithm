#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct point
{
    int UnVisited;
    int IsVisited;
    int xuan;
}dp[201];

map < string, int > Map;
vector < int > vec[201];

int n, i, j, Max;
int T, u, v;
int visit[201], hash[201];
int rt[2];

string str;

int Maximun(int a, int b)
{
    return a > b ? a : b;
}

point dfs(int u, int mode)
{
    point ty;
    ty.IsVisited = ty.UnVisited = 0;

    if(visit[u] && hash[u])
        ty.IsVisited = -1000000;

    int i, size = vec[u].size();
    if(!size)
    {
        ty.IsVisited = 1;
        ty.UnVisited = 0;
        if(visit[u] && hash[u])
             ty.IsVisited = -1000000;
        return ty;
    }

    for(i = 0; i < size; i++)
    {
        int v = vec[u][i];

        if(dp[v].IsVisited == -1)
            dp[v] = dfs(v, mode);

        ty.IsVisited += dp[v].UnVisited;
        ty.UnVisited += Maximun(dp[v].IsVisited, dp[v].UnVisited);
    }
    ty.IsVisited ++;
    return ty;
}

void DFS(int u)
{
    int i, size = vec[u].size();
    for(i = 0; i < size; i++)
    {
        int v = vec[u][i];
        if(dp[u].xuan == 1)
            dp[v].xuan = 0;
        else
        {
            if(dp[v].UnVisited > dp[v].IsVisited)
                dp[v].xuan = 0;
            else
            {
                dp[v].xuan = 1;
                visit[v] = 1;
            }
        }
        DFS(v);
    }
}
int main()
{
    while(scanf("%d", &n) != EOF && n)
    {
        Map.clear();
        for(i = 1; i <= n; i++)
        {
            vec[i].clear();
            dp[i].IsVisited = -1;
            dp[i].xuan = 0;
        }
        memset(hash, 0, sizeof(hash));
        memset(visit, 0, sizeof(visit));

        T = 1;
        cin >> str;
        Map[str] = T++;

        for(i = 0; i < n - 1; i++)
        {
            cin >> str;
            if(!Map[str])
                v = Map[str] = T++;
            else
                v = Map[str];

            cin >> str;
            if(!Map[str])
                u = Map[str] = T++;
            else
                u = Map[str];
            vec[u].push_back(v);
        }

        dp[1] = dfs(1, 0);

        Max = dp[1].IsVisited > dp[1].UnVisited ? dp[1].IsVisited : dp[1].UnVisited;

        if(Max == dp[1].IsVisited)
        {
            dp[1].xuan = 1;
            visit[1] = 1;
        }
        DFS(1);

        for(i = 1; i <= n; i++)
        {
            if(visit[i])
            {
                hash[i] = 1;
                for(j = 1; j <= n; j++)
                    dp[j].IsVisited = -1;
                dp[1] = dfs(1, 0);
                hash[i] = 0;
                int m = dp[1].IsVisited > dp[1].UnVisited ? dp[1].IsVisited : dp[1].UnVisited;
                if(m == Max)
                    break;
            }
        }

        printf("%d ", Max);
        if(i > n)
            printf("Yes\n");
        else
            printf("No\n");
    }
}

