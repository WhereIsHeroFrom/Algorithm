#include <iostream>

using namespace std;

int n, h;
int c[ 100010 ];


int lowbit( int x ) {
    return x & ( -x );
}

void Add( int x, int A ) {
    while( x <= 100000 ) {
        c[ x ] += A;
        x += lowbit( x );
    }
}

int Sum( int x ) {
    int S = 0;
    while( x >= 1 ) {
        S += c[x];
        x -= lowbit( x );
    }
    return S;
}

int x, a, k;
int m;
int p, i;
int main() {
    while( scanf("%d", &m) != EOF ) {
        memset( c, 0, sizeof( c ));

        while( m-- ) {
            scanf( "%d", &p );

            if( p == 0 ) {
                int x;
                scanf("%d", &x);
                Add( x, 1 );
            }else if( p == 1 ) {
                scanf("%d", &x);

                if( Sum(x) - Sum(x-1) == 0 ) {
                    printf("No Elment!\n");
                }else {
                    Add( x, -1 );
                }
            }else {
                scanf("%d %d", &a, &k);
                if( Sum(100000)-Sum(a) < k ) {
                    printf("Not Find!\n");
                }else {
                    int low, high, mid;
                    low = a + 1;
                    high = 100000;

                    while( low <= high ) {
                        mid = ( low + high ) / 2;

                        if( Sum(mid)-Sum(a) < k )
                            low = mid + 1;
                        else
                            high = mid - 1;
                    }

                    int op = mid - 5;
                    if( op < a )
                        op = a;

                    for(i = op; i < op + 10; i++) {
                        if( Sum(i)-Sum(a) >= k )
                            break;
                    }

                    printf("%d\n", i );
                }
            }
        }
    }
    return 0;
}
