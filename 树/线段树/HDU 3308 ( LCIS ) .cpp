/*
题意：
    给出一个长度为N(N <= 100000)的数列，然后是两种操作：
U A B: 将第A个数替换为B (下标从零开始)
Q A B: 输出区间[A, B]的最长连续递增子序列
注意：操作的数目m <= 100000。

解法：
线段树

思路：
    做惯了区间最值、求和、修改、染色的等问题，这题算比较新颖
的了，由这题可以看出线段树的一般解法，因为这题要求保存的信息
比较多，每个线段树的结点要求保存的信息有以下几个：

    int lMax;       // 包含结点左端点的最长连续递增子序列的长度
    int rMax;       // 包含结点右端点的最长连续递增子序列的长度
    int Max;        // 当前结点的最长连续递增子序列的长度
    int lVal, rVal; // 当前结点管辖的区间左右端点的数值
    int l, r;       // 当前结点管辖的区间

我们用以下函数从左右儿子中得到当前结点的信息：
void UpdateBy(Tree* ls, Tree* rs);
之所以把它写成函数是因为这里的处理比较麻烦，很容易出错，并且需要
调用多次，这个函数的作用就是通过左右儿子的信息填充本身的信息。

lVal、rVal、l、r等信息比较容易求得。
lMax和rMax的值就比较麻烦了，需要分情况讨论（下面的len表示区间长度）：
1. 左儿子最右边的值 < 右儿子最左边的值

    lMax = (左儿子的lMax == 左儿子的len) ? 左儿子的len + 右儿子的lMax : 左儿子的lMax;
    rMax = (右儿子的rMax == 右儿子的len) ? 右儿子的len + 左儿子的rMax : 右儿子的rMax;
    Max  = MAX(左儿子的rMax + 右儿子的lMax, 左儿子的Max, 右儿子的Max, lMax, rMax);

2. 左儿子最右边的值 >= 右儿子最左边的值

    lMax = 左儿子的lMax;
    rMax = 右儿子的rMax;
    Max  = MAX(左儿子的Max, 右儿子的Max);

一开始读入的时候有一连串数字，需要建树，建树的时候每次回归时需要
将儿子的信息传递给父亲，调用UpdateBy(Tree* ls, Tree* rs)函数，每
次插入完毕后回归时，信息会更新，也需要调用。询问时，返回的也是一
个线段树结点，并且需要将答案合并，还是需要调用UpdateBy函数，所以
总的来说需要调用三次，把它写成一个函数还是势在必行的。
*/


#include <iostream>

using namespace std;

#define maxn 100010

struct Tree {
    int lMax;       // 包含结点左端点的最长连续递增子序列
    int rMax;       // 包含结点右端点的最长连续递增子序列
    int Max;        // 当前结点的最长连续递增子序列
    int lVal, rVal; // 当前区间左右端点的值
    int l, r;       // 当前结点管辖的区间
    int son[2];

    void clear() {
        son[0] = son[1] = -1;
    }
    void UpdateBy(Tree* ls, Tree* rs);
    void Unit(int nl, int nr, int nv);
    int len() {
        return r - l + 1;
    }
}T[maxn*4];
int root, tot;
int val[ maxn ];

int MAX(int a, int b) {
    return a > b ? a : b;
}

int MAX(int a, int b, int c) {
    return MAX(MAX(a, b), c);
}

int MAX(int a, int b, int c, int d) {
    return MAX( MAX(a, b), MAX(c, d) );
}

void Tree::UpdateBy(Tree* ls, Tree* rs) {
    lVal = ls->lVal;
    rVal = rs->rVal;
    l    = ls->l;
    r    = rs->r;
    if(ls->rVal < rs->lVal) {
        lMax = (ls->lMax == ls->len()) ? ls->len() + rs->lMax : ls->lMax;
        rMax = (rs->rMax == rs->len()) ? rs->len() + ls->rMax : rs->rMax;
        
        Max  = MAX(ls->rMax + rs->lMax, ls->Max, rs->Max);
        Max  = MAX(Max, lMax, rMax);

    }else {
        lMax = ls->lMax;
        rMax = rs->rMax;
        Max  = MAX(ls->Max, rs->Max);
    }
}

void Tree::Unit(int nl, int nr, int nv) {
    lMax = rMax = 1; Max = 1;
    lVal = rVal = nv;
    l = nl; r = nr;
}

int GetID(int& root) {
    if(root == -1) {
        root = tot++;
        T[root].clear();
    }
    return root;
}

void Build(int& root, int l, int r) {
    GetID(root);
    if(l == r) {
        T[root].Unit(l, r, val[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    Build(T[root].son[0], l, mid);
    Build(T[root].son[1], mid+1, r);

    T[root].UpdateBy(&T[ T[root].son[0] ], &T[ T[root].son[1] ]);
}

void Insert(int root, int nPos, int val) {
    if(nPos < T[root].l || nPos > T[root].r)
        return ;
    if(T[root].l == nPos && nPos == T[root].r) {
        T[root].Unit(nPos, nPos, val);
        return ;
    }
    Insert(T[root].son[0], nPos, val);
    Insert(T[root].son[1], nPos, val);

    T[root].UpdateBy(&T[ T[root].son[0] ], &T[ T[root].son[1] ]);
}

Tree Query(int root, int nl, int nr) {
    if(nl > T[root].r || nr < T[root].l) {
        Tree tmp;
        tmp.Max = -1;
        return tmp;
    }

    if(nl <= T[root].l && T[root].r <= nr) {
        return T[root];
    }
    Tree A, B;
    A = Query(T[root].son[0], nl, nr);
    B = Query(T[root].son[1], nl, nr);
    if(A.Max == -1)
        return B;
    else if(B.Max == -1)
        return A;
    else {
        Tree X;
        X.UpdateBy(&A, &B);
        return X;
    }
}

int n, m;
int main() {
    int t, i;
    scanf("%d", &t);

    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        tot = 0;
        root = -1;
        Build(root, 1, n);
        while(m--) {
            char str[10];
            int A, B;
            scanf("%s %d %d", str, &A, &B);
            if(!strcmp(str, "U")) {
                Insert(root, A+1, B);
            }else {
                Tree tmp = Query(root, A+1, B+1);
                printf("%d\n", tmp.Max);
            }
        }
    }
    return 0;
}
