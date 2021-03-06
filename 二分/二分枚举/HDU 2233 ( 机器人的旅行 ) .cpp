#include <iostream>
#include <algorithm>
using namespace std;

int n, t;
int a[ 100010 ];
int i, now;
int fp, fn;

int Bin1( int to ) {
    int low = 0;
    int high = n - 1;
    
    int i;
    if( to >= a[ high ] )
        return n-1;

    int mid;

    while( low < high ) {
        mid = ( low + high ) / 2;
        if( a[ mid ] > to )
            high = mid - 1;
        else
            low = mid + 1;
    }

    while( low < n && a[ low ] <= to )
        low ++;

    int op = low;

    if( op >= n )
        op = n-1;

    for( i = op; i >= 0 ; i-- ) {
        if( a[ i ] <= to )
            return i;
    }

    return -1;
}

int Bin2( int to ) {
    int low = 0;
    int high = n - 1;
    
    int i;
    if( to <= a[ 0 ] )
        return 0;

    int mid;
    while( low < high ) {
        mid = ( low + high ) / 2;

        if( a[ mid ] < to )
            low = mid + 1;
        else
            high = mid - 1;
    }

    while( low >= 0 && a[ low ] >= to )
        low --;

    int op = low;

    if( low < 0 )
        low = 0;

    for(i = low;  i < n; i++) {
        if( a[i] >= to )
            return i;
    }

    return -1;
}

int main() {
    while( scanf("%d %d", &n, &t) != EOF ) {
        int Max = 0;

        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort( a, a + n );

        fp = -1; fn = -1;

        for(i = 0; i < n; i++) {
            if( a[i] > 0 ) {
                fp = i;
                break;
            }
        }

        for(i = n-1; i >= 0; i--) {
            if( a[i] < 0 ) {
                fn = i;
                break;
            }
        }


        for(i = 0; i < n; i++) {
            if( a[i] < 0 ) {
                now = t + a[i];

                if( now < 0 )
                    continue;

                if(fp != -1 && (fp-1) - i + 1 > Max ) {
                     Max = (fp-1) - i + 1;
                }
                int u = Bin1( a[i] + now );

                if( u != -1 && u - i + 1 > Max )
                    Max = u - i + 1;    
            
            }else {
                now = t - a[i];

                if( now < 0 )
                    continue;

                if(fn != -1 && i - (fn+1) + 1 > Max ) {
                     Max = i - (fp+1) + 1;
                }

                int u = Bin2( a[i] - now );

                if( u != -1 && i - u + 1 > Max )
                    Max = i - u + 1;
            }


        }

        printf("%d\n", Max);
    }
}
