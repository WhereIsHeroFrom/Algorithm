/*
并查集：统计最大的集合

*/

#include <iostream>

const int MAXN = 10000010;
int fset[MAXN], sum[MAXN];

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        sum[i] = 0;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fx] = fy;
        return true;
    }
    return false;
}

int n, m;

int main() {
    int x, y;
    int i;
    while (scanf("%d", &n) != EOF) {
        init_set(MAXN - 1);
        int m = n;
        while (m--) {
            scanf("%d %d", &x, &y);
            union_set(x, y);
        }

        int Max = 0;
        for (i = 1; i < MAXN; ++i) {
            int &p = sum[find_set(i)];
            ++p;
            if (p > Max) {
                Max = p;
            }
        }

        printf("%d\n", Max);
    }
    return 0;
}