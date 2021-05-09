#include <iostream>
#include <cmath>
using namespace std;


double y;
double l, r, m;

double f( double x ) {
    return 6 * pow(x, 7.0) + 8 * pow(x, 6.0) + 7 * pow( x, 3.0 ) + 5 * pow( x, 2.0 );
}

double ff( double x ) {
    return 42 * pow(x, 6.0) + 48 * pow(x, 5.0) + 21 * pow( x, 2.0 ) + 10 * pow( x, 1.0 );
}
int i;
double ans[3];

int main() {
    int t;
    scanf("%d", &t );
    while( t-- ) {
        scanf("%lf", &y );
        ans[0] = f(0);
        ans[1] = f(100) - y * 100;
        if( ans[1] < ans[0] )
            ans[0] = ans[1];

        if( ff(0) <= y <= ff(100) ) {
            l = 0;
            r = 100;
            while( r - l > 1e-6 ) {
                m = ( l + r ) / 2;
                double a = ff(m);
                if( a > y ) 
                    r = m - 1e-7;
                else
                    l = m + 1e-7;
            }
            ans[2] = f((l+r)/2) - y * ( (l+r)/2 );
        }
        if( ans[2] < ans[0] )
            ans[0] = ans[2];
        printf("%.4lf\n", ans[0] );
    }
}


