#include <iostream>

using namespace std;

int t;
__int64 dp[100][100];
__int64 hash[100];
char str[1000];
int n, m, p, i, j ,k;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        memset(hash, 0, sizeof(hash));
        scanf("%d%d%d", &m, &n, &p);
        for(i = 0; i < m; i++)
        {
            scanf("%s", str);
            hash[ strlen(str) ] ++;
        }

        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= 50; j++)
            {
                for(k = 1; k <= j; k++)
                {
                    if(hash[k])
                    {
                        dp[i][j] += dp[i-1][j-k] * hash[k]; 
                    }
                }
            }
        }
        while(p--)
        {
            int yu;
            scanf("%d", &yu);
            printf("%I64d\n", dp[n][yu]);
        }
    }
}
