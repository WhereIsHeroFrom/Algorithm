/*#include<iostream>
#include<algorithm>
using namespace std;

#define maxn 410
int dp[maxn][maxn][2];
int n, f[maxn];

int main() {
    int T;
    scanf("%d",&T);
    while( T -- ) {
        scanf("%d",&n);
        for( int i = 0; i < n; i ++ ) scanf("%d",&f[i]);
        sort(f, f + n);
    }
    return 0;
}*/

#include <iostream>
#include <algorithm>

using namespace std;

#define LL long long

LL c[ 500010 ];
LL A[ 500010 ];
LL B[ 500010 ];
LL T[ 500010 ];
LL C[ 500010 ];

LL X, Y, Z, i, S;
int n, m;
int zong;

//计算a*b%n
inline LL Produc_Mod(LL a, LL b, LL mod)
{
    LL sum = 0;
    while( b )
    {
        if( b % 2 == 1 ) sum = ( sum + a ) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return sum;
}

LL Binary( LL S ) {
    LL low = 1, high = zong;
    LL mid;

    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( T[ mid ] == S )
            return mid;
        if( T[ mid ] > S ) {
            high = mid - 1;
        }else
            low = mid + 1;
    }
}

int lowbit( int x ) {
    return x&(-x);
}

void Add( int x, LL A ) {
    while( x <= zong ) {
        c[ x ] += A; if( c[x] >= 1000000007 ) c[x] %= 1000000007;
        x += lowbit( x );
    }
}

LL Sum( int x ) {
    LL S = 0;
    while( x >= 1 ) {
        S += c[ x ]; if( S >= 1000000007 ) S %= 1000000007;
        x -= lowbit( x );
    }
    return S;
}

int t;


int main() {

    scanf("%d", &t);
    int ty = t;

    while( t-- ) {
        scanf("%d %d %lld %lld %lld", &n, &m, &X, &Y, &Z );

        memset( c, 0, sizeof( c ));
        for(i = 0; i < m; i++)
            scanf("%lld", &A[i]);
        X %= Z;
        Y %= Z;

        for( i = 0; i < n; i++) {
            int nt = i % m;

            C[i] = B[i] = A[ nt ];
            //printf("%d ", A[ i % m ]);
            A[ nt ] = ( X * A[ nt ] % Z + Y * (i+1) % Z );
            if( A[ nt ] >= Z )
                A [ nt ] %= Z;
        }
        //puts("");
        sort( C, C + n );

        zong = 2;
        T[1] = C[0];

        for(i = 1; i < n; i++) {
            if( C[i] != C[i-1] )
                T[ zong++ ] = C[i];
        }

        zong --;

        S = 0;
        for(i = 0; i < n; i++) {
            int BX = Binary( B[i] );
            LL DD = Sum( BX-1 );
            S += ( DD + 1 );
            Add( BX, DD + 1 );
        }

        printf("Case #%d: %lld\n", ty - t, (S % 1000000007 + 1000000007 ) % 1000000007 );
    }
    return 0;
}

