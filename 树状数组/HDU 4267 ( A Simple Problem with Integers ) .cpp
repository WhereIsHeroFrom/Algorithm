#include <iostream>

using namespace std;

#define MAXN 50010

int c[56][MAXN];
int sumd[11];

int n;

// 获取需要更新哪个树状数组 
int getTreeArrayIndex(int start, int k) {
    return sumd[k-1] + (start%k);
}

int lowbit(int x) {
    return x & -x;
}

__int64 sum(int treeArrayIdx, int x) {
    __int64 s = 0;
    while(x) {
        s += c[treeArrayIdx][x];
        x ^= lowbit(x);
    }
    return s;
}

void add(int treeArrayIdx, int x, int value) {
    while(x <= n) {
        c[treeArrayIdx][x] += value;
        x += lowbit(x);
    }    
}

void doAdd(int s, int e, int k, int v) {
    int treeArrayIdx = getTreeArrayIndex(s, k);
    add( treeArrayIdx, s, v );
    add( treeArrayIdx, e+1, -v );
}

int main() {
    int i, j;
    int Q, tp;
    int s, e, k, v, x;
    sumd[0] = 0;
    for(i = 1; i <= 10; i++) {
        sumd[i] = sumd[i-1] + i;
    }
    
    while( scanf("%d", &n) != EOF ) {
        for(i = 0; i < 56; i++) {
            for(j = 1; j <= n; j++) c[i][j] = 0;
        }
        for(i = 1; i <= n; i++) {
            scanf("%d", &x);
            doAdd(i, i, 1, x);
        }
        scanf("%d", &Q);
        while(Q--) {
            scanf("%d", &tp);
            if(tp == 1) {
                scanf("%d %d %d %d", &s, &e, &k, &v);
                doAdd(s, e, k, v);
            }else {
                scanf("%d", &v);
                __int64 s = 0;
                for(i = 1; i <= 10; i++) {
                    s += sum(v%i + sumd[i-1], v);
                }
                printf("%I64d\n", s);
            }
        }
        
    }
    
}

/*
4 
1 1 1 1
5
1 1 4 2 1
2 1
2 2
2 3
2 4
*/
