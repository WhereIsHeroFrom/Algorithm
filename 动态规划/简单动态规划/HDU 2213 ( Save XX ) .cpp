#include <iostream>

using namespace std;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m, t;
char map[112][112];
__int64 dp[30][111][111];
int i, j, k, tx, ty;
int dx, dy;
int main()
{
    while(scanf("%d%d%d", &n, &m, &t) != EOF)
    {
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        
        memset(dp, 0, sizeof(dp));
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m ; j++)
            {
                if(map[i][j] == 'S')
                {
                    dp[0][i][j] = 1;
                }else
                    dp[0][i][j] = 0;

                if(map[i][j] == 'E')
                {
                    dx = i;
                    dy = j;
                }
            }
        }


        for(int ti = 1; ti <= t; ti++)
        {
            for(i = 0; i < n; i++)
            {
                for(j = 0; j < m; j++)
                {                        
                    dp[ti][i][j] = dp[ti-1][i][j];

                    for(k = 0; k < 4; k++)
                    {
                        tx = i + dir[k][0];
                        ty = j + dir[k][1];
                        if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                            continue;
                        if(map[tx][ty] != 'X')
                             dp[ti][i][j] += dp[ti-1][tx][ty];
                    }
                }
            }
        }

        for(i = 0; i <= t; i++)
        {
            if(dp[i][dx][dy])
            {
                break;
            }
        }
        if(i < t)
            printf("%I64d\n", dp[t-1][dx][dy]);
        else if(i == t)
            printf("Oh, my god, bad luck!\n");
        else
            printf("God will bless XX and WisKey!\n");

    }
}
