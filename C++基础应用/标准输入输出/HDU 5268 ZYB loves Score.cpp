#include <iostream>

using namespace std;

#define MAXN 4

int A[MAXN], B[MAXN];
int s[MAXN] = { 1000, 1500, 2000, 2500 };

int getMax(int a, int b){
    return a > b ? a : b;
}

int main() {
    int t, cas = 0;
    int i;
    scanf("%d", &t);

    while (t--) {

        int ans = 0;
        for (i = 0; i < MAXN; ++i) {
            scanf("%d %d", &A[i], &B[i]);

            ans += getMax(s[i] * 2 / 5, (250 - A[i])*s[i] / 250 - B[i] * 50);
        }
        printf("Case #%d: %d\n", ++cas, ans);
    }

    return 0;
}