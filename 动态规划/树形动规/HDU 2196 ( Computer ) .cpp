#include <iostream>
#include <vector>
#define M 0
using namespace std;
vector <vector<int> > map;

struct point
{
    int Lgst;
    int LgN;
    int Lger;
    int LgM;

}dp[10001];

int w[10001];
int n;
inline int Max(int a, int b)
{
    return a > b ? a : b;
}
void dfs(int u)
{
    int i, v;
    if(map[u].size() == 0)
        return;
    for(i = 0; i < map[u].size(); i++)
    {
        v = map[u][i];
        if(dp[v].Lgst == M)
            dfs(v);
    }
    for(i = 0; i < map[u].size(); i++)
    {
        v = map[u][i];
        if(dp[v].Lgst + w[v] >= dp[u].Lgst)
        {
             dp[u].Lgst = dp[v].Lgst + w[v];
             dp[u].LgN = v;
        }    
    }
    for(i = 0; i < map[u].size(); i++)
    {
        v = map[u][i];
       if(dp[v].Lgst + w[v] >= dp[u].Lger && v != dp[u].LgN)
       {
           dp[u].Lger = dp[v].Lgst + w[v];
           dp[u].LgM = v;
       }
    }

}

void DFS(int u)
{
    int i, v;

    for(i = 0; i < map[u].size(); i++)
    {
        v = map[u][i];
        if(dp[u].LgN != v)
        {
            if(dp[v].Lgst <= dp[u].Lgst + w[v])
            {
                dp[v].Lger = dp[v].Lgst;
                dp[v].LgM = dp[v].LgN;

                dp[v].Lgst = dp[u].Lgst + w[v];
                dp[v].LgN = u;
            }
        }else
        {
            if(dp[v].Lgst <= dp[u].Lger + w[v] )
            {
                dp[v].Lger = dp[v].Lgst;
                dp[v].LgM = dp[v].LgN;

                dp[v].Lgst = dp[u].Lger + w[v];
                dp[v].LgN = u;
            }else
            {
                if(dp[v].Lger <= dp[u].Lger + w[v])
                {
                    dp[v].Lger = dp[u].Lger + w[v];
                    dp[v].LgM = u;
                }
            }
        }
        DFS(v);
    }    
}

int main()
{
    int i, a, l;
    while(scanf("%d", &n) != EOF)
    {
        map.clear();
        map.resize(n+1);
        for(i = 0; i <= 10000; i++)
        {
            dp[i].Lgst = M;
            dp[i].Lger = M;
            dp[i].LgN = M;
            dp[i].LgM = M;
        }
        for(i = 2; i <= n; i++)
        {
            scanf("%d%d", &a, &l);
            map[a].push_back(i);
            w[i] = l;
        }    
        dfs(1);
        printf("%d\n", dp[1].Lgst);
        DFS(1);
        for(i = 2; i <= n; i++)
            printf("%d\n", dp[i].Lgst);
    }
}
