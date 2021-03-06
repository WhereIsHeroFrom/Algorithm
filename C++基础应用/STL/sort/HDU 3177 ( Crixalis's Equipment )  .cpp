#include <iostream>
#include <algorithm>
using namespace std;

struct point {
    int A, B;
    int X;
}p[ 1010 ];

bool cmp( point a, point b ) {
    if( a.X != b.X )
        return a.X > b.X;
    //return a.B > b.B;
}

int V, n;

int main() {
    int t;
    int i;
    scanf( "%d", &t );

    while( t-- ) {
        scanf("%d %d", &V, &n );
        for( i = 0; i < n; i ++ ) {
            scanf("%d %d", &p[i].A, &p[i].B );
            p[i].X = p[i].B - p[i].A;
        }
        sort( p, p + n, cmp );
        for( i = 0; i < n; i ++ ) {
            if( p[i].B <= V ) {
                V -= p[i].A;
            }else
                break;
        }

        if( i == n )
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

