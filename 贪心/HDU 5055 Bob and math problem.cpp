#include <iostream>
#include <algorithm>

using namespace std;

int n, a[110];
int b[110];

int getMinOdd() {
    int minOdd = 100, zeroCnt = 0;
    for (int i = 1; i <= n; ++i) {
        if ((a[i] & 1) && a[i] < minOdd) {
            minOdd = a[i];
        }
        if (!a[i]) {
            ++zeroCnt;
        }
    }
    if (minOdd == 100) {
        return -1;
    }
    if (zeroCnt >= n - 1) {
        if (n >= 2)
            return -1;
    }
    return minOdd;
}

int main() {

    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        int minOdd = getMinOdd();
        if (minOdd == -1){
            printf("-1\n");
        }
        else {
            int minOddCnt = 1;
            int s = 0;
            for (int i = 1; i <= n; ++i) {
                if (a[i] == minOdd) {
                    if (minOddCnt)
                        minOddCnt--;
                    else {
                        b[s++] = a[i];
                    }
                }
                else {
                    b[s++] = a[i];
                }
            }
            sort(b, b + s);
            for (int i = s - 1; i >= 0; --i) {
                printf("%d", b[i]);
            }
            printf("%d\n", minOdd);
        }

    }
    return 0;
}