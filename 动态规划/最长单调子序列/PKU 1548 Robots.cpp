#include <iostream>
#include <algorithm>

using namespace std;

struct Pair {
    int x, y;
    Pair() {}
    Pair(int _x, int _y) : x(_x), y(_y) {}

    bool operator < (const Pair& p) const {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    }
};


/*******************************************最长递增子序列 模板*******************************************/
typedef Pair ValueType;
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
    if (LIST_STRICTLY == lt) {
        return a.y <= b.y;
    }
}

int findLISIndex(LISType lt, ValueType val, ValueType *g, int& gsize) {
    int l = 1, r = gsize, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cmpLIS(lt, val, g[mid])) {
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
        g[ans] = a[i];            // g[ans]: 长度为ans的最长递增子序列最后一个值的最小值
        f[i] = ans;               // f[i]:   以a[i]结尾的最长递增子序列长度
    }
}


/*******************************************最长递增子序列 模板*******************************************/

ValueType P[maxn];

int main() {
    int n;
    while (true) {
        int i = 1;
        while (scanf("%d %d", &P[i].x, &P[i].y) != EOF) {
            if (P[i].x == -1 && P[i].y == -1) {
                return 0;
            }
            if (!P[i].x && !P[i].y) {
                break;
            }
            ++i;
        }
        n = i - 1;
        sort(P + 1, P + n + 1);
        for (int i = 1; i <= n / 2; ++i) {
            swap(P[i], P[n + 1 - i]);
        }


        findLIS(LIST_STRICTLY, P, n, g, gsize, f);
        printf("%d\n", gsize);
    }

    return 0;
}
