#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN (100010)
#define MAXQ 100010
#define LOGMAXN 17
#define MAXNODE (MAXN*2 + MAXN*LOGMAXN)

// MAXNODE 表示总结点数，由以下几部分组成
//         1、MAXN*2           第一棵空树的结点数
//         2、MAXN*LOGMAXN     后N棵树，每棵树新加入 LOGMAXN 个结点

struct treeNode {
    int sum;                 // 数据和 
    int cnt;                 // 数据个数 
    int lson, rson;          // 左右儿子编号      
    // int l, r;             // 左右区间在递归的时候可以计算出来，这里为了节省空间不予保存
   
    treeNode() {
        reset();
    }
    treeNode(int _s, int _c) {
        sum = _s;
        cnt = _c;
    }
    
    void reset() {
        sum = cnt = 0;
        lson = rson = 0;
    }
   
    void setson(int _lson, int _rson) {
        lson = _lson;
        rson = _rson;
    }
   
}tNode[MAXNODE];     // 主席树结点
int T[MAXN];         // T[i]表示第i棵主席树的根结点编号，下标从1-N，其中 T[0] 指向的是一棵数据域全为0的空数据树
int C[MAXN];         // C[i]表示第i棵主席修改树的根结点编号，该数组本身满足树状数组性质
int L;               // L 离散化后的数据范围为 [1, L]
int totalNodes;

void init() {
    L = 1;
    totalNodes = 0;
}

treeNode *getNode(int id) {
    return &tNode[id];
}

// build chair tree
void build_cmtree(int &x, int l, int r) {
    x = ++totalNodes;
    getNode(x)->reset();
    if(l < r) {
        int mid = (l + r) >> 1;
        treeNode *rt = getNode(x);
        build_cmtree(rt->lson, l, mid);
        build_cmtree(rt->rson, mid+1, r);
    }
}

// insert chair tree
// root      前一棵主席树的游标结点
// newroot   当前构建的主席树的游标结点
// pos 插入的值
// cnt 插入值的数量，一般取1或-1 分别表示 插入一个数 和 删除一个数
int insert_cmtree(int root, int pos, int cnt) {
    int ret = ++totalNodes;
    int l = 1, r = L;
   
    treeNode *newroot = getNode(ret);
    treeNode *oldroot = getNode(root);
   
    // root 为根的旧树 和 newroot为根的新树，结构是一样的，
    // 每次通过pos的值选择进入左子树或右子树，当root进入左子树时，newroot也进入左子树，反之亦然，让两个游标在各自树上的相对位置保持一致
    newroot->cnt = oldroot->cnt + cnt;
    newroot->sum = oldroot->sum + pos;
    
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            // val的值小于l + r的中值，说明修改量发生在x的左子树上
            // 所以x的左子树需要生成一个新的结点，而x的右子树继承y的右子树
            newroot->setson( ++totalNodes, oldroot->rson );
           
            // 将x变成x的左子树，y变成y的左子树，继续迭代
            newroot = getNode(newroot->lson);
            oldroot = getNode(oldroot->lson);
            // 区间缩减一半
            r = mid;
        } else {
            // val的值大于等于l + r的中值，说明修改量发生在x的右子树上
            // 所以x的右子树需要生成一个新的结点，而x的左子树继承y的左子树
            newroot->setson( oldroot->lson, ++totalNodes );
                     
            // 将x变成x的右子树，y变成y的右子树，继续迭代
            newroot = getNode(newroot->rson);
            oldroot = getNode(oldroot->rson);
            // 区间缩减一半
            l = mid + 1;
        }
        // 更新新树当前结点的修改量
        newroot->cnt = oldroot->cnt + cnt;
        newroot->sum = oldroot->sum + pos;
    }

    return ret;
}

//###### 前方 主席树 模板 
//############################################################################################## 

