/*
题意：
    给出一个长度为N(N <= 100000)的数列，然后是五种操作：
插入操作:
0 a b 将所有[a, b]区间内的数改成0
1 a b 将所有[a, b]区间内的数改成1
2 a b 将所有[a, b]区间内的数异或一下（0边1,1变0）
输出操作:
3 a b 输出[a, b]区间内1的数量
4 a b 输出[a, b]区间内最长的连续1串


解法：
线段树

思路：
    这题看起来是一般的区间覆盖问题，还是有一点小trick让我卡了很久，先
来看看线段树的结点要求保存的信息：

    enum eLazyTag {
        ZERO     = 0,
        ONE      = 1,
        XOR      = 2,
        TAG_MAX  = 3
    }; // lazy标记的枚举类型

    char lazy[TAG_MAX];      // 对应的lazy标记
    int root, l, r;          // 当前结点管理的左右区间以及编号
    int lMax[2];             // 包含当前结点管理区间左端点的最长连续相同数字串
    int rMax[2];             // 包含当前结点管理区间右端点的最长连续相同数字串
    int Max[2];              // 当前结点管理区间的最长连续相同数字串
    int Sum;                 // 记录当前区间的和，也就是1的数量

这题的异或操作是亮点，因为它不是单纯的覆盖，而是和先前的线段状态取反，这个操作
和直接覆盖不一样，需要知道以前这块线段的信息，所以如果之前这个线段的lazy标记是
ZERO，传入的变量要求做XOR，那么不能仅仅将XOR赋值给lazy，这样当前结点的左右子树
就不能享受到ZERO带来的“福利”。所以我们保存三个lazy标记（其实只需要两个就够了
，因为0和1的情况是一样，都是普通的覆盖，不涉及到先前值），每次传递标记的时候需
要三个标记都传递下去。

我们用以下函数从左右儿子中得到当前结点的信息：
void UpdateBy(Tree* ls, Tree* rs);
之所以把它写成函数是因为这里的处理比较麻烦，很容易出错，并且需要
调用多次，这个函数的作用就是通过左右儿子的信息填充本身的信息。

这里沿用LCIS那题的思想，保存lMax，rMax，但是需要注意这里有一种异或操作，所以
光保存连续1串的最大长度是不够的，异或之后1就变成了0，于是保存两种值，0和1的分
别最大长度，这样如果有XOR操作，直接将lMax[0]和lMax[1]交换即可，其它两个值亦然。


讲一下我的代码的结构吧。首先是建树，通过Build函数建立完全二叉树，进入函数时将
一些必要的值初始化，当遇到叶子结点时处理那个结点的信息，如果不是叶子结点，则递
归建立二个儿子的信息，然后通过儿子的信息，将父亲结点的所有值算出来，这个计算过
程是通过void UpdateBy(Tree* ls, Tree* rs)来完成的，ls和rs分别表示当前结点的两个
儿子的结点指针，UpdateBy计算的信息包括区间和Sum，区间最长连续0串和1串。对操作分
情况讨论：

插入操作：
    如果当前区间已经完全包含了结点区间，则调用CoverBy函数将插入标记传给当前
结点的lazy，具体的CoverBy函数的实现需要分情况讨论：
    当传入的插入类型mode为ZERO或者ONE则表明是直接覆盖，那么当前lazy[mode]标
记赋值为1，以便下次传递给子孙，而lazy[1-mode]和lazy[XOR]直接置零即可。因为只需
直接覆盖，先前的标记就不起作用了。
    当插入的类型为XOR时，并且之前有ONE或者ZERO标记，说明当前区间肯定全是相同
的数，因为lazy标记存在，说明还没有传递给子孙，则将lazy[ONE]和lazy[ZERO]的值交换
即可（因为当前插入类型为XOR）。如果之前没有标记或者只有XOR标记，直接将lazy[XOR]
和1异或即可。

插入完毕然后更新当前区间的结点值。如果当前区间没有完全包含结点区间，则先将当前
结点的lazy标记传递给左右儿子，然后分别递归左右儿子进行插入操作，插入完毕后，通
过左右儿子得到的结点值利用void UpdateBy(Tree* ls, Tree* rs)更新父亲结点。

询问操作：
完全覆盖时直接返回当前结点，否则需要递归左右儿子将两个结点合并。

*/



#include <iostream>

using namespace std;

enum eLazyTag {
    ZERO     = 0,
    ONE      = 1,
    XOR      = 2,
    TAG_MAX  = 3
};
#define maxn 100010

int MMax(int a, int b) {
    return a > b ? a : b;
}
int MMax(int a, int b, int c, int d) {
    return MMax( MMax(a, b), MMax(c, d) );
}
struct Tree {
    char lazy[TAG_MAX];  // 对应的lazy标记是否存在以及它的奇偶性
    int root, l, r;      // 当前结点管理的左右区间以及编号
    int lMax[2];         // 包含当前结点管理区间左端点的最长连续相同数字串
    int rMax[2];         // 包含当前结点管理区间右端点的最长连续相同数字串
    int Max[2];          // 当前结点管理区间的最长连续相同数字串
    int Sum;             // 记录当前区间的和，也就是1的数量

