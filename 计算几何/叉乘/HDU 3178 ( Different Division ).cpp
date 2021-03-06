#include <iostream>
#include <cmath>

using namespace std;

#define eps 1e-8

struct point {
    double x, y;
    point() {
    }
    point( double _x, double _y ) {
        x = _x; y = _y;
    }
};

point operator +( point a, point b ) {
    return point( a.x + b.x, a.y + b.y );
}
point operator -( point a, point b ) {
    return point( a.x - b.x, a.y - b.y );
}
double operator*( point a, point b ) {
    return a.x * b.y - a.y * b.x;
}
int sgn( double f ) {
    if( fabs(f) < eps ) return 0;
    if( f < 0 ) return -1; else return 1;
}
int Judge( point X, point p1, point p2 ) {
    return sgn( ( X - p1 ) * ( p2 - p1 ) );
}

point T[ 1010 ];
int P[2];
int n;

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while( t-- ) {
        scanf("%d", &n );
        for( i = 1; i <= n; i ++ ) {
            scanf("%lf %lf", &T[i].x, &T[i].y );
        }
        scanf("%d %d", &P[0], &P[1] );
        for( i = 1; i <= n; i ++ ) {
            int u = Judge( T[i], T[ P[0] ], T[ P[1] ] );
            if( u == 0 )
                printf("On\n");
            else if( u == -1 )
                printf("Left\n");
            else
                printf("Right\n");
        }
    }
}

