/*
    题意：给定n(n<=10^5)个数A[i] (1 <= i <= n)，求选择一段连续的数，使得它们的平均数大于a，问这样选择的方案数。
    题解：首先所有数减去a，然后统计前缀和sum[i]，那么对于任意的i,j满足 0<=i < j <= n，如果sum[j] - sum[i] > 0，则必然有区间A[i+1...j]大于a。
    那么问题转化成对于每个j，求比它小的i中sum[i]<sum[j]的个数。
    首先将sum[0]...sum[n]这n+1个数进行离散化，离散到[1, n+1]这个区间内，然后每个sum[i]可以利用二分查找找到新的值newSum[i]。
    用树状数组维护，每次统计比newSum[i]小的数，累计入ans；然后将newSum[i]插入树状数组。
    统计完毕，ans就是最后的答案，记得需要int64。
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAXN 100100
#define LL long long

int c[MAXN+1];
int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x) {
    while(x < MAXN) {
        ++c[x];
        x += lowbit(x); 
    }
}

int gsum(int x) {
    int s = 0;
    while(x) {
        s += c[x];
        x ^= lowbit(x); 
    }
    return s;
}

int sum[MAXN];
int val[MAXN], tot;

void unique(int tot, int *val) {
    sort(val+1, val + tot+1);
    int i, ntot = 1;
    for(i = 2; i <= tot; ++i) {
        if(val[i] != val[ntot]) {
            val[ ++ntot ] = val[i]; 
        }
    }
    tot = ntot;
}

int getIdx(int v) {
    int l = 1, r = tot;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(val[mid] == v) {
            return mid;
        }else if(val[mid] > v) {
            r = mid - 1;
        }else {
            l = mid + 1;
        } 
    }
}

int main() {
    int i, t; 
    int a;
    scanf("%d", &t);
    while(t--) {
        memset(c, 0, sizeof(c));
        
        scanf("%d %d", &n, &a);
        tot = 0;
        val[++tot] = sum[0];
        for(i = 1; i <= n; ++i) {
            int x = 0;
            scanf("%d", &x);
            sum[i] = sum[i-1] + (x-a);
            val[++tot] = sum[i];
        }
        unique(tot, val);
        LL ans = 0;
        for(i = 0; i <= n; ++i) {
            int idx = getIdx(sum[i]);
            add(idx);
            ans += gsum(idx-1);
        }
        printf("%lld\n", ans);
    }
    return 0;
} 
