/*
    题意：给定一个 n (n <= 10^5) 个元素的序列，假设 dp[i] 表示以第 i 个数结尾的最长递增子序列的长度，
    求一个字典序最小的序列，它的第i个数的最长递增子序列长度为 dp[i] (且对于任意的 i 都满足)。

    题解：
*/
#include <iostream>

using namespace std;

struct Pair {
    int w, s;

    bool operator <= (const Pair& p) const {
        return (w < p.w) && (s > p.s);
    }
    bool operator < (const Pair& p) const {
        return (w < p.w);
    }
};

/*******************************************最长递增子序列 模板*******************************************/
typedef int ValueType;
const int maxn = 1000010;
// 在 g 数组中找的时候
// 如果是严格单调，则用 <= 
// 如果是非递增或非递减，则用 < 
ValueType g[maxn];
int f[maxn];
int gsize;

enum LISType {
    LIST_STRICTLY = 0,            // 严格单调
    LIST_NOTSTRICTLY = 1,         // 非严格单调
};

bool cmpLIS(LISType lt, ValueType a, ValueType b) {
    if (LISType::LIST_STRICTLY == lt) {
        return a <= b;
    }
    else if (LISType::LIST_NOTSTRICTLY == lt) {
        return a < b;
    }
}

int findLISIndex(LISType lt, ValueType val, ValueType *g, int& gsize) {
    int l = 1, r = gsize, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if ( cmpLIS(lt, val, g[mid]) ) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

void findLIS(LISType lt, ValueType *a, int asize, ValueType *g, int& gsize, int* f) {
    gsize = 0;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];
        f[i] = ans;
    }
}


/*******************************************最长递增子序列 模板*******************************************/

ValueType a[maxn];

int main() {
    int n, k;
    int cas = 0, t;
    scanf("%d", &t);
    while (t--){

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            a[i] = x;
        }
        findLIS(LIST_STRICTLY, a, n, g, gsize, f);
        bool bSame = true;
        for (int i = 1; i <= n; ++i) {
            if (a[i] != f[i]) {
                bSame = false;
                break;
            }
        }
        if (bSame) {
            ++f[n];
        }
        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                printf(" ");
            }
            printf("%d", f[i]);
        }
        
        puts("");
    }
    return 0;
}
