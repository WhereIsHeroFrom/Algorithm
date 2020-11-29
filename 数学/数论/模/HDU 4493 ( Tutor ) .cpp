#include <iostream>

using namespace std;

#define eps 1e-8

int a[12];
int ans;

int main() {
    int t, i;
    scanf("%d", &t);
    while( t-- ) {
        ans = 0;
        for(i = 0; i < 12; i++) {
            double v;
            scanf("%lf", &v);
            a[i] = int(v * 100 + eps);
            ans += a[i];
        }
        if(ans % 12 >= 6) {
            // 上整
            ans = (ans + 11) / 12;
        }else {
            // 下整
            ans = ans / 12;
        }
        printf("$");
        if(ans % 100 == 0) {
            printf("%d\n", ans/100);
        }else if(ans % 10 == 0) {
            printf("%d.%d\n", ans/100, ans%100/10);
        }else {
            printf("%d.%02d\n", ans/100, ans%100);
        }
    }
    return 0;
}
/*
2 
100.00 
489.12 
12454.12 
1234.10 
823.05 
109.20 
5.27 
1542.25 
839.18 
83.99 
1295.01 
1.75
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00 
100.00
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.2
1.11
1.11
1.11
1.11
1.11
1.11
1.11
1.11
1.11
1.11
1.00
1.00
*/
