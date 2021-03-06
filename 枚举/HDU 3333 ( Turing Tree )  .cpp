/*
题意：
    给出一个长度为N(N <= 30000)的数列，然后是一连串询问，询问数
<= 100000，问给定区间内不同数字的和。

解法：
离线算法+离散化+线段树

思路：
    乍看之下还是区间求和，但是要求不同数字的和，这题我的做法和一
般的区间询问略有不同，采用离线算法。因为数字的范围较大，所以首先
是对数列进行离散化，一般可以用二分或者hash，将大范围的数字映射到
连续的区间。然后一次性读入所有的区间（整数对），并且对整数对的右
端点进行递增排序。这里注意，要记录下整数对读入的位置下标。接下来
按顺序枚举每个数字val[i]，如果val[i]之前出现过，就将val[i]之前位
置的值删除，然后在当前位置插入，当枚举的位置和区间对中某个位置相
等时执行询问操作。枚举完毕后一次性把答案按区间输入的下标输出即可
。总的复杂度是O(nlog(n))。
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define maxn 200010
#define ll __int64

int n, m;
int val[maxn];
int tmp[maxn], tmpsize;
int bin[maxn], size;
int hash[maxn];
ll ans[maxn];

struct Pair {
    int l, r;
    int idx;
};
vector < Pair > Pa;

bool cmp(Pair a, Pair b) {
    return a.r < b.r;
}

void Process() {
    sort(tmp, tmp + tmpsize);
    bin[ size = 1 ] = tmp[0];
    for(int i = 1; i < tmpsize; i++) {
        if(tmp[i] != tmp[i-1])
            bin[ ++size ] = tmp[i];
    }
}

int Binary(int v) {
    int l = 1;
    int r = size;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(bin[m] == v)
            return m;
        if(v > bin[m])
            l = m + 1;
        else
            r = m - 1;
    }
}

struct Tree {
    ll Sum;
}T[4*maxn];

void Build(int p, int l, int r) {
    T[p].Sum = 0;
    if(l == r) {    
        return ;
    }
    int mid = (l + r) >> 1; 
    Build(p<<1, l, mid);
    Build(p<<1|1, mid+1, r);
}

void Insert(int p, int l, int r, int inPos, int val) {
    if(l == inPos && inPos == r) {
        T[p].Sum += val;
        return ;
    }
    int mid = (l + r) >> 1;
    if(inPos <= mid) {
        Insert(p<<1, l, mid, inPos, val);
    }else {
        Insert(p<<1|1, mid+1, r, inPos, val);
    }
    T[p].Sum = T[p<<1].Sum + T[p<<1|1].Sum;
}

ll Query(int p, int l, int r, int a, int b) {
    if(l == a && b == r) {
        return T[p].Sum;
    }
    int mid = (l + r) >> 1;
    ll v = 0;
    if(b <= mid) {
        v += Query(p<<1, l, mid, a, b);
    }else if(a >= mid + 1) {
        v += Query(p<<1|1, mid+1, r, a, b);
    }else {
        v += Query(p<<1, l, mid, a, mid);
        v += Query(p<<1|1, mid+1, r, mid+1, b);
    }
    return v;
}

int main() {
    int t;
    int i, j;

    scanf("%d", &t);
    while(t--) {
        tmpsize = 0;
        
        scanf("%d", &n);
        for(i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            tmp[ tmpsize++ ] = val[i];
        }

        Process();
        Pa.clear();
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            Pair pt;
            scanf("%d %d", &pt.l, &pt.r);
            pt.idx = i;
            Pa.push_back(pt);
        }
        sort(Pa.begin(), Pa.end(), cmp);
        for(i = 1; i <= size; i++)
            hash[i] = 0;
        Build(1, 1, n);

        j = 0;
        for(i = 1; i <= n; i++) {
            int idx = Binary(val[i]);
            int prePos = hash[idx];
            if( prePos ) {
                Insert(1, 1, n, prePos, -val[i]);
            }
            Insert(1, 1, n, i, val[i]);
            hash[idx] = i;

            for(; j < m; j++) {
                if(Pa[j].r == i) {
                    ans[ Pa[j].idx ] = Query(1, 1, n, Pa[j].l, Pa[j].r);
                }else
                    break;
            }
        }

        for(i = 0; i < m; i++) {
            printf("%I64d\n", ans[i]);
        }
    }
    return 0;
}
