#include <iostream>

using namespace std;

#define maxn 100001

int hash[2][100010];
int Min;
int index;
int n, m;

int ABS( int a ) {
    return a < 0 ? -a : a;
}

void dfs( int pre, int val, int k ) {

    if( k == m - 1 ) {
        int now = hash[index][maxn] - hash[index][pre];
        int T = val + ABS( now * m - n ); 
        if( T < Min ) {
            Min = T;
        }
        return;
    }
    if( val >= Min ) return ;

    int low = pre + 1;
    int high = maxn;
    int mid;
    int ans = pre;

    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( m * ( hash[index][mid] - hash[index][pre] ) < n ) {
            ans = mid;
            low = mid + 1;
        }else
            high = mid - 1;
    }

    int i;
    for( i = ans; i <= ans + 1; i ++ ) {
        dfs( i, val + ABS( (hash[index][i] - hash[index][pre]) * m - n ), k + 1 ); 
    }
}

int gcd( int a, int b ) {
    int m = 1;
    while(m) {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

int main() {
    int cas = 1;
    int i, j;
    int x;
    while( scanf( "%d %d", &n, &m ) != EOF && (n||m) ) {
        memset( hash, 0, sizeof( hash ) );

        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < 2; j ++ ) {
                scanf("%d", &x );
                hash[j][x+1] ++;
            }
        }

        for( i = 1; i <= maxn; i ++ ) {
            hash[0][i] += hash[0][i-1];
            hash[1][i] += hash[1][i-1];
        }
        Min = INT_MAX;
        for( i = 0; i < 2; i ++ ) {
            index = i;
            dfs( 0, 0, 0 );
        }
        int A = Min;
        int B = m * m;
        int G = gcd( A, B );
        A /= G;
        B /= G;
        printf("%d. %d/%d\n", cas++, A, B );
    }
    return 0;
}

