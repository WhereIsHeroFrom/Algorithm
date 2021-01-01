/*
并查集：统计集合数量

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

const int MAXN = 200010;
int fset[MAXN], sum[MAXN];

map <string, int> Map;

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        sum[i] = 1;
    }
    Map.clear();
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

int union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fx] = fy;
        sum[fy] += sum[fx];
        return sum[fy];
    }
    return sum[fy];
}

int n, m;

char x[100], y[100];


int findname(char *name) {
    if (Map.find(name) == Map.end()) {
        Map[name] = n++;
    }
    return Map[name];
}

int main() {
    int t, m;
    while (scanf("%d", &t) != EOF) {
        while (t--) {
            scanf("%d", &m);
            init_set(MAXN - 1);
            n = 1;
            while (m--) {
                scanf("%s %s", x, y);
                int nx = findname(x);
                int ny = findname(y);
                int ans = union_set(nx, ny);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}