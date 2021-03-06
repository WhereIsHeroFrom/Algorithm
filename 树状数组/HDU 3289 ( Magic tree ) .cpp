/*
    将树利用先序遍历转成连续的序列后用树状数组进行统计求和
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAXN 200010
#define MAXM 400020
#define LL long long

struct Edge {
    int v, next;
    Edge() {}

    Edge(int _v, int _next) {
        v = _v;
        next = _next;
    }
}E[MAXM];

int tot, head[MAXN];
LL c[MAXN];


void addEdge(int x, int y) {
    //printf("<%d, %d>\n", x, y);
    E[tot] = Edge(y, head[x]);
    head[x] = tot++;
}

int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int cnt) {
    while(x <= n) {
        c[x] += cnt;
        x += lowbit(x);
    }
}

LL get_sum(int x) {
    LL s = 0;
    while(x > 0) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}

int code[MAXN], id;
int sum[MAXN];

int dfs(int root, int fat) {
    code[root] = ++id;
    sum[root] = 1;
    for(int e = head[root]; e != -1; e = E[e].next) {
        int v = E[e].v;
        if(v != fat) {
            sum[root] += dfs(v, root);
        }
    }
    return sum[root];
}


struct valEdge {
    int u, v, val;

    void read() {
        scanf("%d %d %d", &u, &v, &val);
    }

    void output() {
        printf("%d %d %d\n", u, v, val);
    }
    bool operator<(const valEdge& other) {
        return val > other.val;
    }
}VE[MAXM];
int p[MAXN];

void init() {
    tot = 0;
    int i;
    memset(head, -1, sizeof(head));
    memset(c, 0, sizeof(c));
    for(i = 0; i <= n; ++i) p[i] = i;
}

int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

bool union_set(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if(fu != fv) {
        p[fu] = fv;
        return true;
    }
    return false;
}

int main() {
    int i;
    int m;
    while(scanf("%d %d", &n, &m) != EOF) {
        init();
        for(i = 0; i < m; ++i) {
            VE[i].read();
        }
        sort(VE, VE + m);
        //for(i = 0; i < m; ++i) VE[i].output();
        
        int cnt = 0;
        for(i = 0; i < m; ++i) {
            if(union_set( VE[i].u, VE[i].v ) ) {
                addEdge(VE[i].u, VE[i].v);
                addEdge(VE[i].v, VE[i].u);
                ++cnt;
            }
            if(cnt == n-1) {
                break;
            }
        }
        id = 0;
        dfs(1, 0);

        scanf("%d", &m);
        while(m--) {
            char cmd[10];
            int x, y;
            scanf("%s %d", cmd, &x);
            if(cmd[0] == 'G') {
                scanf("%d", &y);
                add(code[x], y);
            }else if(cmd[0] == 'C'){
                LL s = get_sum(code[x]) - get_sum(code[x]-1);
                add(code[x], -s);
            }else {
                LL s = get_sum(code[x]+sum[x]-1) - get_sum(code[x]-1);
                printf("%lld\n", s);
            }
        }
    }
    return 0;
}

/*
4 7
1 2 1
3 1 2
2 4 3
2 3 6
1 4 5
3 4 4
1 2 8


10 9
1 2 1 
1 3 1
1 6 1
3 4 1
3 5 1
6 7 1
6 8 1
5 9 1
10 5 1

100
Q 1
Q 2
Q 3
Q 4
Q 5
Q 6
Q 7
Q 8
Q 9
Q 10
C 1
C 2
C 3
C 4
C 5
C 6
C 7
C 8
C 9
C 10
G 1 1
G 2 2
G 3 3
G 4 4
G 5 5
G 6 6
G 7 7
Q 1
Q 2
Q 3
Q 4
Q 5
Q 6
Q 7
Q 8
Q 9
Q 10


2 4
1 2 3
2 1 4
1 2 6
2 1 56

10
G 1 12
G 2 1212
C 1
Q 1
Q 2
C 2
Q 1
Q 2
*/
