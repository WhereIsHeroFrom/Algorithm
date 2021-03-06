#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 1000010

int x[MAXN];

int main() {
    int i, n;
    x[0] = 1;
    for(i = 1; i < MAXN; ++i) {
        int p1 = i - sqrt(i*1.0);
        int p2 = log(i*1.0);
        int p3 = i*sin(i*1.0)*sin(i*1.0);
        x[i] = x[p1] + x[p2] + x[p3];
        x[i] %= 1000000;
    }
    while(scanf("%d", &n) != EOF && n >= 0) {
        printf("%d\n", x[n]);
    }
    return 0;
}
