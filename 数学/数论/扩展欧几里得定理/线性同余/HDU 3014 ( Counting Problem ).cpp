#include <iostream>

using namespace std;

#define ll __int64
#define maxn 65537

ll exp_gcd(ll a, ll b, ll &X, ll &Y)
{
     ll q, temp;
     if( !b ) {
         q = a;
         X = 1;
         Y = 0;
     }else {
        q = exp_gcd(b, a % b, X, Y);
        temp = X;
        X = Y;
        Y = temp - (a / b) * Y;
     }
     return q;
}

int up[ 5010 ], down[ 5010 ];
int a[ 110 ];
int M;

bool f[ maxn ];
int prime[ maxn ], size;
int p[ 100 ], s[ 100 ], num;

void Init() {
    int i, j;
    f[0] = f[1] = 1;
    for( i = 2; i < maxn; i ++ ) {
        if( !f[i] ) {
            prime[ size++ ] = i;
            for( j = i+i; j < maxn; j += i )
                f[j] = 1;
        }
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

ll C( int n, int m ) {
    int i, j;
    ll B = 1 % M;
    for( i = 1; i <= m; i ++ ) {
        int now = i;
        for( j = 0; j < num; j ++ ) {
            while( now % p[j] == 0 ) {
                now /= p[j];
                s[j] ++;
            }
            if( now == 1 )
                break;
        }
        B = ( B * (ll)now ) % M;
    }
    ll A = 1 % M;
    for( i = n; i > n - m; i-- ) {
        int now = i;
        for( j = 0; j < num; j ++ ) {
            while( s[j] && now % p[j] == 0 ) {
                now /= p[j];
                s[j] --;
            }
            if( now == 1 )
                break;
        }            
        A = ( A * (ll)now ) % M;
    }

    ll X, Y;
    exp_gcd( B, M, X, Y);
    X = ( X % M + M ) % M;
    return A * X % M;
}

void fac( int M ) {
    int i = 1;
    num = 0;
    for( i = 0; i < size; i ++ ) {
        if( M % prime[i] == 0 ) {
            p[ num ] = prime[i];
            s[ num ] = 0;
            num ++;
            while( M % prime[i] == 0 ) 
                M /= prime[i];
        }
    }
    if( M != 1 ) {
        p[ num++ ] = M;
    }
}

int main() {

    Init();

    int i, n, k;
    while( scanf( "%d %d", &n, &M ) != EOF ) {

        n *= n;
        scanf("%d", &k );
        int Sum = 0;
        for( i = 0; i < k; i ++ ) {
            scanf("%d", &a[i] );
            Sum += a[i];
        }
        if( M == 1 || Sum > n ) {
            printf("0\n");
            continue;
        }    
        fac(M);

        ll ans = 1 % M;
        for( i = 0; i < k; i ++ ) {
            ans = ans * C( n, a[i] );
            n -= a[i];
            if( ans >= M )
                ans %= M;
            if( ans == 0 )
                break;
        }
        printf("%I64d\n", ans );
    }
    return 0;
}

/*
5000 100000007
100
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000
5000 5000 5000 5000 5000 5000 5000 5000 5000 5000

*/
