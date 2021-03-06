#include <iostream>

using namespace std;

struct point
{
    int x;
    int y;
}p[100000];
int zong;

int Max(int a, int b)
{
    return a > b ? a : b;
}
int dp[10000][16][16];

int main()
{
    int top = 1, i, j, k, t;
    while(scanf("%d %d", &p[top].x, &p[top].y) != EOF)
        top++;
    dp[1][1][0] = p[1].x;
    dp[1][0][1] = p[1].y;

    for(i = 2; i < top; i++)
    {
        for(j = 0; j <= i && j <= 15; j++)
        {
            for(k = 0; k + j <= i && k <= 15; k++)
            {
                if(i-1 >= j+k)
                    dp[i][j][k] = dp[i-1][j][k];
                if(k >= 1)
                    dp[i][j][k] = Max(dp[i][j][k], dp[i-1][j][k-1] + p[i].y);
                if(j >= 1)
                    dp[i][j][k] = Max(dp[i][j][k], dp[i-1][j-1][k] + p[i].x);
            }
        }
    }

    printf("%d\n", dp[top-1][15][15]);
    return 0;
}
