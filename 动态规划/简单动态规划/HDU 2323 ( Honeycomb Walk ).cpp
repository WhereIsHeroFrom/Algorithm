#include <iostream>
using namespace std;
int direven[6][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, 1}, {1, 1}};
int dirodd[6][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, -1}};

int t, a, i, n, tx, ty;
int map[30][30];
int dp[30][30][15];
int dfs(int sx, int sy, int num)
{
    int i, tpx, tpy;
    if(num == 0)
    {
        
        if(sx == tx && sy == ty)
            return 1;        
        else
            return 0;
    }
    int sum = 0;
    for(i = 0; i < 6; i++)
    {
        if(sx & 1)
        {
            tpx = sx + direven[i][0];
            tpy = sy + direven[i][1];
        }else
        {
            tpx = sx + dirodd[i][0];
            tpy = sy + dirodd[i][1];
        }

        if(dp[tpx][tpy][num-1] == -1)
            dp[tpx][tpy][num-1] = dfs(tpx, tpy, num-1);
        sum += dp[tpx][tpy][num-1];
    }
    return sum;
}
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        memset(dp, -1, sizeof(dp));
        tx = 15;
        ty = 16;
        printf("%d\n", dfs(15, 15, n-1)*6);
    }
}

/*
14
1
2
3
4
5
6
7
8
9
10
11
12
13
14
*/

/*
0
6
12
90
360
2040
10080
54810
290640
1588356
8676360
47977776
266378112
1488801600
*/