/*
LCA 转化为 RMQ
       首先要有一棵树，以7个顶点，6条边为例:
              7
              (0,5) (5,2) (2,4) (3,0) (1,3) (3,6)
       1)如果根结点不确定，那么定义0为根结点，然后从根结点开始进行一次深度优先遍历，原有边是M条，那么一次遍历完毕就会有2M条边。
              (0,5) -> (5,2) -> (2,4) -> (4,2) -> (2,5) -> (5,0) -> (0,3) -> (3,1) -> (1,3) -> (3,6) -> (6,3) -> (3,0)
       2)由于相邻两条边的端点是一样的，所以可以压缩到一个一维数组E (edge)中：
              E[i] = 0 5 2 4 2 5 0 3 1 3 6 3 0
         将E数组中对应点在树上的深度记录在数组D (depth)中：
              D[i] = 0 1 2 3 2 1 0 1 2 1 2 1 0
       3)将每个点在E数组中第一次出现的位置记录在I (index)中：
              I[i] = 0 8 2 7 3 1 10
       4) 然后得到结点x和y的最近公共祖先：
              LCA(x, y) = E[ RMQ_MIN( D, I[x], I[y] ) ]
*/
#define MAXL 18

class Edge {
    public:
        int u, v;
        int next;
        int val;   // 有些题目的边是有权值的
        Edge() {}
        Edge( int _u, int _v, int _val, int _next) {
            u = _u;
            v = _v;
            val = _val;
            next = _next;
        }
}edges[ 2*MAXN ];           // LCA 求解树的最近公共祖先，需要用到双向边，所以边数为 2*(n-1)
int head[ MAXN ], tot;      // 邻接表的head结点 
int I[MAXN];                // I下标，每个结点在E数组中第一次出现的位置 
int RMQ_N;

class LCAData {
public:
        int E, D;

       LCAData() {

       }
       LCAData( int _e, int _d) {
              E = _e;
              D = _d;
       }
}ld[2*MAXN];

void LCA_init() {
   memset(head, -1, sizeof(head));
   memset(I, -1, sizeof(I));
   tot = 0;
   RMQ_N = 0;
}

void addEdge(int u, int v, int val) {
    edges[tot] = Edge(u, v, val, head[u]);
    head[u] = tot++;
}

// 生成E、D数组 递归版 
void LCA_Dfs(int fat, int u, int depth) {
    if(I[u] == -1) I[u] = RMQ_N;

    ld[RMQ_N++] = LCAData(u, depth);
    for( int i = head[u]; i != -1; i = edges[i].next) {
        if(edges[i].v == fat) {
            continue;
        }
        LCA_Dfs(u, edges[i].v, depth + 1);
        ld[RMQ_N++] = LCAData(u, depth);
   }
}

typedef Edge stackItem;

stackItem lcaStack[2*MAXN];
int newhead[MAXN];
int top;

// 生成E、D数组 非递归版 
void LCA_NonDfs(int root) {
    for(int i = 0; i < MAXN; i++) newhead[i] = head[i];
    
    top = 0;
    lcaStack[top++] = stackItem(-1, root, -1, -1);
    while(top) {
        stackItem st = lcaStack[top-1];
        int u = st.v;
        
        if(I[u] == -1) I[u] = RMQ_N;
        ld[RMQ_N++] = LCAData(u, top-1);
        int end = true;
        for( int i = newhead[u]; i != -1; i = edges[i].next) {
            if( edges[i].v == st.u ) {
                continue;
            }
            lcaStack[top++] = stackItem(edges[i].u, edges[i].v, -1, -1);
            newhead[u] = edges[i].next;
            end = false;
            break;
        }
        if(end) top--;
    }
}

// 该RMQ模板只用于求最小值，若要求最大值只需要将原数组取相反数，然后结果再取相反数即可
class RMQData {
public:
        int index;
        int val;
}rd[2*MAXN];

