/*
题意：
    现在有1到N(N <= 50000)个连续内存块，然后给出四种操作：
1.  Reset 释放所有内存块，并且输出“Reset Now”。
2.  New x 找到一块有连续x块内存的空间，并且占据它。如果有多种，选择起始数字
最小的，然后“New at A”，A表示起始数字；否则输出“Reject New”。
3.  Free x 释放一块占据x单元的内存块，并且输出“Free from A to B”，A到B表示
占据的内存块；否则输出“Reject Free”。
4.  Get x 找到第x块连续内存，如果找到，输出“Get at A”，A表示起始的数字单元
，如果当前内存块小于x，则输出“Reject Get”。


解法：
    线段树 + 树状数组
    
思路：
    线段树染色问题，和PKU 3667 Hotel类似，也是寻找最长连续区间。线
段树中可以保存如下信息：

    enum eKind {
        EK_MUTIPLE = -1,      // 多种情况
        EK_EMPTY = 0,         // 当前内存块全空
        EK_FULL = 1,          // 当前内存块全满
        EK_LPOINT = 2,        // 当前内存块的左端点
    };

    int root, l, r;
    eKind cover;       // 当前区间的种类的枚举     
    int lMax;          // 包含左区间的连续空闲区间的最大值
    int rMax;          // 包含右区间的连续空闲区间的最大值
    int mMax;          // 当前结点管辖区间的最大值
    int nCount;        // 当前区间分配好的内存块的数量

    首先来看下问题对应的操作，查询连续D区间这个我在后面会详细介绍
，先来看看插入操作，题目中有两种插入，一个是插入一块满的区间，另一
个是删除一段固定长度的区间，其实原理是一样的，我们只要用一个lazy标
记即可。我的结构中的lazy标记用eKind这个枚举类型来表示。EK_EMPTY表示
清空一段区间，EK_FULL表示填充一段区间。每次插入操作只进行到当前区间
完全覆盖结点区间时。如果完全覆盖，则根据插入的eKind类型填充mMax、
lMax、rMax的信息，否则将当前结点有的lazy标记传递给两个子结点，更新
他们的结点信息，然后递归左右儿子，继续插入操作，递归返回时我们用以
下函数从左右儿子中得到当前结点的信息：
    void UpdateBy(Tree* ls, Tree* rs);
    之所以把它写成函数是因为这里的处理比较麻烦，很容易出错，并且需要
调用多次，这个函数的作用就是通过左右儿子的信息填充本身的信息。
信息一多，处理的时候就要极为小心，因为很容易出错。
lMax表示当前结点的包含左闭区间的最优解。
rMax表示当前结点的包含右闭区间的最优解。
mMax则是当前区间的最优解。
    这样我们就可以通过传递性在儿子结点的属性都得知的情况下将父亲的值
计算出来，最后递归到根结点。具体的计算过程可以自己画棵树看一下。
    然后是查询操作，查询的话首先判断当前结点的最大值是否比给定的查
询值小，如果是这样直接返回0表示没有找到。否则将当前值和左儿子的最大
值进行比较，如果满足给定值小于等于左儿子的最大值则递归计算左儿子，
如果不是，则比较的不是右儿子，因为有可能这个最大空闲区间是在左儿子的
rMax + 右儿子的 lMax 上，因此需要和这个值比较，最后才是和右儿子的值
比较，这里可以保证肯定能找到一个解，需要注意的是在询问的时候需要将当
前结点的lazy标记往下传。
    以上操作可以处理New操作，Free操作可以用树状数组来统计，我们把每次
New一块空间的时候，将连续块的左端点标记为EK_LPOINT，nCount则记为1，这
样通过儿子结点计算父亲的nCount值只需要将左右儿子的nCount域相加即可。
然后Get操作和Free操作是类似的，也需要找到第K块内存块，二分这个K，然后
找到满足条件的最小值即可。
*/


#include <iostream>

using namespace std;

#define maxn 50010
int n;

enum eKind {
    EK_MUTIPLE = -1,      // 多种情况
    EK_EMPTY = 0,         // 当前内存块全空
    EK_FULL = 1,          // 当前内存块全满
    EK_LPOINT = 2,        // 当前内存块的左端点
};

struct Tree {
    int root, l, r;
    int mMax;            // 当前结点下最大空闲块
    int lMax;            // 左连接最大空闲块
    int rMax;            // 右连接最大空闲块
    int nCount;          // 当前结点下占据内存块的次数
    eKind lazy_cover;

    int len() {
        return r - l + 1;
    }

    void CoverBy(eKind eVal);
    void TranslateTo(Tree *ts);
    void TranslateToSon();
    void UpdateBy(Tree* ls, Tree* rs);
}T[maxn*6];

int MMax(int a, int b) {
    return a > b ? a : b;
}

int MMax(int a, int b, int c, int d) {
    return MMax(MMax(a, b), MMax(c, d));
}

