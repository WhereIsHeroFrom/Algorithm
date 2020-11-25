#include <iostream>
#include <queue>

using namespace std;

#define MAXN 10010

int d[MAXN], T;
int pre[MAXN], val[MAXN];

int n, k;
int sta[16];

int Q[2000000], front, rear;
int ans[1000000], lastAns[1000000];

bool isSmallthan(int *nowAns, int *preAns) {
    if(nowAns[0] != preAns[0]) {
        return nowAns[0] < preAns[0];
    }
    
    for(int i = nowAns[0]; i >= 1; i--) {
        if( nowAns[i] != preAns[i] ) {
            return nowAns[i] < preAns[i];
        }
    }
    return false;
}

bool bfs() {
    T ++;
    front = rear = 0;
    
    Q[ rear++ ] = 0;
    
    int i;
    while( front < rear ) {
        int now = Q[front++];
        if(now == 0 && front != 1) {
            // Êä³öÂ·¾¶
            ans[0] = 0;
            while( !ans[0] || now ) {
                ans[ ++ans[0] ] = val[now];
                now = pre[now];
            }
            
            if( isSmallthan(ans, lastAns) ) {
                lastAns[0] = ans[0];
                for(i = 1; i <= lastAns[0]; i++) {
                    lastAns[i] = ans[i];
                    //printf("%d", ans[i]);
                }
            //    puts("");
            }
            return true;
        }
        
        for(i = 1; i <= sta[0]; i++) {
            if(!sta[i] && front==1) continue;
            
            int next = (now * k + sta[i]) % n;
            if( d[next] != T ) {
                d[next] = T;
                Q[rear++] = next;
                pre[next] = now;
                val[next] = sta[i];
            }
        }
    }
    return false;
}

bool flag;

void dfs(int start, int depth, int maxDepth) {
    if(k-start < maxDepth - depth) {
        return ;
    }
    int i;
    
    if(maxDepth == depth) {
        /*for(i = sta[0]; i >= 1; i--) {
            printf("%d", sta[i]);
        }
        puts("");*/
        if( bfs() ) {
            flag = 1;
        }
        return ;
    }
    for(i = start; i < k; i++) {
        sta[ ++sta[0] ] = i;
        dfs(i+1, depth+1, maxDepth);
        --sta[0];
    }
}

int main() {
    int i;
    while( scanf("%d %d", &n, &k) != EOF ) {
        lastAns[0] = 100000000;
        for(i = 1; ; i++) {
            sta[0] = 0;
            flag = false;
            dfs(0, 0, i);
            if (flag) break;
        }
        for(i = lastAns[0]; i >= 1; i--) {
            printf("%d", lastAns[i]);
        }
        puts("");
    }
    return 0;
}

/*
9987 2
9977 2
*/
