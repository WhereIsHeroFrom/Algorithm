#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

// RMQ 区间最小值询问

const int MAXM = 18;
const int MAXN = (1 << MAXM) + 1;

// typedef long long ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

int RMQ_MinIndex(ValueType A[], int l, int r) {
    return A[r] < A[l] ? r : l;
}

// f[i][j] = opt(f[i-1][j], f[i-1][j + 2^{i-1}]);
void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
    int i, j, k = 0;
    for (i = 1; i <= ALen; i++) {
        lg2K[i] = k - 1;
        if ((1 << k) == i) k++;
    }
    for (i = 0; i < MAXM; i++) {
        for (j = 1; j + (1 << i) - 1 <= ALen; j++) {
            if (i == 0) {
                f[i][j] = j;
            }
            else {
                f[i][j] = RMQ_MinIndex(A, f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
}

/*
设区间长度为2^k，则X表示的区间为[a, a + 2^k)，Y表示的区间为(b - 2^k, b]，
则需要满足一个条件就是X的右端点必须大于等于Y的左端点-1，即 a+2^k-1 >= b-2^k，
则2^(k+1) >= (b-a+1), 两边取对数（以2为底），得 k+1 >= lg(b-a+1)，则k >= lg(b-a+1) - 1。
k只要需要取最小的满足条件的整数即可( lg(x)代表以2为底x的对数 )。
*/
int RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
    if (a == b) {
        return a;
    }
    else if (a > b) {
        a = a^b, b = a^b, a = a^b;
    }
    int k = lg2K[b - a + 1];
    return RMQ_MinIndex(A, f[k][a], f[k][b - (1 << k) + 1]);
}


int n;
int f[MAXM][MAXN];

// RMQ 求最小值，b[i]= -a[i]，用b[i]求最大值
int a[MAXN], b[MAXN];

// dp[i] 代表当 i 这个元素取的时候，往后的单调递增序列的长度
int dp[MAXN];

bool check(int l, int r, int val) {
    return -b[RMQ_Query(b, f, l, r)] > val;
}

// 在 [l, r] 区间内找到下标最接近 l 且 > value 的数
// 二分区间，如果区间 [l, mid] 内的最大值能够找到，则缩小区间；
// 特殊的，当 l>r时或者找不到时，直接返回最大值 n+1
int getFirstBiggerThan(int l, int r, int value) {
    int ans = n + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;

        if (check(l, mid, value)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

int pre[MAXN];
int has[MAXN];
int sum[MAXN];

void preProcess() {
    memset(has, 0, sizeof(has));
    a[0] = 0;
    sum[0] = 0;

    a[n + 1] = 2000000000;
    int now = 0;

    for (int i = 1; i <= n + 1; ++i) {
        pre[i] = now;
        sum[i] = sum[i - 1];
        if (a[i] > a[now]) {
            now = i;
            has[now] = 1;
            ++sum[now];
        }
    }

}

int main() {
    int t;
    int Q;
    int i;

    scanf("%d", &t);

    while (t--) {

        scanf("%d %d", &n, &Q);
        a[0] = 0;
        a[n + 1] = 2000000000;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (i = 0; i <= n + 1; ++i) {
            b[i] = -a[i];
        }
        RMQ_Init(b, n + 1, f);
        preProcess();
        int total = sum[n + 1] - 1;

        dp[n + 1] = 0;
        for (i = n; i >= 1; --i) {
            int ans = getFirstBiggerThan(i + 1, n + 1, a[i]);
            dp[i] = dp[ans] + 1;
        }

        while (Q--) {
            int p, q;
            scanf("%d %d", &p, &q);

            int ans;
            if (has[p]) {
                if (q <= a[pre[p]]) {
                    // 第 p 个值 取不到
                    ans = sum[pre[p]] + dp[getFirstBiggerThan(p + 1, n + 1, a[pre[p]])];
                }
                else {
                    // 第 p 个值 取得到
                    ans = sum[p] + dp[getFirstBiggerThan(p + 1, n + 1, q)];
                }
            }
            else {
                if (q <= a[pre[p]]) {
                    ans = total;
                }
                else if (q > a[pre[p]]) {
                    ans = sum[pre[p]] + 1 + dp[getFirstBiggerThan(p + 1, n + 1, q)];
                }
            }

            printf("%d\n", ans);
        }
    }



    return 0;
}

/*
10000000
13 100
1 5 6 4 8 5 3 7 8 9 8 6 10
1 9

*/