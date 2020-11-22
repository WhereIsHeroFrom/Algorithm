#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 65536

typedef int ValueType;

struct treeNode {
    ValueType lazy;
    ValueType sum;
    int len;
    // int l, r; 区间端点不用存，可以在递归的时候作为函数传参 
    treeNode() {
    }
    treeNode(ValueType _sum, ValueType _lazy, int _len) {
        sum = _sum;
        lazy = _lazy;
        len = _len;
    }
    void giveLazyToSon(treeNode *lson, treeNode *rson) {
        lson->updateByValue(lazy);
        rson->updateByValue(lazy);
        lazy = 0;
    }
    void updateByValue(ValueType _val) {
        lazy += _val;
        sum += _val * len;
    }
    void updateFromSon(treeNode *lson, treeNode *rson) {
        sum = lson->sum + rson->sum;
    }
    
}nodes[MAXN*2];

ValueType srcArray[MAXN];

void segtree_build(int p, int l, int r) {
    nodes[p] = treeNode( srcArray[l], 0, (r-l+1) );
    if (l < r) {
        int mid = (l + r) >> 1;
        segtree_build(p<<1, l, mid);
        segtree_build(p<<1|1, mid+1, r);
        nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
    }
}

// [x, y]区间上每个点都加上一个值val 
void segtree_add(int p, int l, int r, int x, int y, ValueType val) {
    if(y < l || x > r || x > y) return ;
    if(x <= l && r <= y) {
        nodes[p].updateByValue(val);
        return ;
    } 
    nodes[p].giveLazyToSon( &nodes[p<<1], &nodes[p<<1|1] );
    int mid = (l + r) >> 1; 
    segtree_add(p<<1, l, mid, x, y, val);
    segtree_add(p<<1|1, mid+1, r, x, y, val);
    nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
}

// 询问区间[x, y]所有值的和
void segtree_query(int p, int l, int r, int x, int y, ValueType& sum) {
    if(y < l || x > r || x > y) return ;
    if(x <= l && r <= y) {
        sum += nodes[p].sum;
        return;
    }
    nodes[p].giveLazyToSon( &nodes[p<<1], &nodes[p<<1|1] );
    int mid = (l + r) >> 1; 
    segtree_query(p<<1, l, mid, x, y, sum);
    segtree_query(p<<1|1, mid+1, r, x, y, sum);
    nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
} 

#define INVALID_NODE -1

struct treeChain {
    // 树链剖分结构 
    // father 该结点对应树的父亲 
    // son    重链上的子结点
    // depth  对应树的深度
    // size   以该结点为根的子树的结点个数 
    int father, son, depth, size;
    
    // top    当前结点所在重链的链表头
    // idx    当前结点和父结点的那条边在 离散后的 数组中的 下标 
    int top, idx; 
    treeChain() {
    }
    treeChain(int _fat, int _dep) {
        father = _fat;
        depth = _dep;
        size = 1;
        son = INVALID_NODE;
    }
    
    void Print() {
        // base info
        printf(" father = %d son = %d depth = %d size = %d top = %d idx = %d\n", father, son, depth, size, top, idx);
    }
}TC[MAXN];
int treeChainIdx;

struct edgeData {
    int u, v, val;
    int next;
    edgeData() {
    }
    edgeData(int _u, int _v, int _val, int _next) {
        u = _u;
        v = _v;
        val = _val;
        next = _next;
    } 
}edge[2*MAXN];
int head[MAXN], edgeCount;

void graphInit() {
    edgeCount = 0;
    treeChainIdx = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int val = 0) {
    edge[ edgeCount ] = edgeData(u, v, val, head[u]);
    head[u] = edgeCount ++;
}

void addEdge2(int u, int v, int val = 0) {
    addEdge(u, v, val), addEdge(v, u, val);
}
 
void treeChain_preDfs(int u, int fat, int depth) {         
    TC[u] = treeChain(fat, depth);                         // 初始化u结点的树链结构体
    for (int e = head[u]; e != -1; e = edge[e].next) {     // 采用链式前向星存储边结构 
        int v = edge[e].v;                                 // 枚举任意一个和u相连的结点v 
        if(v != fat) {                                     // 考虑无向树,建边的时候建的双向边，所以要去掉树中"回边"的情况 
            treeChain_preDfs(v, u, depth+1);               // 递归计算u的子树v 
            TC[u].size += TC[v].size;                      // 统计结点u的size信息 
            
            if( TC[u].son == INVALID_NODE || \
                TC[v].size > TC[ TC[u].son ].size ) {
                TC[u].son = v;                             // 利用各个子结点的size信息计算重儿子 
            }
        }
    }
}

