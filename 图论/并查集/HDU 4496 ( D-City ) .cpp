/*
    题意：给定N(N <= 10000)个点和M( M <= 100000 )条边，求去掉前K条边时
整个图的连通分量的数目。
    题解：并查集
    将所有边保存，逆序进行并查集的操作，初始化连通分量数为n，每次对边的
两个顶点进行询问，如果本来在同一个连通分量，那么加入这条边后的分量数为
前一次的值，否则为前一次的值减1，最后将这些分量数逆序输出即可。
 
*/
#include <iostream>

using namespace std;

#define MAXN 200000

int pre[MAXN], rak[MAXN];

int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int merge(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if(rx == ry) {
        return false;
    }else {
        if( rak[rx] == rak[ry] ) {
            pre[ry] = rx;
            rak[rx]++;
        }else if( rak[rx] < rak[ry] ) {
            pre[rx] = ry;
        }else {
            pre[ry] = rx;
        }
        return true;
    }
}

int u[MAXN], v[MAXN];
int ans[MAXN];

int main() {
    int n, m;
    int i;
    while( scanf("%d %d", &n, &m) != EOF ) {
        for(i = 0; i < n; i++) {
            pre[i] = i;
            rak[i] = 0;
        }
        for(i = 0; i < m; i++) {
            scanf("%d %d", &u[i], &v[i]);
        }
        ans[0] = 0;
        ans[ ++ans[0] ] = n;
        for(i = m-1; i >= 0; i--) {
            int pre = ans[ ans[0] ];
            bool f = merge( u[i], v[i] );
            if(f) {
                ans[ ++ans[0] ] = pre - 1;
            }else {
                ans[ ++ans[0] ] = pre;
            }
        }
        for(i = ans[0] - 1; i >= 1; i--) {
            printf("%d\n", ans[i]);
        }
    }
}
/*
6 7
0 3
1 2
0 1
0 2
3 4
3 5
4 5
*/
