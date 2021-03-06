#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXV 1000000000
#define MAXN 100010
#define MAXLOGN 18
#define LL __int64

LL nodeSum[MAXLOGN][MAXN];
bool isLeftEnd[MAXLOGN][MAXN];

int a[MAXN];

struct interval {
    int dep, l, r;
    interval() {
    }
    interval(int _dep, int _l, int _r) {
        dep = _dep;
        l = _l;
        r = _r;
    }
    void print() {
        printf("%d %d %d\n", dep, l, r);
    }
};


void merge_sort(LL* tar, LL* srcl, int srclsize, LL* srcr, int srcrsize) {
    int lp = 0, rp = 0;
    while( lp < srclsize || rp < srcrsize )    {
        if(lp == srclsize || (rp != srcrsize) &&  srcr[rp] <= srcl[lp]) {
            tar[lp+rp] = srcr[rp];
            rp ++;
        }else if( rp == srcrsize || (lp != srclsize) && srcl[lp] < srcr[rp] ) {
            tar[lp+rp] = srcl[lp];
            lp++;
        }
    }
}

void build(int depth, int l, int r) {
    if(l == r) {
        nodeSum[depth][l] = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(depth+1, l, mid);
    build(depth+1, mid+1, r);
    merge_sort( &nodeSum[depth][l], &nodeSum[depth+1][l], mid-l+1, &nodeSum[depth+1][mid+1], r-mid );
}

void build_sum(int depth, int l, int r) {
    
    isLeftEnd[depth][l] = true;
    if(l == r) {
        return;
    }
    
    for(int i = l + 1; i <= r; i++) {
        nodeSum[depth][i] += nodeSum[depth][i-1];
    }
    
    int mid = (l + r) >> 1;
    build_sum(depth+1, l, mid);
    build_sum(depth+1, mid+1, r);
    
}

void getInterval(interval* ret, int& retsize, int dep, int s, int t, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == s && r == t) {
        ret[ ++retsize ] = interval(dep, s, t);
        return ;
    }
    if(t <= mid) {
        getInterval(ret, retsize, dep+1, s, t, l, mid);
    }else if(s >= mid + 1) {
        getInterval(ret, retsize, dep+1, s, t, mid+1, r);
    }else {
        getInterval(ret, retsize, dep+1, s, mid, l, mid);
        getInterval(ret, retsize, dep+1, mid+1, t, mid+1, r);
    }
}

__int64 getNumber(int dep, int pos) {
    __int64 pre = 0;
    if (isLeftEnd[dep][pos]) {
        pre = 0;
    }else {
        pre = nodeSum[dep][pos-1];
    }
    return nodeSum[dep][pos] - pre;
}

// 在给定区间内，小于等于给定数的个数
// LE = less or equal than 
int getLENumberCount(interval I, int val, bool includeEqual) {
    // I 对应到线段树中的某个完全覆盖的结点
    int l = I.l, r = I.r;
    int ans = I.l - 1;    // ans表示最大的小于val的数 
    
    while(l <= r) {
        int mid = (l + r) >> 1;
        int num = getNumber(I.dep, mid);
        
        if(num < val || includeEqual && num == val  ) {
            ans = mid;
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    } 
    return ans - I.l + 1;
}

// 在一堆有序数组中得到 小于某个数的个数 
int getLTNumberCountInArray(interval* ary, int arysize,  int val) {
    int cnt = 0;
    for(int i = arysize; i > 0; i--) {
        cnt += getLENumberCount(ary[i], val, false);
    }
    return cnt;
}

// 在一堆有序数组中得到 小于等于某个数的个数 
int getLENumberCountInArray(interval* ary, int arysize, int val) {
    int cnt = 0;
    for(int i = arysize; i > 0; i--) {
        cnt += getLENumberCount(ary[i], val, true);
    }
    return cnt;
}

// 在一堆有序数组中得到 小于等于某个数的数的总和
__int64 getLENumberSumInArray(interval* ary, int arysize, int val) {
    __int64 tot = 0;
    for(int i = arysize; i > 0; i--) {
        int cnt = getLENumberCount(ary[i], val, false);
        if(cnt)
            tot += nodeSum[ary[i].dep][ ary[i].l + cnt - 1 ];    
    }
    return tot;
}

int b[MAXN], bs;
int L;
// 在一堆有序数组中得到第K大的数 
int getKthNumber(interval* ary, int arysize, int k) {
    int l = 1, r = L;
    int i;
    int ans = -1;
    
    while(l <= r) {
        int mid = (l + r) >> 1;
        int tot = 0;
        for(i = arysize; i > 0; i--) {
            tot += getLENumberCount (ary[i], b[mid], true);
        }
        if(tot >= k) {
            ans = mid;
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
    return b[ans];
}


interval ret[100];
int retsize = 0;

int main() {
    int Q, i, j, t, cases = 0;
    int n;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < MAXLOGN; i++) {
            for(j = 0; j <= n; j++) {
                isLeftEnd[i][j] = 0;
            }
        }
        bs = 0;
        L = 1;
        for(i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[++bs] = a[i];
        }
        sort(&b[1], &b[1] + bs);
        for(i = 2; i<= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        build(0, 1, n);
        build_sum(0, 1, n);
        /*for(i = 0; i < 10; i++) {
            for(j = 1; j <= n; j++) {
                printf("%I64d ", nodeSum[i][j]);
            }
            puts("");
        }*/
        printf("Case #%d:\n", ++cases);
        scanf("%d", &Q);
        while(Q--) {
            int l, r;
            scanf("%d %d", &l, &r);
            l++, r++;
            retsize = 0;
            getInterval(ret, retsize, 0, l, r, 1, n);
            int len = r-l+1;
            int k = len/2+1;
            int kval = getKthNumber(ret, retsize, len/2+1);
            //printf("%d\n", kval);
            
            // 前 (len/2+1)个数的总和为 sum1
            __int64 sum1 =  (k - getLTNumberCountInArray(ret, retsize, kval)) * (__int64) kval + getLENumberSumInArray(ret, retsize, kval);
            // 后len - (len/2+1)个数的总和为 sum2 
            __int64 sum2 = getLENumberSumInArray(ret, retsize, MAXV) - sum1;
            //printf( "%d %I64d %I64d %I64d\n", getLTNumberCountInArray(ret, kval), getLENumberSumInArray(ret, kval), sum1, sum2 );
            
            __int64 ans = (__int64)kval*k - sum1 + sum2 - (__int64)(len-k)*kval;
            printf("%I64d\n", ans );
        }
        puts("");
        
    }
    return 0;
}

/*
6
10
11 8 5 5 5 5 5 61 7 31
10
0 4

3

8
4 5 6 7 8 9 9 9
10
2 6
3 7
1 5
0 3

5
3 6 2 2 4
2
1 4
0 2

2
7 7
2
0 1
1 1

*/
