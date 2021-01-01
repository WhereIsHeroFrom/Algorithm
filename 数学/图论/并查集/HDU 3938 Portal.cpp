
/*
并查集 的 离线操作
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
int fset[MAXN], sum[MAXN];

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        sum[i] = 1;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

struct Edge {
    int u, v, val;

    void read() {
        scanf("%d %d %d", &u, &v, &val);
    }

    bool operator < (const Edge& o) {
        return val < o.val;
    }
}E[MAXN];

struct Len {
    int idx;
    int len;
    void read(int i) {
        idx = i;
        scanf("%d", &len);
    }
    bool operator < (const Len& o) {
        return len < o.len;
    }
}L[MAXN];

int ans[MAXN];

int val(int s) {
    return s * (s - 1) / 2;
}

int main() {
    int n, m, Q;
    int i;
    while (scanf("%d %d %d", &n, &m, &Q) != EOF) {
        init_set(n);
        for (i = 0; i < m; ++i) {
            E[i].read();
        }
        sort(E, E + m);
        for (i = 0; i < Q; ++i) {
            L[i].read(i);
        }
        sort(L, L + Q);
        int preans = 0;
        int j = 0;


        for (i = 0; i < Q; ++i) {
            for (; j < m; ++j) {
                if (E[j].val <= L[i].len) {
                    int fx = find_set(E[j].u);
                    int fy = find_set(E[j].v);

                    if (fx != fy) {
                        preans -= val(sum[fy]) + val(sum[fx]);
                        fset[fx] = fy;
                        sum[fy] += sum[fx];
                        preans += val(sum[fy]);
                    }
                }
                else break;
            }
            ans[L[i].idx] = preans;
        }


        for (i = 0; i < Q; ++i) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}