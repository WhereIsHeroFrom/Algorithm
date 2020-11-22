#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 140010

struct treeNode {
    __int64 sum[5];       // 当前结点中下标模5为i的数的和为 sum[ (i + placement) % 5 ];
    char placement;
    void reset() {
        placement = 0;
        for(int i = 0; i < 5; i++) {
            sum[i] = 0;
        }
    }
    
    inline int getIndex(int kth) {
        int idx = kth + placement;
        if(idx >= 5) idx -= 5;
        return idx;
    }

    void addValue(int kth, int val) {
        sum[ getIndex(kth) ] += val;
    }
    
    __int64 getValue(int kth) {
        return sum[ getIndex(kth) ];
    }
    
    void updatePlacement(int upd) {
        placement += upd;
        if (placement >= 5) placement -= 5;
    }
    
    void tagGiveToSon(treeNode *lson, treeNode *rson) {
        if(placement) {
            lson->updatePlacement(placement);
            rson->updatePlacement(placement);
            placement = 0;
        }
    }
    
}nodes[2*MAXN];

int L;

treeNode* getNode(int id) {
    return &nodes[id];
}

void build_segtree(int p, int l, int r) {
    getNode(p)->reset();
    
    int mid = (l + r) >> 1;
    if(l < r) {
        build_segtree(p<<1, l, mid);
        build_segtree(p<<1|1, mid+1, r);
    }
}

// insert_type 
// 0 插入   1 删除 
void insert_segtree(int p, int l, int r, int kth, int idx, int v, int insert_type) {
    
    treeNode *now = getNode(p);
    if(l == r) {
        now->addValue(kth%5, v);
        return ;
    }
    
    int mid = (l + r) >> 1;
    treeNode *left = getNode(p<<1);
    treeNode *right = getNode(p<<1|1);
    now->tagGiveToSon(left, right);
    
    if(idx <= mid) {    
        right->updatePlacement( insert_type == 0 ? 4 : 1 );   // 4 == -1 在 mod 5 的情况下 
        insert_segtree(p<<1, l, mid, kth, idx, v, insert_type);
    }else {
        insert_segtree(p<<1|1, mid+1, r, kth, idx, v, insert_type);
    }
    
    for(int i = 0; i < 5; i++) {
        now->sum[i] = left->getValue(i) + right->getValue(i);
    }
}


struct queryInfo {
    int tp, idx, value;
    queryInfo() {
    }
    queryInfo(int _tp, int _idx, int _value) {
        tp = _tp;
        idx = _idx;
        value = _value;
    }
}Q[MAXN];


int c[MAXN];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int val) {
    while(x <= L) {
        c[x] += val;
        x += lowbit(x);
    }
}

int sum(int x) {
    int s = 0;
    while(x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}

int n;
int b[MAXN], bs;

int getIdx(int v) {
    int l = 1, r = L;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(v == b[mid]) return mid;
        if(v < b[mid]) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}

int main() {
    int i;
    while( scanf("%d", &n) != EOF ) {
        L = 1;
        bs = 0;
        
        for(i = 1; i <= n; i++) {
            char str[10];
            int val;
            scanf("%s", str);
            
            if(str[0] == 'a') {
                scanf("%d", &val);
                Q[i] = queryInfo(0, -1, val);
            }else if (str[0] == 'd') {
                scanf("%d", &val);
                Q[i] = queryInfo(1, -1, val);
            }else {
                Q[i] = queryInfo(2, -1, -1);
            }
            b[ ++bs ] = val;
        }
        sort(&b[1], &b[1] + bs);
        for(i = 2; i <= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        
        for(i = 1; i <= n; i++) {
            if(Q[i].tp == 2) continue;
            Q[i].idx = getIdx(Q[i].value);
        }
        
        for(i = 1; i <= L; i++) c[i] = 0;
        build_segtree(1, 1, L);

        for(i = 1; i <= n; i++) {
            int index = Q[i].idx;
            if(Q[i].tp == 0) {                
                add(index, 1);
                insert_segtree(1, 1, L, sum(index), index, Q[i].value, 0);
            }else if(Q[i].tp == 1) {
                insert_segtree(1, 1, L, sum(index), index, -Q[i].value, 1);
                add(index, -1);
            }else if(Q[i].tp == 2) {
                printf("%I64d\n", getNode(1)->sum[3]);
            }
        }        
        
    }
    return 0;
}

/*
9
add 1
add 2
add 3
add 4
add 5
sum
add 6
del 3
sum

16
add 7
add 90
add 12
add 8
add 3
add 5
add 101
add -5
del 7
del 101
add 901
del 90
add 1111
add 1222
add 78
sum

*/
