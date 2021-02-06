#include <iostream>
#include <algorithm>
using namespace std;

int a[3];

int main() {
    int t, cas = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &a[0], &a[1], &a[2]);
        sort(a, a + 3);
        int ans = a[0] * a[0] + a[1] * a[1] - a[2] * a[2];
        printf("Case %d: ", ++cas);
        if (ans > 0) {
            printf("Acute triangle\n");
        }
        else if (ans == 0) {
            printf("Right triangle\n");
        }
        else {
            printf("Obtuse triangle\n");
        }
    }

    return 0;
}