#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 4750

int sg[MAXN];
int b[MAXN];

int mex(int cnt) {
    int i;
    bool vis[40];
    memset(vis, 0, sizeof(vis));
    for(i = 0; i < cnt; i++) {
        vis[sg[i] ^ 1 ^ sg[cnt-i-1]] = 1;
        if(2*i > cnt) {
            break;
        }
    }
    for(i = 0; i < cnt-1; i++) {
        vis[sg[i] ^ sg[cnt-i-2]] = 1;
        if(2*i > cnt-1) {
            break;
        }
    }
    for(i = 0; vis[i]; i++);
    return i;
}

int main() {
    int i, n, m;
    memset(sg, -1, sizeof(sg));
    sg[0] = sg[1] = 0; 
    for(i = 2; i < MAXN; i++) {
        sg[i] = mex(i);
    }
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        memset(b, 0, sizeof(b));
        for(i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--;
            b[y] |= (1<<x);
        }
        
        int start, end = 0;
        int ans = 0;
        while(1) {
            start = -1;
            for(i = end+1; i <= n; i++) {
                if(!b[i]) {
                    start = i;
                    break;
                }else if(b[i] < 3){
                    ans ^= 1;
                }
            }
            if(start == -1) {
                break;
            }
            for(i = start; i <= n; i++) {
                if(!b[i]) {
                    end = i;
                }else {
                    break;
                }
            }
            ans ^= mex(end - start + 1);
        }
        printf("Case %d: %s\n", ++cases, ans?"Alice":"Bob");
        
    }
    
    return 0;
} 

/*
1 0
2 2
3 2
4 1
5 4
6 3
7 3
8 1
9 4
10 2
11 6
12 5
13 0
*/ 