    void ProcessUnit(int val);
    void UpdateBy(Tree* ls, Tree* rs);
    void CoverBy(int mode);
    void TranslateToSon();
    void TranslateTo(Tree* ts);
    int len() {
        return r - l + 1;
    }
}T[maxn*4];

int val[maxn];
void Tree::ProcessUnit(int val) {
    lMax[val] = rMax[val] = Max[val] = len();
    lMax[val^1] = rMax[val^1] = Max[val^1] = 0;
    Sum = val * len();
}

void Tree::UpdateBy(Tree* ls, Tree* rs) {
    Sum  = ls->Sum + rs->Sum;
    l    = ls->l;
    r    = rs->r;

    int i;
    for(i = 0; i < 2; i++) {
        lMax[i] = (ls->lMax[i]==ls->len()) ? ls->len() + rs->lMax[i] : ls->lMax[i];
        rMax[i] = (rs->rMax[i]==rs->len()) ? rs->len() + ls->rMax[i] : rs->rMax[i];

        Max[i]  = MMax(ls->Max[i], rs->Max[i]);
        Max[i]  = MMax(Max[i], lMax[i], rMax[i], ls->rMax[i]+rs->lMax[i]);
    }
}
void Tree::CoverBy(int mode) {

    if(mode == ZERO    || mode == ONE) {
        ProcessUnit(mode);
        lazy[mode] = 1;
        lazy[mode^1] = 0;
        lazy[XOR] = 0;
    }else if(mode == XOR){
        swap(lMax[0], lMax[1]);
        swap(rMax[0], rMax[1]);
        swap( Max[0],  Max[1]);
        Sum = len() - Sum;
        if(lazy[ZERO]) {
            lazy[ONE] = 1;
            lazy[ZERO] = 0;
        }else if(lazy[ONE]) {
            lazy[ONE] = 0;
            lazy[ZERO] = 1;
        }else
            lazy[mode] ^= 1;
    }
}
void Tree::TranslateTo(Tree* ts) {
    int i;
    for(i = 0; i < TAG_MAX; i++) {
        if(lazy[i]) {
            ts->CoverBy(i);
        }
    }
}

void Tree::TranslateToSon() {
    TranslateTo(&T[root<<1]);
    TranslateTo(&T[root<<1|1]);
    for(int i = 0; i < TAG_MAX; i++)
        lazy[i] = 0;
}

void Build(int p, int l, int r) {
    int i;
    for(i = 0; i < TAG_MAX; i++)
        T[p].lazy[i] = 0;
    T[p].l = l; T[p].r = r;
    T[p].root = p;
    if(l == r) {
        T[p].ProcessUnit(val[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    Build(p<<1, l, mid);
    Build(p<<1|1, mid+1, r);

    T[p].UpdateBy(&T[p<<1], &T[p<<1|1]);
}

void Insert(int root, int l, int r, int mode) {
    if(l <= T[root].l && T[root].r <= r) {
        T[root].CoverBy(mode);
        return ;
    }
    if(mode != XOR && T[root].lazy[mode]) {
        return ;
    }
    T[root].TranslateToSon();
    int mid = T[root<<1].r;
    if(r <= mid) {
        Insert(root<<1, l, r, mode);
    }else if(mid + 1 <= l) {
        Insert(root<<1|1, l, r, mode);
    }else {
        Insert(root<<1, l, r, mode);
        Insert(root<<1|1, l, r, mode);
    }
    T[root].UpdateBy(&T[root<<1], &T[root<<1|1]);
}

Tree Query(int root, int l, int r) {
    if(l <= T[root].l && T[root].r <= r) {
        return T[root];
    }
    T[root].TranslateToSon();
    int mid = T[root<<1].r;
    
    if(r <= mid) {
        return Query(root<<1, l, r);
    }else if(l >= mid + 1) {
        return Query(root<<1|1, l, r);
    }else {
        Tree A = Query(root<<1, l, r);
        Tree B = Query(root<<1|1, l, r);
        Tree X;
        X.UpdateBy(&A, &B);
        return X;
    }
}

int n, m;
int main() {
    int t;
    int i;
    int p, a, b;

    scanf("%d", &t);

    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        Build(1, 1, n);
        while(m--) {
            scanf("%d %d %d", &p, &a, &b);
            a++; b++;
            if(p <= 2) {
                Insert(1, a, b, p);
            }else {
                Tree X = Query(1, a, b);
                if(p == 3) {
                    printf("%d\n", X.Sum);
                }else
                    printf("%d\n", X.Max[1]);
            }
        }
    }
    return 0;
}

