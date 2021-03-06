#include <iostream>
#include <cmath>
#define pi acos(-1.0)

using namespace std;

double r, R, H, V, RR;
double s, S, h;

double Min(double a, double b) {
    return a < b ? a : b;
}

double low, high, mid;


int main() {
    int t;

    scanf("%d", &t);

    while(t--) {
        scanf("%lf %lf %lf %lf", &r, &R, &H, &V);
        if(fabs(R - r) < 1e-6) {
            h = V / pi / R / R;
        }else {
            low = 1;
            high = 100;

            while(high - low > 1e-8) {
                h = (low + high) / 2;
                RR = h / H * (R - r) + r;
                double buf = (r * r + RR * RR + r * RR) * h * pi / 3;
                if(buf > V) {
                    high = h - 1e-8;
                }else {
                    low = h + 1e-8;
                }
            }
        }
        printf("%.6lf\n", Min(h, H));
    }
}
