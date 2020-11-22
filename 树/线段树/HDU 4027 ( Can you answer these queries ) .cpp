/*
lazy思想
    求和模型
        区间更新、求和。
        适用题型：
            poj 3468 A Simple Problem with Integers
        结点存储
            和sum：每个区间当前的和 
            延迟标记lazy：表示当前子树还有lazy的和未进行累加 

        接口说明
            giveLazyToSon      传递延迟标记给两个子结点（调用子结点的updateByValue，并且lazy重置）
            updateByValue      通过某个lazy值更新当前结点信息（更新sum、lazy）
            updateFromSon      通过两个子结点更新当前结点信息（更新sum）
            mergeQuery         询问时用于对分割后的子结点进行合并用，不同情况实现不同

        调用说明
            建树：              调用静态函数   treeNode::segtree_build(1, 1, n);
            插入([x, y], val)： 调用静态函数   treeNode::segtree_insert(1, 1, n, x, y, val);
            询问([x, y]):       调用静态函数   treeNode::segtree_query(1, 1, n, x, y, ans);

*/ 

#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 131072
typedef __int64 ValueType;

// 返回[l, r]和[x, y]两条线段是否相交
bool is_intersect(int l, int r, int x, int y) {
    return !(r < x || l > y);
}
// 返回[x, y]是否完全包含[l, r]
bool is_contain(int l, int r, int x, int y) {
    return x <= l && r <= y;
}

struct treeNode {
    char layer;
    ValueType sum;
    int pid;
    int l, r;
    treeNode() {
        reset(-1, 0, 0, 0);
    }
    void reset(int p, ValueType v, int _l, int _r) {
        sum = v;
        pid = p;
        layer = 0;
        l = _l, r = _r;
    }
    int lson() { return pid << 1; }
    int rson() { return pid<<1|1; }
    
    bool addValue(int v);
    void updateByValue(int v);
    void giveLazyToSon();
    void updateFromSon();

    // 询问的时候将结点合并后计入答案
    void mergeQuery(int p);

    // 建树 
    static void segtree_build(int p, int l, int r);
    // 插入线段[x, y]到[l, r]
    static void segtree_insert(int p, int l, int r, int x, int y, ValueType val);
    // 区间询问[x, y]上的信息
    static void segtree_query(int p, int l, int r, int x, int y, treeNode& ans);
    

};

/* 全局变量 
    nodes[MAXN*2] 存储所有静态线段树结点(动态开内存太费时间)
*/
treeNode nodes[MAXN*2];
ValueType srcArray[65][MAXN];
int maxDepth;

bool treeNode::addValue(int v) {
    if( layer != -1 ) {
        updateByValue( layer + v < maxDepth ? layer + v : maxDepth );
    }
    return layer != -1;
}

void treeNode::updateByValue(int _layer) {
    layer = _layer;
    sum = srcArray[layer][r] - srcArray[layer][l-1];
}

void treeNode::giveLazyToSon() {
    if( layer != -1 ) {
        nodes[ lson() ].updateByValue(layer);
        nodes[ rson() ].updateByValue(layer);
    }
}

void treeNode::updateFromSon() {
    sum = nodes[ lson() ].sum + nodes[ rson() ].sum;
    int ll = nodes[ lson() ].layer;
    int rl = nodes[ rson() ].layer;
    
    // 子树收缩 
    if ( ll  == -1 || rl == -1 ) {
        layer = -1;
    }else {
        layer = ll == rl ? ll : -1;
    }
}

void treeNode::mergeQuery(int p) {
    sum += nodes[p].sum;
}

void treeNode::segtree_build(int p, int l, int r) {
    // 创建线段树结点的时候只需要知道该线段树结点管辖区间的长度，
    // 区间端点不用存，可以在递归的时候作为函数传参
    nodes[p].reset(p, srcArray[0][l], l, r);
    if (l < r) {
        int mid = (l + r) >> 1;
        // 递归创建左右儿子结点
        treeNode::segtree_build(p<<1, l, mid);
        treeNode::segtree_build(p<<1|1, mid+1, r);
        nodes[p].updateFromSon();
    }
}

void treeNode::segtree_insert(int p, int l, int r, int x, int y, ValueType val) {
    if( !is_intersect(l, r, x, y) ) {
        return ;
    }
    if( is_contain(l, r, x, y) ) {
        if( nodes[p].addValue(1) ) {
            return ;
        }
    } 
    nodes[p].giveLazyToSon();
    int mid = (l + r) >> 1; 
    treeNode::segtree_insert(p<<1, l, mid, x, y, val);
    treeNode::segtree_insert(p<<1|1, mid+1, r, x, y, val);
    nodes[p].updateFromSon();
}

void treeNode::segtree_query(int p, int l, int r, int x, int y, treeNode& ans) {
    if( !is_intersect(l, r, x, y) ) {
        return ;
    }
    if( is_contain(l, r, x, y) ) {
        ans.mergeQuery(p);
        return;
    }
    nodes[p].giveLazyToSon();
    int mid = (l + r) >> 1; 
    treeNode::segtree_query(p<<1, l, mid, x, y, ans);
    treeNode::segtree_query(p<<1|1, mid+1, r, x, y, ans);
    nodes[p].updateFromSon();
} 


int n, m;

int main() {
    int i, j;
    int t = 0;
    while( scanf("%d", &n) != EOF ) {
        for(i = 1; i <= n; i++) {
            scanf("%I64d", &srcArray[0][i] );
        }
        maxDepth = 0;
        bool flag = true;
        while(flag) {
            flag = false;
            maxDepth ++;
            for(i = 1; i <= n; i++) {
                ValueType v;
                v = (ValueType)sqrt(1.0 * srcArray[maxDepth-1][i]);
                if ( (v+1) * (v+1) == srcArray[maxDepth-1][i] ) {
                    v++;
                }
                if(v > 1) {
                    flag = true;
                }
                srcArray[maxDepth][i] = v;
            }
        }
        
        for(i = 0; i <= maxDepth; i++) {
            for(j = 1; j <= n; j++) {
                srcArray[i][j] += srcArray[i][j-1];
            }
        }
        
        treeNode::segtree_build(1, 1, n);
        printf("Case #%d:\n", ++t);
        scanf("%d", &m);
        while( m-- ) {
            int op, a, b;
            scanf("%d %d %d", &op, &a, &b); 
            if(a > b) swap(a, b);
            if ( op == 0 ) {
                treeNode::segtree_insert(1, 1, n, a, b, 0);
            }else {
                treeNode ans;
                treeNode::segtree_query(1, 1, n, a, b, ans);
                printf("%I64d\n", ans.sum);
            }
        }
        puts("");
    }
    return 0;
}

/*
10
1 2 3 4 5 6 7 8 9 10
5
0 1 10
1 1 10
1 1 5
0 5 8
1 4 8

Case #1:
19
7
6
*/
