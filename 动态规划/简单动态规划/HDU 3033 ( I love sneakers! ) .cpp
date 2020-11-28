/*

K种物品，第i中物品有Ai件，要求每种物品至少取一件，并且使得总容量在某个上限之内，求最大价值。


设DP[0][i]表示未取当前物品时总容量为i时的最大价值，
DP[1][i]表示取了当前物品时总容量为i时的最大价值，
对于每中物品，初始化
DP[0][j] = DP[1][j];      // 未取当前物品时的价值等于前一种物品取的时候的价值
DP[1][j] = inf;           // 取当前物品时的价值无穷大，稍后更新
然后每次做背包就好了，避免重复，采用逆序。

*/

#include <iostream>
 
using namespace std;
 
#define inf -100000000
 
int n, m, K;
 
struct point {
    int pack;
    int val;
}p[ 11 ][ 110 ];
int size[ 11 ];
 
int DP[ 2 ][ 10001 ], pre;
 
int main() {
 
    int A, B, C;
    int i, j, k;
 
    while( scanf("%d %d %d", &n, &m, &K ) != EOF ) {

        for(i = 1; i <= K; i++)
            size[i] = 0;

        for(i = 1; i <= n; i++) {
            scanf( "%d %d %d", &A, &B, &C );
            p[A][ ++size[A] ].pack = B;
            p[A][ size[A] ].val = C;
        }
 
        for(i = 0; i <= m; i++) {
            DP[1][i] = inf;
        }
        DP[1][0] = 0;

        for(i = 1; i <= K; i++) {

            for( j = 0; j <= m; j++) {
                DP[0][j] = DP[1][j];
                DP[1][j] = inf;
            }

            for( k = 1; k <= size[i]; k++ ) {

                for( j = m; j >= p[i][k].pack ; j -- ) {

                    if( DP[0][ j-p[i][k].pack ] != inf ) {
                        if( DP[0][ j-p[i][k].pack ] + p[i][k].val > DP[1][j] ) {
                            DP[1][j] = DP[0][ j-p[i][k].pack ] + p[i][k].val;
                            if( !p[i][k].pack )
                                continue;
                        }
                    }


                    if( DP[1][ j-p[i][k].pack ] != inf ) {
                        if( DP[1][ j-p[i][k].pack ] + p[i][k].val > DP[1][j] )
                            DP[1][j] = DP[1][ j-p[i][k].pack ] + p[i][k].val;
                    }
                }

            }
        }


        int Max = -1;
 
        for( i = 0; i <= m; i++) {
            if( DP[1][i] > Max )
                Max = DP[1][i];
        }
 
        if( Max == -1 )
            printf("Impossible\n");
        else
            printf("%d\n", Max );
    }
    return 0;
}
 
/*
3 5 2
1 2 2
1 3 10
2 3 2
 
1 100 2
1 0 0
 
1 100 1
1 0 0
 
1 100 1
1 0 1000

2 4 2
1 3 3
2 2 100

3 10000 3
1 4 6
2 5 7
3 4 99

4 0 4
1 0 0
2 0 0
3 0 0
4 0 0

4 0 5
2 0 0
3 0 0
4 0 0
5 0 0

4 0 4
1 0 10
2 0 10000
3 0 10
4 0 10
*/


