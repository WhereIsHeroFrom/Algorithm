#include <iostream>

using namespace std;

#define MAXN 100010

int a[MAXN];
int b[MAXN], bn;

int main() {
    int i, n;
    while (scanf("%d", &n) != EOF) {
        bn = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);


            int l = 0, r = bn - 1;
            int ans = bn;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[i] <= b[mid]) {
                    r = mid - 1;
                    ans = mid;
                }
                else {
                    l = mid + 1;
                }
            }

            if (ans == bn) {
                b[bn++] = a[i];
            }
            else {
                b[ans] = a[i];
            }
        }
        printf("%d\n", bn);


    }
    return 0;
}