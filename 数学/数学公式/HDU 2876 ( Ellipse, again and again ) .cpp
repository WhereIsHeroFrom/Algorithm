#include <iostream>
#include <cmath>
using namespace std;

struct point {
    int x;
    int y;
}p;

double Qx, Qy, Del, d2, c;
int t;
int a, b;

double Sqr( double x ) {
    return x * x;
}

int main() {
    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %d %d %d", &a, &b, &p.x, &p.y );

        if( p.x * p.x * b * b + a * a * p.y * p.y < a *a * b * b ) {
            printf("In ellipse\n");
            continue;
        }

        if( a < b ) {
            int temp = a;
            a = b;
            b = temp;

            temp = p.x;
            p.x = p.y;
            p.y = temp;
        }

        if( p.y == 0 ) {
            printf("%d\n", a*b*a*b );
        }else {
            Del = Sqr( p.x * b ) + Sqr( a * p.y );
            Del = sqrt( Del );

            Qx = a * b * p.x / Del;
            Qy = a * b * p.y / Del;

            c = sqrt( a*a - b*b * 1.0 );

            d2 = Sqr( Sqr(b*Qx)+Sqr(a*Qy) ) / ( Sqr(a*a*Qy) + Sqr(b*b*Qx) );
            d2 *= sqrt( Sqr(Qx - c) + Sqr(Qy) ) * sqrt( Sqr(Qx + c ) + Sqr(Qy) );

            printf("%.0lf\n", d2);
        }
    }
    return 0;
}

