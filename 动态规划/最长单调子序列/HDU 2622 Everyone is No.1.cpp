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
}P[1010];


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
        return b < a;
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

char mat[30][30];



int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%s", mat[i]);
        }
        int s = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == 'E') {
                    P[++s] = Pair(i, j);
                }
            }
        }
        sort(P + 1, P + s + 1);

        //findLIS(LIST_STRICTLY, P, s, g, gsize, f);
        for (int i = 1; i <= s / 2; ++i) {
            swap(P[i], P[s + 1 - i]);
        }

        int ans = 0;
        for (int i = 1; i <= s; ++i) {
            f[i] = 1;
            for (int j = 1; j < i; ++j) {
                if (P[j].y < P[i].y) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }

            ans = max(ans, f[i]);
        }


        printf("%d\n", ans);

    }

    return 0;
}

/*
6 7
.E.E...
...E.E.
.......
...E..E
.......
.....E.

5 7
EEEEEEE
E...EEE
EE..EEE
....EEE
..EEEEE

6 10
E........
.E.......
..E......
...E.....
........E
........E

1 10
E...E....E

5 5
....E
...E.
..E..
.E...
E....

2 2
EE
EE

6 5
EEEEE
E....
EE...
EEE..
EEEE.
E....

4 4
.EEE
....
..E.
.E..

4 4
.EEE
....
..E.
E...
*/