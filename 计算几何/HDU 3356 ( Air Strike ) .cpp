#include <iostream>
#include <cmath>
using namespace std;

#define pi 3.141

struct point {
    double x, y;
}X[2], p[ 1010 ];

double R[2];
int n;
double A;

double Sqr( double x ) {
    return x * x;
}

double Dist( point a, point b ) {
    return sqrt( Sqr(a.x-b.x) + Sqr(a.y-b.y) );
}

bool In( point Y, int index ) {
    if( Dist( Y, X[ index ] ) <= R[ index ] )
        return true;
    return false;
}


int main() {
    int i, j, k;
    int cas = 1;

    while( scanf( "%d", &n ) != EOF && n ) {

        for( i = 0; i < 2; i ++ ) {
            scanf("%lf %lf", &X[i].x, &X[i].y );
        }
        scanf( "%lf", &A );
        for( i = 0; i < n; i ++ ) {
            scanf("%lf %lf", &p[i].x, &p[i].y );
        }

        int Min = n;
        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < 2; j ++ ) {
                R[j] = Dist( p[i], X[j] );
                if( R[j] * R[j] * pi <= A ) {
                    R[j^1] = sqrt(   (A - R[j] * R[j] * pi) / pi );
                    int ans = 0;
                    for( k = 0; k < n; k ++ ) {
                        if( k == i )
                            continue;
                        if( In( p[k], 0 ) || In( p[k], 1 ) )
                            continue;
                        ans ++;

                        if( ans >= Min )
                            break;
                    }
                    if( ans < Min )
                        Min = ans;
                }
            }
        }

        printf("%d. %d\n", cas++, Min );
    }
    return 0;
}

