#include <iostream>

using namespace std;

int n, m, i, j, k;
char map[1000][1000];
double dp[1001][1000];
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n ;i++)
            scanf("%s", map[i]);
        
        double sum = -999999999;
        
        for(i = 0; i < m; i++)
        {
            
            for(j = 0; j < n; j++)
            {
                for(k = 0; k < m; k++)
                    dp[j][k] = 0;
            }
            dp[0][i] = 1;
            
            for(j = 1; j < n; j++)
            {
                for(k = 0; k < m; k++)
                {
                    if(map[j][k] == '*')
                    {
                        dp[j][k-1] += dp[j-1][k] / 2;
                        dp[j][k+1] += dp[j-1][k] / 2;
                    }
                    if(map[j-1][k] == '.')
                    {
                        dp[j][k] += dp[j-1][k];
                    }
                }        
                
            }
            double zong = 0;
            for(j = 0; j < n; j++)
            {
                for(k = 0; k < m; k++)
                {
                    if(map[j][k] >= '1' && map[j][k] <= '9')
                    {
                         zong += dp[j][k] * (map[j][k] - '0');
                    }
                }
                
            }
            if(zong > sum)
                sum = zong;
        }
        printf("%.7lf\n", sum);
    }
}
 