int Log2[2*MAXN];        // Log2[i] = log2(i)
int f[2*MAXN][MAXL];     // f[i][j] 表示 [i, (i + 2^j) - 1]这个区间的最小值 对应数的下标
                         // f[i][j] = min{ f[i][j-1] , f[ i + 2^(j-1) ][j-1] }

void RMQ_Init() {
    int i, j, p;
    
    // 计算log以2为底的i的对数 log2(i)
    Log2[1] = 0;
    for(i = 2; i <= RMQ_N; i++) {
        Log2[i] = Log2[i-1];
        if( 1<<(Log2[i] + 1) == i ) {
            Log2[i] ++;
        }
    }
    for(j = 0; j < MAXL; j++) {
        for(i = 0; i < RMQ_N; i++) {
            if(j == 0) {
                f[i][0] = i;
            } else {
                f[i][j] = f[i][j-1];
                p = i + (1<<(j-1));
                if(p < RMQ_N) {
                    if( rd[ f[p][j-1] ].val < rd[ f[i][j] ].val ) {
                        f[i][j] = f[p][j-1];
                }
            }                          
        }
    }
}
}

// 询问的时候拆成两个长度为2^k的区间
// f[l][k] 和 f[r-2^k+1][k]
// 并且k的取值要求能够使得 [l,l+2^k-1] 和 [r-2^k+1,r] 的并集 为 [l, r]
// 于是 k为满足l+2^k-1 <= r并且值最大，即2^k <= r-l+1
// k <= log2(r-l+1), 又k为整数，所以k为log2(r-l+1)的下取整
int RMQ_Query(int l, int r) {
    if(l > r) {
        int tmp = l; l = r; r = tmp;
    }
    int k = Log2[r - l + 1];
    return rd[ f[l][k] ].val < rd[ f[r-(1<<k)+1][k] ].val ? f[l][k] : f[r-(1<<k)+1][k];
}


void LCA_To_RMQ() {
    int i;
    for(i = 0; i < RMQ_N; i++) {
        rd[i].val = ld[i].D;
        rd[i].index = i;
    }
    RMQ_Init();
}

int LCA_Query(int x, int y) {
    int l = I[x];
    int r = I[y];
    return ld[ RMQ_Query(l, r) ].E;
}

//###### 前方 LCA 模板 
//############################################################################################## 


int getIdx(int cap) {
    return cap + 1;
}

void dfs(int fat, int u) {
    for(int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].v;
        int val = edges[e].val;
        
        if(v == fat) continue;
        
        T[v] = insert_cmtree(T[u], getIdx(val), 1);
        dfs(u, v);
    }
}

void calc_cmtree(int root) {
    for(int i = 0; i < MAXN; i++) newhead[i] = head[i];
    
    top = 0;
    lcaStack[top++] = stackItem(-1, root, -1, -1);
    while(top) {
        stackItem st = lcaStack[top-1];
        int end = true;
        for( int i = newhead[st.v]; i != -1; i = edges[i].next) {
            if( edges[i].v == st.u ) {
                continue;
            }
            lcaStack[top++] = stackItem(edges[i].u, edges[i].v, -1, -1);
            newhead[st.v] = edges[i].next;
            end = false;
            
            T[ edges[i].v ] = insert_cmtree(T[edges[i].u], getIdx(edges[i].val), 1);
            break;
        }
        if(end) top--;
    }    
}

int minv(int a, int b) {
    return a < b ? a : b;
}

int getlson(int id) {
    return getNode(id)->lson;
}
int getrson(int id) {
    return getNode(id)->rson;
}

