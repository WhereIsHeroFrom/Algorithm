#include <iostream>
#include <cmath>
using namespace std;

double a, b, c;

int main()
{
    while(scanf("%lf %lf %lf", &a, &b, &c) != EOF){
        double buf = c / a;
        buf = log(buf) / log(1 + b / 100);
        printf("%d\n", int(buf) == buf ? (int)buf : (int)buf + 1);
    }
    return 0;
}

