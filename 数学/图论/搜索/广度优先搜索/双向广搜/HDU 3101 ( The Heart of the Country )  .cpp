#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010

int n, k;
vector <int> edges[MAXN];
int troops[MAXN];
int total[MAXN];

int main() {
    int i, j;
    int m;
    
    while(scanf("%d %d", &n, &k) != EOF) {
        if(!n && !k) {
            break;
        }
        int all = 0, cryCnt = n;
        for(i = 0; i < n; ++i) {
            scanf("%d", &troops[i]);
            all += troops[i];
            edges[i].clear(); 
            scanf("%d", &m);
            while(m--) {
                int v;
                scanf("%d", &v);
                edges[i].push_back(v);
            } 
        }
        for(i = 0; i < n; ++i) {
            total[i] = troops[i];
            for(j = 0; j < edges[i].size(); ++j) {
                total[i] += troops[edges[i][j]];
            }
        }
        queue <int> Q;
        
        for(i = 0; i < n; ++i) {
            if(total[i] < k) {
                all -= troops[i];
                -- cryCnt;
                Q.push(i);
                total[i] = -1;
            }
        }
        
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            
            for(i = 0; i < edges[u].size(); ++i) {
                int v = edges[u][i];
                if(total[v] == -1) {
                    continue;
                }
                total[v] -= troops[u];
                if(total[v] < k) {
                    all -= troops[v];
                    -- cryCnt;
                    Q.push(v);
                    total[v] = -1;
                }
            }
        }
        
        printf("%d %d\n", cryCnt, all);
    }
    return 0;
}

