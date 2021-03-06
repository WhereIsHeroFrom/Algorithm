#include <iostream>
#include <cmath>
using namespace std;


double Y;
double l, r, m;

double f( double x ) {
    return 8*pow(x, 4.0) + 7*pow(x, 3.0) + 2*pow(x, 2.0) + 3*x + 6;
}

int main() {
    int t;
    scanf("%d", &t );
    while( t-- ) {
        scanf("%lf", &Y );
        if( f(0) <= Y && Y <= f(100) ) {
            l = 0;
            r = 100;
            while( r - l > 1e-6 ) {
                m = (l + r) / 2;
                double ans = f(m);
                if( ans > Y ) {
                    r = m - 1e-7;
                }else
                    l = m + 1e-7;
            }
            printf("%.4lf\n", (l + r) / 2 );
        }else
            printf("No solution!\n");
    }
}

