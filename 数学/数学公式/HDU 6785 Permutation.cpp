#include <iostream>

using namespace std;

#define ll long long

ll n, m;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld %lld", &n, &m);
        if(m == 0) {
            printf("0\n");
            continue;
        }
        if(m*2 > n) {
            m = n / 2;
        }
        ll ans = (n*2 - m - 1) * m / 2 + (n - 2*m) * m + m*(m-1) / 2;
        printf("%lld\n", ans);
    }
    
    return 0;
} 
