#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 100010
#define ll __int64

ll C[2][ maxn ];
int n;

int lowbit( int key ) {
    return key & ( -key );
}
void add( int index, int key, int val ) {
    while( key <= n ) {
        C[ index ][ key ] += val;
        key += lowbit( key );
    }
}
ll sum( int index, int key ) {
    ll s = 0;
    while( key >= 1 ) {
        s += C[ index ][key];
        key -= lowbit(key);
    }
    return s;
}

int B[2][maxn];
struct point {
    int X, H;
}p[ maxn ];

int BIN( int index, int key ) {
    int low = 0;
    int high = n - 1;
    int mid, ans;
    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( B[index][mid] >= key ) {
            ans = mid;
            high = mid - 1;
        }else
            low = mid + 1;
    }
    return ans + 1;
}

bool cmp( point a, point b ) {
    if( a.H != b.H )
        return a.H > b.H;
    return a.X < b.X;
}

int main() {
    int i;
    while( scanf( "%d", &n ) != EOF ) {
        for( i = 0; i < n; i ++ ) {
            scanf("%d %d", &p[i].X, &p[i].H );
            B[0][i] = p[i].X;
            B[1][i] = p[i].H;
        }
        sort( B[0], B[0] + n );
        sort( B[1], B[1] + n );
        for( i = 0; i < n; i ++ ) {
            p[i].X = BIN( 0, p[i].X );
            p[i].H = BIN( 1, p[i].H );
        }
        sort( p, p + n, cmp );
        memset( C, 0, sizeof( C ) );

        add( 0, p[0].X, p[0].X );
        add( 1, p[0].X, 1 );

        ll Sum = 0;
        for( i = 1; i < n; i ++ ) {
            Sum += (ll)p[i].H * ( sum(1, p[i].X) * p[i].X - sum( 0, p[i].X ) );
            Sum += (ll)p[i].H * ( ( sum( 0, n ) - sum( 0, p[i].X ) ) - ( sum( 1, n ) - sum( 1, p[i].X ) ) * p[i].X );
            add( 0, p[i].X, p[i].X );
            add( 1, p[i].X, 1 );
        }
        printf("%I64d\n", Sum );
        
    }
    return 0;
}

