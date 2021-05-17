#include <iostream>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        long long n;
        scanf("%lld", &n);
        int c = 0, pre = 0;
        while(n) {
            int now = (n & 1);
            n >>= 1;
            
            if(pre == 0 && now == 1) {
                ++c;
            }
            pre = now;
        }
        printf("%d\n", c);
    }
    
    return 0;
} 
