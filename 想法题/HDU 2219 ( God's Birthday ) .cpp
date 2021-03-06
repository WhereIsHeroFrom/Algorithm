#include <iostream>

using namespace std;

struct point {
    int mon, day;
}D[ 400 ];

int M[40][40];
int n, m, d, j;

int main() {
    int t;
    int i;
    scanf("%d", &t );

    while( t-- ) {
        scanf( "%d %d %d", &n, &m, &d );

        memset( M, 0, sizeof( M ));
        for( i = 1; i <= n; i ++ ) {
            scanf("%d %d", &D[i].mon, &D[i].day );
            M[ D[i].mon ][ D[i].day ] = 1;
        }
        int flag = -1;
        int first = 0;
        int Now = 1;

        while( first < 2000 && Now ) {
            
            Now = 0;
            int Count;
            int ans;

            if( first++ ) {
                // 男的根据女的话推断出

                for( i = 1; i <= 31; i ++ ) {
                    Count = 0;
                    for( j = 1; j <= 12; j ++ ) {
                        if( M[j][i] ) {
                            Count ++;
                            ans = j;
                        }
                    }
                    if( Count == 1 ) {
                        M[ ans ][i] = 0;
                        Now = 1;
                    }
                }
            }

            // 男的来算算看
            Count = 0;
            for( i = 1; i <= 31; i ++ ) {
                if( M[m][i] ) {
                    Count ++;
                    ans = i;
                }
            }
            if( Count == 1 && ans == d ) {
                flag = 0;
                break;
            }

            // 女的根据男的话推断出

            for( i = 1; i <= 12; i ++ ) {
                Count = 0;
                for( j = 1; j <= 31; j ++ ) {
                    if( M[i][j] ) {
                        Count ++;
                        ans = j;
                    }
                }
                if( Count == 1 ) {
                    M[i][ ans ] = 0;
                    Now = 1;
                }
            }

            // 女的来算算看
            Count = 0;
            for( i = 1; i <= 12; i ++ ) {
                if( M[i][d] ) {
                    Count ++;
                    ans = i;
                }
            }
            if( Count == 1 && ans == m ) {
                flag = 1;
                break;
            }
        }

        if( flag == 0 )
            printf("Wiskey Win\n");
        else if( flag == 1 )
            printf("Michelle Win\n");
        else
            printf("No\n");
    }
    return 0;
}

/*
7 12 25
12 23
12 24
12 25
11 23
11 25
10 25
10 6
*/

