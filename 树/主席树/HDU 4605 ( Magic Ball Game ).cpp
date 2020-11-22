#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXQ 100010
#define MAXN (100010 + MAXQ)*2
#define LOGMAXN 19
#define MAXNODE (MAXN*2 + 100010*LOGMAXN)

// MAXNODE 表示总结点数，由以下几部分组成
//         1、MAXN*2           第一棵空树的结点数
//         2、MAXN*LOGMAXN     后N棵树，每棵树新加入 LOGMAXN 个结点

struct treeNode {
    int data;                // 分子up、分母down 
    int lson, rson;          // 左右儿子编号       
    // int l, r;             // 左右区间在递归的时候可以计算出来，这里为了节省空间不予保存 
    
    treeNode() {
        reset();
    }
    
    void reset() {
        data = 0;
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
    newroot->data = oldroot->data + cnt;
 
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
        }else {
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
        newroot->data = oldroot->data + cnt;
    }

    return ret;
} 

int lowbit(int x) {
    return x & (-x);
}

void modify(int x, int n, int val, int cnt) {
    while(x <= n) {
        C[x] = insert_cmtree(C[x], val, cnt);
        x += lowbit(x);
    }
}

int CC[MAXN];
int CCHash[MAXN], CCHashV = 1;   // 记录C数组的游标结点 

void updateCC(int x, int upType) {
    while( x > 0 ) {
        
        if (CCHash[x] != CCHashV) {
            CCHash[x] = CCHashV;
        }else {
            break;
        }
        
        if (upType == 0) {
            CC[x] = C[x];
        }else if (upType == 1) {
            CC[x] = getNode(CC[x])->lson; 
        }else if(upType == 2) {
            CC[x] = getNode(CC[x])->rson; 
        }
        
        x -= lowbit(x);
    }    
}

int getLeftSonSum(int x) {
    int s = 0;
    while(x > 0) {
        s += getNode( getNode(CC[x])->lson )->data;
        x -= lowbit(x);
    }
    return s;
}


int query_cmtree(int lt, int rt, int lnode, int rnode, int l, int r, int k) {

    int mid = (l + r) >> 1;
    if(l == r) {
        return mid;
    }
    treeNode *ln = getNode(lnode), *rn = getNode(rnode);
    
    int modifyCnt = getLeftSonSum( rt ) - getLeftSonSum( lt );
    int nowCnt = ( getNode(rn->lson)->data - getNode(ln->lson)->data );
    int totalCnt =  modifyCnt + nowCnt;
                                                
    if(k > totalCnt) {
        updateCC(lt, 2), updateCC(rt, 2);
        CCHashV ++;
        return query_cmtree(lt, rt, ln->rson, rn->rson, mid+1, r, k - totalCnt);
    }else {
        updateCC(lt, 1), updateCC(rt, 1);
        CCHashV ++;
        return query_cmtree(lt, rt, ln->lson, rn->lson, l, mid, k);
    }
}

// C[lt] 和 T[lt]     相加表示的是前缀 [1:lt] 修改完的线段树，其中 C[lt] 表示线段树的修改量 
// C[rt] 和 T[rt]     相加表示的是前缀 [1:rt] 修改完的线段树，其中 C[rt] 表示线段树的修改量
int query(int lt, int rt, int k) {
    updateCC(lt, 0), updateCC(rt, 0);
    CCHashV ++;
    return query_cmtree(lt, rt, T[lt], T[rt], 1, L, k);
}

//前方高能，模板区 ####################################################################################### 
//########################################################################################################

int N, M, Q;
int a[MAXN], b[MAXN], bs;
int ls[MAXN], rs[MAXN], fat[MAXN];
int root;

int Qv[MAXQ], Qx[MAXQ];

int getRoot() {
    for(int i = 1; i <= N; i++) {
        if(fat[i] == -1) return i;
    }
}

int getIdx(int v) {
    int l = 1, r = L/2;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(v == b[mid]) return mid;
        else if(v < b[mid]) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}

void dfs(int u) {
    
    
    if(ls[u] != -1) {
        T[ ls[u] ] = insert_cmtree(T[u], getIdx(a[u]), 1);
        dfs(ls[u]);
    }
    
    if(rs[u] != -1) {
        T[ rs[u] ] = insert_cmtree(T[u], getIdx(a[u]) + L/2, 1);
        dfs(rs[u]);
    }
    
}

int getNumberCount(int root, int s, int t, int l, int r) {
    if(s > t) {
        return 0;
    }
    if(s == l && t == r) {
        return getNode(root)->data;
    }
    int mid = (l + r) >> 1;
    if(t <= mid) {
        return getNumberCount( getNode(root)->lson, s, t, l, mid );
    }else if(s >= mid + 1) {
        return getNumberCount( getNode(root)->rson, s, t, mid+1, r );
    }else {
        return getNumberCount( getNode(root)->lson, s, mid, l, mid ) + getNumberCount( getNode(root)->rson, mid+1, t, mid+1, r );
    }
} 

int main() {
    int t;
    int i;
    scanf("%d", &t);
    
    while(t--) {
        init();
        scanf("%d", &N);
        
        for(i = 1; i <= N; i++) {
            fat[i] = ls[i] = rs[i] = -1;
        }
        
        bs = 0;
        for(i = 1; i <= N; i++) {
            scanf("%d", &a[i]);
            b[++bs] = a[i];
        }
        scanf("%d", &M);
        for(i = 0; i < M; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            ls[x] = y;
            rs[x] = z;
            fat[y] = fat[z] = x;
        }
        scanf("%d", &Q);
        for(i = 0; i < Q; i++) {
            scanf("%d %d", &Qv[i], &Qx[i]);
            b[++bs] = Qx[i];
        }
        
        sort(&b[1], &b[1] + bs);
        
        for(i = 2; i <= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        
        /*for(i = 1; i <= L; i++) {
            printf("%d ", b[i]);
        }*/
        L *= 2;
        
        root = getRoot();
        build_cmtree(T[0], 1, L);
        T[root] = T[0];
        dfs(root);
        
        for(i = 0; i < Q; i++) {
            int segRoot = T[ Qv[i] ];
            int x = getIdx( Qx[i] );
            int valCount = getNumberCount(segRoot, x, x, 1, L) + getNumberCount(segRoot, x+L/2, x+L/2, 1, L);
            if( valCount ) {
                printf("0\n");
            }else {
                // 从左子树下来，值小于X的，概率乘上 1/8
                int x1 = getNumberCount(segRoot, 1, x-1, 1, L);
                // 从右子树下来，值小于X的，概率乘上7/8
                int x2 = getNumberCount(segRoot, 1+L/2, x-1+L/2, 1, L);
                
                // 从左子树下来，值大于x的，概率乘上1/2
                int x3 = getNumberCount(segRoot, x+1, L/2, 1, L); 
                // 从右子树下来，值大于x的，概率乘上1/2
                int x4 = getNumberCount(segRoot, x+1+L/2, L, 1, L);
                
                int up   = x1*0 + x2*1 + x3*0 + x4*0;
                int down = x1*3 + x2*3 + x3*1 + x4*1;
                printf("%d %d\n", up, down);
            }
        }
    }
    return 0;
} 

/*
1

7
6 5 4 3 9 6 1
3
2 1 4
4 3 5
5 7 6
10
7 1
7 2
7 3
7 4
7 5
7 6
7 7
7 8
7 9
7 10

1
1
100
0
3
1 1
1 101
1 1000000000

*/
