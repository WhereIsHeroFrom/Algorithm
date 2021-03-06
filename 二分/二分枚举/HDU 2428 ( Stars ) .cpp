#include <iostream>
#include <vector>
using namespace std;

int t;
int n;

struct point {
    int x;
    int y;
}p[ 10000 ];

int cmp( const void *a, const void *b ) {
    point *c = (point *)a;
    point *d = (point *)b;
    if( c->x != d->x )
        return c->x - d->x;
    return c->y - d->y;
}

vector < int > vec[ 20001 ];

int binary( int x, int key ) {
    int low = 0;
    int high = vec[ x ].size() - 1;
    int mid;

    int i;
    while( low < high ) {
        mid = ( low + high ) / 2;
        if( vec[ x ][ mid ] == key )
            return 1;
        else if( vec[ x ][ mid ] > key )
            high = mid - 1;
        else
            low = mid + 1;
    }
    int op = mid - 3;
    if( op < 0 )
        op = 0;
    for(i = op; i < op + 6 && i < vec[ x ].size(); i++) {
        if( vec[ x ][ i ] == key )
            return 1;
    }
    return 0;
}

int main() {

    int i, j, k;

    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
            p[i].x += 10000;
            p[i].y += 10000;
        }
        qsort( p, n, sizeof( point ), cmp);

        for(i = 0; i <= 20000; i++)
            vec[i].clear();

        for(i = 0; i < n; i++) {
            vec[ p[i].x ].push_back( p[i].y );
        }

        int sum = 0;
        for(i = 0; i <= 20000; i++) {
            if( vec[i].size() > 1 ) {
                for(j = 0; j < vec[i].size(); j++) {
                    for(k = j + 1; k < vec[i].size(); k ++ ) {
                        if( vec[i][k] == vec[i][j] )
                            continue;

                        int del = vec[i][k] - vec[i][j];
                        if( i + del > 20000 || vec[ i+del ].size() <= 1 )
                            continue;
                        if( !binary( i+del, vec[i][j] ) )
                            continue;
                        if( !binary( i+del, vec[i][k] ) )
                            continue;
                        sum ++;
                    }
                }
            }
        }

        printf("%d\n", sum);
    }

    return 0;
}
