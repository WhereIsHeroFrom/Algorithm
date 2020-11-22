#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1025
#define ROOT_INTERVAL Interval(1, L)
#define ROOT_ID 1
#define son(x) (p*4-2+x)

struct Interval {
    int l, r;
    Interval() {}
    Interval(int _l, int _r) {
        l = _l;
        r = _r;
    }    
    
    // 区间中点 
    int mid() {
        return (l + r) >> 1;
    }
    // 区间长度 
    int len() {
        return r - l + 1;
    }
    // 左半区间 
    Interval left() {
        return Interval(l, mid());
    }
    // 右半区间 
    Interval right() {
        return Interval(mid()+1, r);
    }
    // 是否区间相交
    bool isIntersectWith( Interval& tarI ) {
        return !( l > tarI.r || r < tarI.l );
    } 
    // 是否包含
    bool isInclude( Interval& tarI ) {
        return l <= tarI.l && tarI.r <= r;
    }
    bool in (int v) {
        return l <= v && v <= r;
    }
};

// 最值信息 
struct dataInfo {
    short posx, posy;
    int val;
    dataInfo() {
        posx = posy = -1;
        val = -1;
    }
    dataInfo(short _posx, short _posy, int _val) {
        posx = _posx;
        posy = _posy;
        val = _val;
    }
};

struct treeNode {
    //  四个儿子分布如下： 
    // son[4] = {A, B, C, D} 
    //  A B
    //  C D
    // int son[4];   
    //为了节省内存，儿子信息不予保存，父结点编号为p，则四个儿子分别为 4*p-2, 4*p-1, 4*p, 4*p+1 
    dataInfo maxv, minv;
    
    void reset() {
        maxv = dataInfo(0, 0, INT_MIN);
        minv = dataInfo(0, 0, INT_MAX);
    }
}nodes[ ((1<<22)-1) / 3 + 100 ];

// 区间1X1, 结点数 = 1
// 区间2X2，结点数 = 5 = 1 + 4
// 区间4X4，结点数 = 21 = 1 + 4 + 16
// ...
// 区间2^n X 2^n，结点数 = 1 + 4 + 16 + ... + 4^n = (4^(n+1)-1) / 3
 
int L;

void init() {
    L = 1;
}

treeNode* getNode(int id) {
    return &nodes[id];
}
 
void build_segtree(int p, Interval xI, Interval yI) {
    
    if(xI.len() <= 0 || yI.len() <= 0) {
        return ;
    }
    //printf("%d %d %d %d %d\n", p, xI.l, xI.r, yI.l, yI.r);
    treeNode* now = getNode(p);
    now->reset();
    if(xI.len() == 1 && yI.len() == 1) {
        return ;
    }
    build_segtree( son(0), xI.left(), yI.left() );
    build_segtree( son(1), xI.right(), yI.left());
    build_segtree( son(2), xI.left(), yI.right() );
    build_segtree( son(3), xI.right(), yI.right());    
}

// 返回结点是否合法 
bool insert_segtree(int p, Interval xI, Interval yI, int x, int y, int val) {
    if(xI.len() <= 0 || yI.len() <= 0) {
        return false;
    }
    if( !xI.in(x) || !yI.in(y) ) {
        return true;
    }
    treeNode *now = getNode(p);
    if(xI.len() == 1 && yI.len() == 1) {
        now->maxv = now->minv = dataInfo(x, y, val);
        return true;
    }
    bool isvalid[4];
    isvalid[0] = insert_segtree( son(0), xI.left(), yI.left(), x, y, val );
    isvalid[1] = insert_segtree( son(1), xI.right(), yI.left(), x, y, val );
    isvalid[2] = insert_segtree( son(2), xI.left(), yI.right(), x, y, val );
    isvalid[3] = insert_segtree( son(3), xI.right(), yI.right(), x, y, val ); 
    
    now->maxv = dataInfo(0, 0, INT_MIN);
    now->minv = dataInfo(0, 0, INT_MAX);
    int i;
    for(i = 0;i < 4; i++) {
        if( !isvalid[i] ) continue;
        treeNode *sonNode = getNode(son(i));
        now->maxv = sonNode->maxv.val > now->maxv.val ? sonNode->maxv : now->maxv;
        now->minv = sonNode->minv.val < now->minv.val ? sonNode->minv : now->minv;
    }
    return true; 
}

// 询问tarI区间内的最值信息 
// query_type 0 最大值   1最小值 
void query_segtree(int p, Interval xI, Interval yI, Interval tarXI, Interval tarYI, dataInfo& ans, int query_type) {
    if(xI.len() <= 0 || yI.len() <= 0) {
        return ;
    }
    
    if( !tarXI.isIntersectWith(xI) || !tarYI.isIntersectWith(yI) ) {
        return ;
    }
    treeNode *now = getNode(p);
    
    // 最大值 优化 
    if(query_type == 0 && ans.val >= now->maxv.val) {
        return ;
    }
    // 最小值 优化 
    if(query_type == 1 && ans.val <= now->minv.val) {
        return ;
    }
        
    if(tarXI.isInclude(xI) && tarYI.isInclude(yI)) {
        if(query_type == 0) {
            ans = now->maxv;
        }else {
            ans = now->minv;
        }
        return ;
    }
    query_segtree( son(0), xI.left(), yI.left(), tarXI, tarYI, ans, query_type );
    query_segtree( son(1), xI.right(), yI.left(), tarXI, tarYI, ans, query_type );
    query_segtree( son(2), xI.left(), yI.right(), tarXI, tarYI, ans, query_type );
    query_segtree( son(3), xI.right(), yI.right(), tarXI, tarYI, ans, query_type ); 
}

int n, m;

int maxv(int a, int b) {
    return a > b ? a : b;
}
int minv(int a, int b) {
    return a < b ? a : b;
} 

int main() {
    int t, cases = 0;
    int i, j;
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        init();
        L = n;
        build_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL);
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                int v;
                scanf("%d", &v);
                insert_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL, i, j, v);
            }
        }
        printf("Case #%d:\n", ++cases);
        scanf("%d", &m);
        while(m--) {
            int x, y, l;
            scanf("%d %d %d", &x, &y, &l);
            Interval X( maxv(x-l/2, 1), minv(x+l/2, n) );
            Interval Y( maxv(y-l/2, 1), minv(y+l/2, n) );

            dataInfo maxinfo(0, 0, INT_MIN), mininfo(0, 0, INT_MAX);
            query_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL, X, Y, maxinfo, 0);
            query_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL, X, Y, mininfo, 1);
            int vv = (maxinfo.val + mininfo.val) / 2;
            printf("%d\n", vv);
            insert_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL, x, y, vv);
            
            /*printf(" ******************\n");
            for(i = 1; i <= n; i++) {
                for(j = 1; j <= n; j++) {
                    dataInfo maxin(0, 0, INT_MIN);
                    query_segtree(ROOT_ID, ROOT_INTERVAL, ROOT_INTERVAL, Interval(i,i), Interval(j,j), maxin, 0);
                    printf("%d ", maxin.val);
                }
                puts("");
            }            */
            
        }
    }
    return 0;

}
/*
2
3
1 2 3
4 5 6
7 8 9
5
2 2 1
3 2 3
1 1 3
1 2 3
2 2 3

5
11 12 13 15 65
89 56 43 90 23
94 34 23 11 32
98 45 33 22 11
90 89 12 32 11
30
2 3 3

*/
