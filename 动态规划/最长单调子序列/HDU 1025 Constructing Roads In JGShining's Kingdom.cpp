#include <iostream>

using namespace std;


/*******************************************最长递增子序列 模板*******************************************/
typedef int ValueType;
const int maxn = 1000010;
// 在 g 数组中找的时候
// 如果是严格单调，则用 <= 
// 如果是非递增或非递减，则用 < 
ValueType g[maxn];
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

void findLIS(LISType lt, ValueType *a, int asize, ValueType *g, int& gsize) {
    gsize = 0;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans != -1) {
            g[ans] = a[i];
        }
        else {
            g[++gsize] = a[i];
        }
    }
}


/*******************************************最长递增子序列 模板*******************************************/

ValueType a[maxn];

int main() {
    int n;
    int cas = 0;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            a[x] = y;
        }
        findLIS(LIST_STRICTLY, a, n, g, gsize);
        printf("Case %d:\nMy king, at most %d road%s can be built.\n\n", ++cas, gsize, gsize > 1 ? "s" : "");
    }
    return 0;
}