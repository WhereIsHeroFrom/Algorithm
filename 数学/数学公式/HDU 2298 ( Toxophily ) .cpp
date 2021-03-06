#include <iostream>
#include <cmath>

#define g 9.8
#define pi acos(-1.0)

using namespace std;

double change(double x) {
    return x * pi / 180;
}

double v;

double f(double a, double b, double c, double d) {
     return ( -b + d * sqrt( b*b - a * c * 4 ) ) / 2 / a;
}

int t;
double x, y;

double Min(double a, double b){
    return a < b ? a : b;
}

double Max(double a, double b){
    return a > b ? a : b;
}

int main() {
    double i;

    scanf("%d", &t);

    while(t--) {
        scanf("%lf %lf %lf", &x, &y, &v);

        if(fabs(x) < 1e-6 && fabs(y) < 1e-6) {
            printf("0.000000\n");
            continue;
        }


        if( fabs(x) < 1e-6 ) {

            if( v >= sqrt(2 * g * y ) ) {
                printf("%.6lf\n", pi / 2);
            }else {
                printf("-1\n");
            }
            continue;
        }

        if(v <= sqrt(2 * g * y ) ) {
            printf("-1\n");
        }else {

            double a, b, c;
            a = - g * x * x / 2/ v / v;
            b = x;
            c = a - y;

            if(b * b - 4 * a * c  < 0) {
                printf("-1\n");
                continue;
            }

            if(y < 1e-7) {
                printf("%.6lf\n", Max(  atan(f(a, b, c, 1)) ,  atan(  f(a, b, c, -1)) )   );
            }else
                printf("%.6lf\n", Min(  atan(f(a, b, c, 1)) ,  atan(  f(a, b, c, -1)) )   );
        }
    }
}