treeNode getSum(int s, int t, int l, int r, int a, int b, int c) {
    if(s == l && t == r) {
        
        treeNode nd;
        nd.sum = getNode(a)->sum + getNode(b)->sum - 2 * getNode(c)->sum;
        nd.cnt = getNode(a)->cnt + getNode(b)->cnt - 2 * getNode(c)->cnt;
        return nd;
    }
    int mid = (l + r) >> 1;
    if(t <= mid) {
        return getSum(s, t, l, mid, getlson(a), getlson(b), getlson(c) );
    }else if(s >= mid + 1) {
        return getSum(s, t, mid+1, r, getrson(a), getrson(b), getrson(c) );
    }else {
        treeNode ndl, ndr;
        ndl = getSum(s, mid, l, mid, getlson(a), getlson(b), getlson(c) );
        ndr = getSum(mid+1, t, mid+1, r, getrson(a), getrson(b), getrson(c) );
        return treeNode(ndl.sum + ndr.sum, ndl.cnt + ndr.cnt);
    }
    
}

int n, m;


 
__int64 getMaxFlow(int totalBudget, int s, int t, int lca) {
    int l = 1, r = L;
    int ans = 0, sum = 0, cnt = 0;
    
    while(l <= r) {
        int mid = (l + r) >> 1;
        treeNode ret = getSum(1, mid, 1, L, T[s], T[t], T[lca]);

        if ( totalBudget >= ret.cnt * mid - ret.sum ) {
            ans = mid;
            sum = ret.sum;
            cnt = ret.cnt;
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    __int64 re;
    if(ans == L) {
        // 流过来 
        totalBudget -= (cnt * L - sum);
        // 多出来的流量再进行一次分配，每条边都分配到 
        re = (__int64)(totalBudget / cnt) + (L-1);
    }else {
        re = ans - 1;
    }
    return re; 
} 

int main() {
    int tt, cases = 0;
    int i, j;
    scanf("%d", &tt);
    while(tt--) {
        scanf("%d %d", &n, &m);
        LCA_init();
        init();
        L = getIdx(9999);
        
        for(i = 0; i < n-1; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            //u = i+1; v = i+2; c = 9999;
            addEdge( u, v, c );
            addEdge( v, u, c );
        }
        
        // 令1号结点为根，对根结点构造线段树，线段树根结点为T[1] 
        // 每个结点都是一棵线段树，保存的是当前结点到根结点的路径上的 cap的出现次数 以及 路径总和 
        build_cmtree(T[1], 1, L);
        
        RMQ_N = 0;
        LCA_NonDfs(1);
        //LCA_Dfs(-1, 1, 0);
        LCA_To_RMQ();
        //dfs(-1, 1);           
        calc_cmtree(1);       // 自上而下构造主席树

        printf("Case #%d:\n", ++cases);
        while(m--) {
            int s, t, K, A, B;
            scanf("%d %d %d %d %d", &s, &t, &K, &A, &B);
            
            int has = K / minv(A, B);
            int l = 1, r = L;
            int lca = LCA_Query(s, t);
            int ans = 0, sum = 0, cnt = 0;
            
            // 方法一：不建立新的边，在原来的图上进行灌溉，以最大的方式进行灌溉 
            __int64 ret = getMaxFlow(has, s, t, lca);
            
            // 方法二：在A-B之间连一条边，容量为1，花费A，将剩余的 K - A进行从那条边流过来，加上从原图流过来 的流量 
            if( K >= A ) {
                __int64 cap = 1 + (K-A) / minv(A, B);
                __int64 rem =  getMaxFlow( 0, s, t, lca);
                //printf("%I64d %I64d\n", cap, rem);
                if (rem + cap > ret) ret = rem + cap; 
            }
            printf("%I64d\n", ret);
        }
        
    }
    return 0;
}

/*
10
7 8
1 5 2
1 2 3
2 3 4
3 4 1
3 7 5
2 6 6
1 7 100 6 6
1 7 100 101 6
1 7 100 6 2
1 7 2147483646 2147483647 1
1 2 2147483646 2147483647 1
3 2 2147483646 2147483647 1
2 3 2147483646 2147483647 1



10 10
1 2 3
1 4 8
4 3 9
4 5 8
4 7 9
6 2 5
5 8 7
5 9 0
5 10 10
1 5 1 1 10
1 5 10 1 10

ans = 16 9 48 715827886 2147483649 2147483650
*/
