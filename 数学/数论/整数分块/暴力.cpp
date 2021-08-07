#include <iostream>
using namespace std;
int main() {
    int n, k;
    while(scanf("%d %d", &n, &k) != EOF) {
        int ans = 0; 
        for(int x = 1; x <= n; ++x) {
            ans += k / x;
        }
        printf("%d\n", ans);
    }
    return 0;
} 
