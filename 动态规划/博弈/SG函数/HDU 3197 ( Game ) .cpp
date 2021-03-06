#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 1010

vector <int> edges[MAXN];
int fat[MAXN];

int dfs(int u) {
    int i;
    int sg = 0;
    for(i = 0; i < edges[u].size(); ++i) {
        sg ^= (dfs(edges[u][i]) + 1);
    }
    return sg;
}

int main() {
    int i, n;
    while(scanf("%d", &n) != EOF) {
        for(i = 0; i < n; ++i) edges[i].clear();
        for(i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            fat[i] = x;
            if(x != -1) {
                edges[x].push_back(i);
            }
        }
        int ans = 0;
        for(i = 0; i < n; ++i) {
            if(fat[i] == -1) {
                ans ^= dfs(i);
            }
        }
        printf("%s\n", ans==0? "NO": "YES");
    }
    return 0;
}
