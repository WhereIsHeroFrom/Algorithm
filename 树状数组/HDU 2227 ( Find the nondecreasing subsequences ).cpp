#include <iostream>
#include <algorithm>
using namespace std;

#define LL __int64

int a[ 100010 ], n;
int c[ 100010 ];
int B[ 100010 ], top, T[ 100010 ];

int lowbit( int x ) {
    return x & ( - x );
}

void Add( int x, int a ) {
    while( x <= 100000 ) {
        c[ x ] += a;
        if( c[ x ] >= 1000000007 )
            c[ x ] %= 1000000007;
        x += lowbit( x );
    }
}

LL Sum ( int x ) {
    LL S = 0;

    while( x >= 1 ) {
        S += c[ x ];
        if( S >= 1000000007 )
            S %= 1000000007;
        x -= lowbit( x );
    }

    return S;
}

int Bin( int x ) {
    int low = 1, high = top;
    int mid;

    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( T[ mid ] == x )
            return mid;
        else if( T[ mid ] < x )
            low = mid + 1;
        else
            high = mid - 1;
    }
}

int i, j;

int main() {
    while( scanf( "%d", &n ) != EOF ) {
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            B[i] = a[i];
        }
        sort( B, B + n );
        top = 2;
        T[1] = B[0];
        for(i = 1; i < n; i++) {
            if( B[i] != B[i-1] ) {
                T[ top ++ ] = B[i];
            }
        }
        top --;

        memset( c, 0, sizeof( c ));
        LL S = 0;
        for(i = 0; i < n; i++) {
            int pos = Bin(a[i]);
            LL A = Sum( pos ); 
            S += ( A + 1 ); if( S >= 1000000007 ) S %= 1000000007;
            Add( pos, A+1 );
        }
        printf("%I64d\n", S );
    } 
    return 0;
}