void Tree::CoverBy(eKind eVal) {
    lazy_cover = eVal;
    
    if(eVal == EK_EMPTY) {
        nCount = 0;
        mMax = lMax = rMax = len();
    }else if(eVal == EK_FULL) {
        nCount = 0;
        mMax = lMax = rMax = 0;
    }else if(eVal == EK_LPOINT) {
        nCount = 1;
        mMax = lMax = rMax = 0;
    }
}

void Tree::TranslateTo(Tree *ts) {
    ts->CoverBy(lazy_cover);
}

void Tree::TranslateToSon() {
    if(lazy_cover != EK_MUTIPLE) {
        TranslateTo(&T[root<<1]);
        TranslateTo(&T[root<<1|1]);
        lazy_cover = EK_MUTIPLE;
    }
}

void Tree::UpdateBy(Tree* ls, Tree* rs) {
    nCount = ls->nCount + rs->nCount;

    lMax = ls->lMax; if(lMax == ls->len()) lMax += rs->lMax;
    rMax = rs->rMax; if(rMax == rs->len()) rMax += ls->rMax;

    mMax = MMax(lMax, rMax);
    mMax = MMax(mMax, ls->mMax, rs->mMax, ls->rMax + rs->lMax);
}

void Build(int root, int l, int r) {
    T[root].root = root;
    T[root].l = l;
    T[root].r = r;
    T[root].CoverBy(EK_EMPTY);
    if(l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    Build(root<<1, l, mid);
    Build(root<<1|1, mid+1, r);
}

void Insert(int root, int l, int r, eKind val) {
    if(l > T[root].r || r < T[root].l)
        return ;

    if(l <= T[root].l && T[root].r <= r) {
        T[root].CoverBy(val);
        return ;
    }

    T[root].TranslateToSon();

    Insert(root<<1, l, r, val);
    Insert(root<<1|1, l, r, val);

    T[root].UpdateBy(&T[root<<1], &T[root<<1|1]);
}

int QueryNew(int root, int val) {
    if(val > T[root].mMax)
        return 0;

    // 递归结束到元区间位置
    if(T[root].l == T[root].r) {
        if(val == 1) {
            return T[root].l;
        }
        return 0;
    }

    T[root].TranslateToSon();

    if(val <= T[root<<1].mMax) {
        return QueryNew(root<<1, val);
    }else if(val <= T[root<<1].rMax + T[root<<1|1].lMax)
        return T[root<<1].r - T[root<<1].rMax + 1;
    else {
        return QueryNew(root<<1|1, val);
    }
}

bool IsEmpty(int root, int pos) {
    if(pos < T[root].l || pos > T[root].r)
        return false;

    if(pos == T[root].l && T[root].r == pos) {
        return T[root].mMax;
    }

    T[root].TranslateToSon();
    return IsEmpty(root<<1, pos) || IsEmpty(root<<1|1, pos);
}

int Count(int root, int l, int r) {
    if(l > T[root].r || r < T[root].l)
        return 0;
    if(l <= T[root].l && T[root].r <= r)
        return T[root].nCount;

    T[root].TranslateToSon();

    return Count(root<<1, l, r) + Count(root<<1|1, l, r);
}

int FindKCount(int K) {
    int l = 1;
    int r = n;
    int ans = n + 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(Count(1, 1, m) >= K) {
            r = m - 1;
            ans = m;
        }else
            l = m + 1;
    }
    return ans;
}


int m;
int main() {
    int i;
    char str[10];
    while(scanf("%d %d", &n, &m) != EOF) {
        Build(1, 1, n);
        for(i = 0; i < m; i++) {
            scanf("%s", str);
            if(!strcmp(str, "Reset")) {
                Insert(1, 1, n, EK_EMPTY);
                printf("Reset Now\n");
            }else {
                int x;
                scanf("%d", &x);
                if(!strcmp(str, "New")) {
                    int pos = QueryNew(1, x);
                    if(pos) {
                        printf("New at %d\n", pos);
                        Insert(1, pos, pos + x - 1, EK_FULL);
                        Insert(1, pos, pos, EK_LPOINT);
                    }else
                        printf("Reject New\n");
                }else if(!strcmp(str, "Free")) {
                    if(IsEmpty(1, x)) {
                        printf("Reject Free\n");
                    }else {
                        int K = Count(1, 1, x);
                        int l = FindKCount(K);
                        int r = FindKCount(K+1) - 1;
                        int st = l;
                        int ed = r;
                        while(l <= r) {
                            int m = (l + r) >> 1;
                            if(!IsEmpty(1, m)) {
                                l = m + 1;
                                ed = m;
                            }else
                                r = m - 1;
                        }
                        l = st;
                        r = ed;
                        printf("Free from %d to %d\n", l, r);
                        Insert(1, l, r, EK_EMPTY);
                    }
                }else {
                    int K = FindKCount(x);
                    if(K == n + 1)
                        printf("Reject Get\n");
                    else
                        printf("Get at %d\n", K);
                }
            }
        }
        puts("");
    }
    return 0;
}

