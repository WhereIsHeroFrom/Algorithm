#include <iostream>
#include <cstdio>
using namespace std;

#define MAXN 500010
#define INF -1

struct edgeValue {
    int v, val;
    int next;
    edgeValue(): next(-1) {}
    edgeValue(int _v, int _val, int _next) {
        v = _v;
        val = _val;
        next = _next;
    }
}E[MAXN];

int head[MAXN], tot;
int n, L, R;

void addEdge(int x, int y, int z) {
    E[tot] = edgeValue(y, z, head[x]);
    head[x] = tot++;
}

int dfs(int s, int l, int r, int u) {
    if(r < 0) {
        return INF;
    }
    if(head[u] == -1) {
        return l <= 0 && 0 <= r ? 0 : INF;
    }
    int i;
    int mmax = INF, mmin = INF;
    for(i = head[u]; ~i; i = E[i].next) {
        edgeValue &ev = E[i];
        int vval = dfs(1-s, l - ev.val, r - ev.val, ev.v);
        if(vval == INF) {
            continue;
        }
        vval += ev.val;
        if(s == 0) {
            if(mmax == INF || vval > mmax) mmax = vval;
        }else {
            if(mmin == INF || vval < mmin) mmin = vval;
        }
    }
    if(s == 0) {
        return mmax;
    }else {
        return mmin;
    }
}

char strBuffer[1100];

int main() {
    int i, j;
    while( scanf("%d %d %d", &n, &L, &R) != EOF ) {
        tot = 0;
        int tval = 0;
        memset(head, -1, sizeof(head));
        getchar();
        for(i = 0; i < n-1; ++i) {
            int x[30];
            //scanf("%d %d %d", &x, &y, &z);
            gets(strBuffer);
             int s = -1, idx = 0;
            j = 0;
            while(strBuffer[j]) {
                if(strBuffer[j] >= '0' && strBuffer[j] <= '9') {
                    if(s == -1) {
                        s = strBuffer[j] - '0';
                    }else {
                        s = s * 10 + (strBuffer[j] - '0');
                    }
                }else {
                    if(s != -1) {
                        x[idx++] = s;
                        s = -1;
                    }
                }
                ++j;
            }
            if(s != -1) {
                x[idx++] = s;
                s = -1;
            }

            addEdge(x[0], x[1], x[2]);
            tval += x[2];
        }
        int ans = dfs(0, L, R, 0);
        if(ans == INF) {
            printf("Oh, my god!\n");
        }else 
            printf("%d\n", ans);
    }
    return 0;
}
/*

7 2 8
0    1 1  
0   2 1  
1    3 1  
1 4    10  
2    5   1
2   6   5   

7 101 102
0 1 100
0 2 2
1 3 1
1 4 2
2 5 3
2 6 4

7 10 20
0 1 6
0 2 7
0 3 8 
0 4 15
0 5 19
0 6    21
*/

