#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 210

int n, m, k;
char str[100010];
int dist[2][MAXN][MAXN];
int num[100010];
int costs[2];

void get_num(char *str, int *num, int k) {
    num[0] = 0;
    int i, s = 0;
    for(i = 0; str[i]; ++i) {
        if(str[i] >= '0' && str[i] <= '9') {
            s = s * 10 + str[i] - '0';
        }else {
            if(s) {
                num[ ++num[0] ] = s;
                s = 0;
            }
        }
    }
    if(s) {
        num[ ++num[0] ] = s;
        s = 0;
    }
    
    for(i = 1; i < num[0]; ++i) {
        int u = num[i], v = num[i+1];
        
        if(k >= 0 && dist[0][u][v] == -1) {
            dist[0][u][v] = 1;
        }
        
        if(k >= 1 && dist[1][u][v] == -1) {
            dist[1][u][v] = 1;
        }
    }


}

int d[MAXN], vis[MAXN];
int getDist(int idx, int start, int end) {
    memset(d, -1, sizeof(d));
    memset(vis, 0, sizeof(vis));
    int i;
    d[start] = 0;
    while(1) {
        int Min = 100000000, u = -1;
        for(i = 1; i <= n; i++) {
            if(vis[i] || d[i] == -1) {
                continue;
            }
            if(d[i] < Min) {
                u = i;
                Min = d[u];
            }        
        }
        if(u == -1) {
            break;
        }
        vis[u] = 1;
        for(i = 1; i <= n; ++i) {
            if(vis[i]) continue;
            int &val = dist[idx][u][i];
            if(val == -1) continue;
            
            if(Min + val < d[i] || d[i] == -1) {
                d[i] = Min + val;
            }
        }
    } 
    if(d[end] == -1) {
        return -1;
    }
    return costs[idx] * d[end];
}

int Min(int a, int b) {
    if(a == -1) return b;
    if(b == -1) return a;
    return a < b ? a : b;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        memset(dist, -1, sizeof(dist));
        scanf("%d %d", &n, &m);
        while(m--) {
            scanf("%s %d", str, &k);
            get_num(str, num, k);
        }
        scanf("%d %d", &costs[0], &costs[1]);
        
        int start, end;
        scanf("%d %d", &start, &end);
        int ans = Min( getDist(0, start, end), getDist(1, start, end) );
        printf("%d\n", ans); 
    }
    return 0;
}
