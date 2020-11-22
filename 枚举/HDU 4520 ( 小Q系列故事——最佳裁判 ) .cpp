#include <iostream>
#include <cmath>
using namespace std;

int n;
double Max, Min;
double a[25];

int main() {
    int i;
    while( scanf("%d", &n) != EOF && n) {
        Max = -1;
        Min = 11;
        double sum = 0;
        for(i = 1; i <= n; i++) {
            scanf("%lf", &a[i]);
            sum += a[i];    
            if(a[i] > Max) Max = a[i];
            if(a[i] < Min) Min = a[i];
        }
        sum -= (Max + Min);
        sum /= (n-2);
        int u = 1;
        for(i = 1; i <= n; ++i) {
            if(fabs(a[i] - sum) < fabs(a[u] - sum)) {
                u = i;
            }
        }
        printf("%d\n", u);
    }
    return 0;
}
