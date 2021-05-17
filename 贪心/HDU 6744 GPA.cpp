#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;

double f[11][2] ={
    {95, 4.3},
    {90, 4.0},
    {85, 3.7},
    {80, 3.3},
    {75, 3.0},
    {70, 2.7},
    {67, 2.3},
    {65, 2.0},
    {62, 1.7},
    {60, 1.0},
    {0, 0},
};





int main() {
    int t, x;
    scanf("%d", &t);
    while(t--) {
        double ans = 0;
        scanf("%d", &x);
        for(int i = 0; i < 11; ++i) {
            for(int j = i; j < 11; ++j) {
                for(int k = j; k < 11; ++k) {
                    for(int l = k; l < 11; ++l) {
                        if( f[i][0] + f[j][0] + f[k][0] + f[l][0] <= x ) {
                            ans = max(ans, f[i][1] + f[j][1] + f[k][1] + f[l][1]);
                        }
                    }
                }
            }
        }
        printf("%.1lf\n", ans);
    }
    return 0;
} 
