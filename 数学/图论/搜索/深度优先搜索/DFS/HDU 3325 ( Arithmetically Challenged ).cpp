#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int now[4], a[4];
int hash[4];
int stack[4];
int A[ 10000 ], Bu[ 10000 ],  top;

char v[4] = { '+', '-', '*', '/' };
char b[4];

int rt( int a, char c, int b ) {
    if( c == '/' ) {
        if( b == 0 || a % b )
            return INT_MAX;
        return a / b;
    }

    if( c == '+' )
        return a + b;
    if( c == '-' )
        return a - b;
    return a * b;
}

void cal ( char A, char B, char C ) {
    int ans, ans1, ans2;

    // 1, 2, 3
    while(1) {
        ans = rt ( a[0], A, a[1] ); if( ans == INT_MAX ) break;
        ans = rt ( ans , B, a[2] ); if( ans == INT_MAX ) break;
        ans = rt ( ans,  C, a[3] ); if( ans == INT_MAX ) break;
        Bu[ top++ ] = ans;
        break;
    }


    // [ 1, 3 ], 2

    // 包括了{1, 3, 2}  {3, 1, 2}  
    while(1) {
        ans1 = rt ( a[0], A, a[1] ); if( ans1 == INT_MAX ) break;
        ans2 = rt ( a[2], C, a[3] ); if( ans2 == INT_MAX ) break;
        ans = rt( ans1, B, ans2 ); if( ans == INT_MAX ) break;
        Bu[ top++ ] = ans;
        break;
    }

    // 2, 1, 3

    while(1) {
        ans1 = rt ( a[1], B, a[2] ); if( ans1 == INT_MAX ) break;
        ans1 = rt ( a[0], A, ans1 ); if( ans1 == INT_MAX ) break;
        ans = rt ( ans1, C, a[3] ); if( ans == INT_MAX ) break;
        Bu[ top++ ] = ans;
        break;
    }


    // 2, 3, 1
    while(1) {
        ans1 = rt ( a[1], B, a[2] ); if( ans1 == INT_MAX ) break;
        ans1 = rt ( ans1, C, a[3] ); if( ans1 == INT_MAX ) break;
        ans = rt ( a[0], A, ans1 ); if( ans == INT_MAX ) break;
        Bu[ top++ ] = ans;
        break;
    }

    // 3, 2, 1
    while(1) {
        ans1 = rt ( a[2], C, a[3] ); if( ans1 == INT_MAX ) break;
        ans1 = rt ( a[1], B, ans1 ); if( ans1 == INT_MAX ) break;
        ans = rt ( a[0], A, ans1 ); if( ans == INT_MAX ) break;
        Bu[ top++ ] = ans;
        break;
    }
}


void dfs( int depth ) {
    int i, j, k;

    if( depth == 4 ) {
        for( i = 0; i < 4; i ++ ) {
            for( j = 0; j < 4; j ++ ) {
                for( k = 0; k < 4; k ++ ) {
                    b[1] = v[i];
                    b[2] = v[j];
                    b[3] = v[k];


                    a[0] = now[ stack[0] ];
                    a[1] = now[ stack[1] ];
                    a[2] = now[ stack[2] ];
                    a[3] = now[ stack[3] ];

                    cal( b[1], b[2], b[3] );
                }
            }
        }
    }

    for( i = 0; i < 4; i ++ ) {
        if( !hash[i] ) {
            hash[i] = 1;
            stack[ depth ] = i;
            dfs( depth+1 );
            hash[i] = 0;
        }
    }
}

int main() {
    int cas = 1;
    int i;
    while( scanf( "%d %d %d %d", &now[0], &now[1], &now[2], &now[3] ) != EOF ) {
        if( !now[0] && !now[1] && !now[2] && !now[3] )
            break;

        memset( hash, 0, sizeof( hash ) );
        top = 0;
        dfs(0);
        sort( Bu, Bu + top );

        int N = 1;
        A[0] = Bu[0];

        for( i = 1; i < top; i ++ )
            if( Bu[i] != Bu[i-1] )
                A[ N++ ] = Bu[i];
        top = N;

        //for( i = 0; i < top; i ++ )
        //    printf("%d ", A[i] );


        int Max(1);
        int bufst(0);
        int st(0), en(0);


        for( i = 1; i < top; i ++ ) {
            if( A[i] == A[i-1] + 1 ) {
                if( i - bufst + 1 >= Max ) {
                    Max = i - bufst + 1;
                    st = bufst;
                    en = i;
                }
            }else {
                if( 1 >= Max ) {
                    Max = 1;
                    st =  en = i;
                }
                bufst = i;
            }
        }

        printf("Case %d: %d to %d\n", cas++, A[st], A[en] );
    }
    return 0;
}


