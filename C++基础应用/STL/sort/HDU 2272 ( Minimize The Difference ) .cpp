#include <iostream>

using namespace std;

struct point {
    int x;
    int index;
}p[1000];

char str[1000];

int cmp(const void *a, const void *b) {
    point *c = (point *)a;
    point *d = (point *)b;
    return c->x - d->x;
}
int main() {
    int i;
    int n;

    while(scanf("%d", &n) != EOF) {
        for(i = 0; i < n; i++) {
            scanf("%s", str);
            scanf("%d", &p[i].x);
            p[i].index = i + 1;
        }

        int sum = 0;
        qsort(p, n, sizeof(point), cmp);
        for(i = 0; i < n; i++) {
            sum += abs(p[i].x - i - 1);
        }
        printf("%d\n", sum);
    }
    return 0;
}
