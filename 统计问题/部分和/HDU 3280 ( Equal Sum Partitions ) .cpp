#include <iostream>

using namespace std;

#define MAXN 10010

int a[MAXN], sum[MAXN];

int main() {
    int t;
    int i, j;
    scanf("%d", &t);

    while(t--) {
        int c, n;
        scanf("%d %d", &c, &n);
        for(i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            sum[i] = a[i] + sum[i-1];
        }

        for(i = 1; i <= n; i++) {
            if(sum[n] % sum[i] == 0) {
                int v = 0;
                for(j = i+1; j <= n; j++) {
                    v += a[j];
                    if(v > sum[i]) break;
                    if(v == sum[i]) {
                        v = 0;
                    }
                }
                if(j > n) {
                    break;
                }
            }
        }
        printf("%d %d\n", c, sum[i]);
    } 
    return 0;
}