void treeChain_postDfs(int u) {
    
    if( TC[u].father == INVALID_NODE ) {                   // 这种情况下，u为根结点 
        TC[u].top = u;                                     //     则 重链的链表头为它本身 
    }else {
        TC[u].idx = ++treeChainIdx;                        // (father[u], u)这条边映射到线性表的下标为 ++treeChainIdx
        if( TC[TC[u].father].son == u ) {                  // 如果u为重儿子， 
            TC[u].top = TC[TC[u].father].top;              //     则 重链链表头 继承它父亲的 重链链表头
        }else { 
            TC[u].top = u;                                 // 如果u为轻儿子，重链链表头等于本身 
        }
    }
    
    if( TC[u].son != INVALID_NODE ) {                      // 优先遍历重儿子 
        treeChain_postDfs(TC[u].son);
    }
    for (int e = head[u]; e != -1; e = edge[e].next) {
        int v = edge[e].v;
        if(v == TC[u].father || v == TC[u].son) continue; // 排除重儿子和父结点的情况 
        treeChain_postDfs(v);                             // 递归计算u的子树v
    }
}

void treeChain_build(int n, int* nodeVal) {
    // 因为是点权值，需要引入虚拟根0；如果是边权值则不需要 
    addEdge2(0, 1);
    treeChain_preDfs(0, INVALID_NODE, 0);
    treeChain_postDfs(0);
    for(int i = 1; i <= n; i++) {
        srcArray[ TC[i].idx ] = nodeVal[i];
    }
    segtree_build(1, 1, n);    
}

void treeChain_update_func(int n, int l, int r, ValueType data) {
    // 具体得线性结构是线段树、树状数组 或者其它... 
    if (l > r) swap(l, r);
    segtree_add(1, 1, n, l, r, data);
}

ValueType treeChain_query_func(int n, int l, int r) {
    ValueType val = 0;
    segtree_query(1, 1, n, l, r, val);
    return val;
}

void treeChain_update(int n, int x, int y, ValueType data) {
    bool flag = false;
    while(x != y) {
        if(TC[x].top == TC[y].top) {
            // x和y在同一条重链上，所以他们在线性表的映射上是连续的，可以直接采用数据结构进行更新 
            treeChain_update_func(n, TC[x].idx, TC[y].idx, data);
            return ;
        }else {
            // x 的 重链链表头 一定是深度大的那个 
            if(TC[ TC[x].top ].depth < TC[ TC[y].top ].depth) {
                swap(x, y);
            }
            int tx = TC[x].top;
            
            if(x == tx) {
                // x本身就是重链的链表头 或者 叶子结点 
                treeChain_update_func(n, TC[x].idx, TC[x].idx, data);
                x = TC[x].father;
            }else {
                treeChain_update_func(n, TC[tx].idx+1, TC[x].idx, data);
                x = tx;
            }
        }
    }
    treeChain_update_func(n, TC[x].idx, TC[x].idx, data);    
}

int n, m, Q;
int val[MAXN];
char str[10];

int main() {
    int i;
    while( scanf("%d %d %d", &n, &m, &Q) != EOF ) {
        for(i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        graphInit(); 
        while(m--) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge2(x, y);
        }
        treeChain_build(n, val);
        while( Q-- ) {
            scanf("%s", str);
            if(str[0] == 'I' || str[0] == 'D') {
                int x, y, z;
                scanf("%d %d %d", &x, &y, &z);
                if(str[0] == 'D') {
                    z = -z;
                }
                treeChain_update(n, x, y, z); 
            }else {
                int x;
                scanf("%d", &x);
                printf("%d\n", treeChain_query_func(n, TC[x].idx, TC[x].idx) );
            }
        }
    }
    return 0;
}
/*
9 8 100
1 2 3 4 5 6 7 8 9
1 2
1 3
2 8
2 9
3 4
3 5
5 6
5 7
I 6 9 -5

in :
3 2 51
1 2 3
2 1
2 3
I 1 3 5
Q 1 
Q 2
Q 1 
Q 3
D 1 2 2
Q 1 
Q 3
out :
7 4 8
*/
