#include <iostream>

using namespace std;

#define maxn 510

int gcd( int a, int b ) {
    int m = 1;
    if( a == 0 ) return b;
    if( b == 0 ) return a;
    while(m) {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

int n, m;
int map[ maxn ][ maxn ];
int Map[ maxn ][ maxn ];
int gc[ maxn ][ maxn ];
int ans;
int I[ 65537 ], f[ 65537 ];
int G;


bool AllOne( int r, int c ) {
    int i, j;
    for( i = 0; i < r; i ++ ) {
        for( j = 0; j < c; j ++ ) {
            if( gc[i][j] != 1 )
                return false;
        }
    }
    return true;
}

bool cmp( int r, int c, int R, int C ) {
    int i, j;
    int v = 0;
    for( i = 0; i < r; i ++ ) {
        for( j = 0; j < c; j ++ ) {
            if( map[ R*r+i ][ C*c+j ] % gc[i][j] )
                return false;
            if( map[ R*r+i ][ C*c+j ] / gc[i][j]
                != map[ R*r ][ C*c ] / gc[0][0] )
                return false;
        }
    }
    return true;
}

bool Matrix( int r, int c ) {
    int i, j;
    int v = 0;

    for( i = 0; i < r; i ++ ) {
        for( j = 0; j < c; j ++ ) {
            v = gcd( v, map[i][j] );
        }
    }

    for( i = 0; i < r; i ++ ) {
        for( j = 0; j < c; j ++ ) {
            gc[i][j] = map[i][j] / v;
        }
    }

    G = 0;
    for( i = 0; i < (n/r); i++ ) {
        for( j = 0; j < (m/c); j ++ ) {
            if( !cmp( r, c, i, j ) )
                return false;
            G = gcd( G, map[ i*r ][ j*c ] / gc[0][0] );
        }
    }
    return true;
}

int main() {
    I[1] = 1;

    int i, j;

    f[0] = f[1] = 1;

    for( i = 2; i < 65537; i++ ) {
        if( !f[i] ) {
            I[i] = 2;
            for( j = i+i; j < 65537; j += i ) {
                f[j] = 1;
                if( I[j] == 0 ) I[j] = 1;

                int now = j;
                int cnt = 1;
                while( now % i == 0 ) {
                    now /= i;
                    cnt ++;
                }
                I[j] *= cnt;
            }
        }
    }

    while( scanf( "%d %d", &n, &m ) != EOF && (n||m) ) {
        int postive = 1;
        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < m; j ++ ) {
                scanf("%d", &map[i][j] );
                if( map[i][j] <= 0 )
                    postive = 0;
            }
        }

        if( !postive ) {
            printf("0\n");
            continue;
        }

        ans = 0;

        for( i = 1; i <= n; i ++ ) {
            if( n % i == 0 ) {
                for( j = 1; j <= m; j ++ ) {
                    if( m % j == 0 ) {
                        if( i==1 && j==1 )
                            continue;
                        if( i==n && j==m )
                            continue;
                        if( Matrix( i, j ) )
                            ans += I[G];
                    }
                }
            }
        }

        printf("%d\n", ans );
    }

    return 0;
}

