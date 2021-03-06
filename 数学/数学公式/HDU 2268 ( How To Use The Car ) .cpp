#include <iostream>

using namespace std;

double a, b, c;
double q, w, e, r, t, y;
double t1, t2;

double ans_one(double a, double b, double c) {
    q = b;
    w = a;
    e = (3*a*b - b*b) / (a+b);
    r = b;
    t = b;
    y = a;
    t2 = (c*e - c*q) / (w*e - r*q);
    t1 = (c - w*t2) / q;
    return t1 + t2;
}

int main() {

    while(scanf("%lf %lf %lf", &a, &b, &c) != EOF) {

        if(a <= b) {
            printf("%.3lf\n", ans_one(a, b, c) ); 
        }else {
            printf("%.3lf\n", c / a);
        }
    }
    return 0;
}
