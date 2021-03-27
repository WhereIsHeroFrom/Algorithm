#include <iostream>

using namespace std;

#define ll long long
ll dir[3] = { -1, 0, 1 };
ll map[1001][1001];
ll dp[1001][1001];
ll n, m;
ll dfs(ll x, ll y)
{
    ll tx;
    if (y == m - 1)
        return map[x][y];
    ll Min = INT_MIN;
    ll i;
    for (i = 0; i < 3; i++)
    {
        tx = (x + dir[i] + n) % n;
        if (dp[tx][y + 1] == INT_MIN)
            dp[tx][y + 1] = dfs(tx, y + 1);

        if (Min == INT_MIN || map[x][y] + dp[tx][y + 1] < Min)
            Min = map[x][y] + dp[tx][y + 1];
    }
    return Min;
}
int main()
{
    ll i, j, k;
    while (scanf("%I64d %I64d", &n, &m) != EOF)
    {
        for (i = 0; i < 1000; i++)
            for (j = 0; j < 1000; j++)
                dp[i][j] = INT_MIN;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                scanf("%I64d", &map[i][j]);
            }
        }
        ll Min = INT_MAX;
        int rt = 0;
        for (j = 0; j < n; j++)
        {
            dp[j][0] = dfs(j, 0);
            if (dp[j][0] < Min)
            {
                Min = dp[j][0];
                rt = j;
            }
        }
        /*for(i = 0; i < n; i++)
        {
        for(j = 0; j < m; j++)
        printf(" %I64d", dp[i][j]);
        puts("");
        }*/
        ll x = 0, y = 0;
        ll tx = 0, bufx;
        x = rt, y = 0;
        for (i = 0; i < m; i++)
        {
            if (i)
                printf(" ");
            printf("%I64d", x + 1);
            bufx = 1000000;
            for (k = 0; k < 3; k++)
            {
                tx = (x + dir[k] + n) % n;
                if (tx < bufx && dp[x][i] - dp[tx][i + 1] == map[x][i])
                {
                    bufx = tx;
                }
            }
            x = bufx;
        }
        puts("");
        printf("%I64d\n", dp[rt][0]);
    }
}