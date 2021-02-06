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
        printf("Case #%d: ", ++cas);
        if (a[0] + a[1] <= a[2]) {
            printf("invalid!\n");
        }
        else if (a[0] == a[1] && a[1] == a[2]) {
            printf("equilateral\n");
        }
        else if (a[0] == a[1] || a[1] == a[2]) {
            printf("isosceles\n");
        }
        else {
            printf("scalene\n");
        }
    }

    return 0;
}