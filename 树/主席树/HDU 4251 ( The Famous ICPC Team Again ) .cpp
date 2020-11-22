#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXN 100010
#define MAXQ 100010
#define LOGMAXN 17
#define MAXNODE 1990000

// MAXNODE 表示总结点数，由以下几部分组成
//         1、MAXN*2           第一棵空树的结点数
//         2、MAXN*LOGMAXN     后N棵树，每棵树新加入 LOGMAXN 个结点

struct treeNode {
    int data;                // 数据域 
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
    getNode(x)->reset();     // 对于多case，这里必须重置
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

//前方高能，模板区 ####################################################################################### 
//########################################################################################################

int a[MAXN], b[MAXN], bs;
int n, m;

int getIdx(int val) {
    int l = 1, r = L;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(val == b[mid]) return mid;
        
        if(val > b[mid]) {
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
}

void build() {
    int i;
    // 创建空树 
    build_cmtree(T[0], 1, L);
    for(i = 0; i < n; i++) {
        T[i+1] = insert_cmtree(T[i], getIdx(a[i]), 1);
    }    
}

int query(int s, int t, int l, int r, int k) {
    if(l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    int cnt = getNode(getNode(t)->lson)->data - getNode(getNode(s)->lson)->data;
    if(k > cnt) {
        return query(getNode(s)->rson, getNode(t)->rson, mid+1, r, k-cnt);
    }else {
        return query(getNode(s)->lson, getNode(t)->lson, l, mid, k);
    }
}

int main() {
    //printf("%d\n", sizeof( treeNode ) );
    int i;
    int t, cases = 0;
    while( scanf("%d", &n) != EOF ) {
        //n = 100000;
        init();
        bs = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            //a[i] = i;
            b[++bs]    = a[i];
        }
        sort(&b[1], &b[1] + bs);
        for(i = 2; i <= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        build(); //printf("%d\n", totalNodes);
        printf("Case %d:\n", ++cases);
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            int idx = query(T[A-1], T[B], 1, L, (B-A)/2+1 );
            printf("%d\n", b[idx]);
        }

    }
    return 0;
}
