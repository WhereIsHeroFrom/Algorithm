#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int x[110], y[110];
int n, m;

int main() {
    int t;
    scanf("%d", &t);
    
    while(t--) {
        int ans = 1000000000;
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; ++i) {
            scanf("%d %d", &x[i], &y[i]);
            int g = (m + x[i] - 1)/ x[i];
            ans = min(ans, g * y[i]);
        }
        printf("%d\n", ans);
    }
    
    return 0;
} 
