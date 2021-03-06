#include <iostream>

using namespace std;
__int64 a[1000], n, e;
__int64 dp[101][101];
int main()
{
    __int64 i, j, k;
    while(scanf("%I64d %I64d", &n, &e) != EOF)
    {
        if(!n && !e)
            break;
        for(i = 0; i < n; i++)
        {
            scanf("%I64d", &a[i]);
        }

        memset(dp, 0, sizeof(dp));

        for(i = 0; i < n; i++)
            dp[1][i] = 1;

        for(i = 1; i < n; i++)
        {
            for(j = 0; j < i; j++)
            {
                for(k = 2; k <= n; k++)
                {
                    if(a[i] > a[j])
                    {
                        dp[k][i] += dp[k-1][j];
                    }
                }
            }
        }

        __int64 sum = 0;
        for(i = 0; i < n; i ++)
            sum += dp[e][i];
        printf("%I64d\n", sum);

    }
}
