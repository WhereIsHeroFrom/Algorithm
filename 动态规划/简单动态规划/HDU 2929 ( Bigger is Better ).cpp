#include <iostream>

using namespace std;
int all[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

struct point {
    __int64 ans[4];
    int len;
} dp[ 110 ][ 3010 ], temp;

int cmp( point a, point b ) {
    int i;

    if( a.len > b.len ) {
        return 1;
    }
    if( a.len < b.len ) {
        return -1;
    }

    for( i = a.len - 1; i >= 0; i--) {
        if( a.ans[i] > b.ans[i] )
            return 1;
        if( a.ans[i] < b.ans[i] )
            return -1;
    }
    return 0;
}

__int64 E17() {
    return ( ( __int64 )100000000 ) * ( ( __int64 )1000000000 );
}

int main() {

    __int64 n, m;
    __int64 i, j, k, l;
    
    int t = 1;

    while( scanf("%I64d", &n) != EOF && n) {
        scanf("%I64d", &m);

        for(i = 0; i <= n; i++) {
            for(j = 0; j < m; j++) {
                dp[i][j].len = -1;
            }
        }
        dp[0][0].len = 0;


        for(i = 0; i <= n; i++) {
            for(j = 0; j < m; j++) {
                for(k = 0; k < 10; k++) {
                    if( dp[i][j].len != -1 ) {
                        if( i + all[k] <= n ) {

                            int nexi = i + all[k];


                            if( k == 0 && dp[i][j].len == 0 ) {
                                
                                temp.ans[0] = 0;
                                temp.len = 1;

                                if( cmp( temp, dp[ nexi ][ 0 ] ) == 1 ) 
                                    dp[ nexi ][ 0 ] = temp;

                            }else {
                                int nexj = ( ( j * 10 ) + k ) % m;

                                for(l = 0; l < dp[i][j].len; l++) {
                                    temp.ans[l] = dp[i][j].ans[l];
                                }
                                for(l = dp[i][j].len; l < 3; l++) {
                                    temp.ans[l] = 0;
                                }

                                for(l = 0; l < 3; l++) {
                                    temp.ans[l] *= ( __int64 )10;
                                }
                                temp.ans[0] += k;

                                for(l = 0; l < 3; l++) {
                                    if( temp.ans[l] >= E17() ) {
                                        temp.ans[l+1] += temp.ans[l] / E17();
                                        temp.ans[l] %= E17();
                                    }
                                }

                                for(l = 2; l >= 0; l-- ) {
                                    if( temp.ans[l] ) {
                                        temp.len = l + 1;
                                        break;
                                    }
                                }

                                if( cmp( temp, dp[ nexi ][ nexj ] ) == 1 ) {
                                    dp[ nexi ][ nexj ] = temp;
                                }
                            }
                        }
                    }
                }

            }
        }    
        
        
        printf("Case %d: ", t++ );
        point a;
        a.len = 0;

        for(i = 1; i <= n; i++) {
            if( dp[i][0].len != -1 ) {
                if( cmp( dp[i][0], a ) == 1 ) {
                    a = dp[i][0];
                }
            }
        }

        if(a.len == 0 )
            printf("-1\n");
        else {

            printf("%I64d", a.ans[ a.len-1 ] );
            for( i = a.len-2; i >= 0; i-- ) {
                printf("%017I64d", a.ans[i]);
            }
            puts("");
        }
    }
    return 0;
}
