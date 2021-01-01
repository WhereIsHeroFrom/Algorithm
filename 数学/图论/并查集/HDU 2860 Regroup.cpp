#include <iostream>
#include <cstring>

using namespace std;

#define inf -1

const int MAXN = 300010;
int fset[MAXN];
int minv[MAXN];

void init_set(int n) {
    for (int i = 0; i <= n; ++i) {
        fset[i] = i;
        minv[i] = inf;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

int Min(int a, int b) {
    if (a == inf) return b;
    if (b == inf) return a;
    return a < b ? a : b;
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fx] = fy;
        minv[fy] = Min(minv[fx], minv[fy]);
        return true;
    }
    return false;
}

int n, k, m;

int main() {
    while (scanf("%d %d %d", &n, &k, &m) != EOF) {
        init_set(n);
        while (k--) {
            int r, c;
            scanf("%d %d", &r, &c);
            minv[c] = Min(minv[c], r);
        }
        while (m--) {
            char ch[10];
            int x, y;
            scanf("%s", ch);
            if (!strcmp(ch, "GT")) {
                scanf("%d", &x);

                if (fset[x] == x) {
                    if (minv[x] == inf) {
                        printf("Company %d is empty.\n", x);
                    }
                    else
                        printf("Lowest rate: %d.\n", minv[x]);
                }
                else {
                    printf("Company %d is a part of company %d.\n", x, find_set(x));
                }
            }
            else if (!strcmp(ch, "AP")) {
                scanf("%d %d", &x, &y);
                if (fset[y] != y) {
                    printf("Reject\n");
                    continue;
                }
                int fy = find_set(y);
                minv[fy] = Min(minv[fy], x);
                printf("Accept\n");
            }
            else {
                scanf("%d %d", &x, &y);
                if (fset[x] != x || fset[y] != y) {
                    printf("Reject\n");
                    continue;
                }

                if (union_set(y, x)) {
                    printf("Accept\n");
                }
                else {
                    printf("Reject\n");
                }
            }

        }

        puts("");
    }

    return 0;
}