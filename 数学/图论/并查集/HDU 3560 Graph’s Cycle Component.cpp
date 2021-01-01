#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define inf -1

const int MAXN = 300010;
int fset[MAXN], deg[MAXN];
vector <int> vec[MAXN];

void init_set(int n) {
    for (int i = 0; i <= n; ++i) {
        fset[i] = i;
        deg[i] = 0;
        vec[i].clear();
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
    int i, j;
    while (scanf("%d %d", &n, &m) != EOF && (n||m)) {
        init_set(n);
        for (i = 0; i < m; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            ++deg[x];
            ++deg[y];
            union_set(x, y);
        }

        for (i = 0; i < n; ++i) {
            vec[find_set(i)].push_back(i);
        }
        int comp = 0, cyc = 0;
        for (i = 0; i < n; ++i) {
            if (vec[i].size()) {
                ++comp;
                for (j = 0; j < vec[i].size(); ++j) {
                    if (deg[vec[i][j]] != 2) {
                        break;
                    }
                }
                if (j == vec[i].size()) {
                    ++cyc;
                }
            }
        }
        printf("%d %d\n", comp, cyc);
    }

    return 0;
}