#include <iostream>
using namespace std;

int n, m;
int v[1<<16];
int x, y;
int Max, Sum;

int main() {
    int i, sub;
    while( scanf( "%d", &n ) != EOF && n ) {
        scanf("%d", &m );
        memset( v, 0, sizeof( v ) );
        while( m-- ) {
            scanf("%d %d", &x, &y );
            v[x] += y;
        }
        Max = 0;
        for( i = 1; i < (1<<n); i ++ ) {
            Sum = 0;
            for( sub = i; sub != 0; sub = ( sub - 1 ) & i ) {
                Sum += v[sub];
            }
            if( Sum > Max )
                Max = Sum;
        }
        printf("%d\n", Max );
    }
    return 0;
}

