#include <iostream>

using namespace std;
int t, n, m;
int map[1001][1001];
int dp[1001][1001];
int i, j, c = 1;
int Max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++)
            for(j = 1; j <= m; j++)
                scanf("%d", &map[i][j]);

        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m; j++)
            {
                if(i == 1 && j == 1)
                    dp[i][j] = map[i][j];
                else if(i == 1)
                    dp[i][j] = map[i][j] + dp[i][j-1];
                else if(j == 1)
                    dp[i][j] = map[i][j] + dp[i-1][j];
                else 
                {
                    dp[i][j] = map[i][j] + Max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        printf("Scenario #%d:\n", c++);
        printf("%d\n\n", dp[n][m]);

    }
}
