#include <iostream>
#include <algorithm>

using namespace std;

int i, a[10000], b;
int n;

int main() {
    int sum  = 0;
    while(scanf("%d", &n) != EOF) {

        sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &b, &a[i]);
            sum += b;
        }
        sort(a, a + n );
        printf("%.2lf\n", sum * 1.0 / a[0]);
    }
}

