#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;


/*******************************************最长递增子序列 模板*******************************************/
typedef int ValueType;
const int maxn = 100010;
const int inf = -1;
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
    if (LIST_STRICTLY == lt) {
        return a <= b;
    }
    else if (LIST_NOTSTRICTLY == lt) {
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

void findLIS(LISType lt, ValueType *a, int asize) {
    gsize = 0;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];            // g[ans]: 长度为ans的最长递增子序列最后一个值的最小值
    }
}


/*******************************************最长递增子序列 模板*******************************************/

typedef int LCSType;
const int maxc = 100001;

void preLCS(int hsize, LCSType *h, int maxv, vector<int> pos[maxc]) {
    for (int i = 0; i <= maxv; ++i) {
        pos[i].clear();
    }
    for (int i = 1; i <= hsize; ++i) {
        pos[h[i]].push_back(i);
    }
    for (int i = 0; i <= maxv; ++i) {
        reverse(pos[i].begin(), pos[i].end());
    }
}

int a[maxn];

int getLCS(int vsize, LCSType *v, vector<int> pos[26]) {
    int s = 0;
    for (int i = 1; i <= vsize; ++i) {
        int idx = v[i];
        for (int j = 0; j < pos[idx].size(); ++j) {
            a[++s] = pos[idx][j];
        }
    }
    findLIS(LIST_STRICTLY, a, s);
    return gsize;
}



LCSType s[2][maxn];
vector <int> pos[maxc];

int main() {
    //int len[2];
    //while (scanf("%s %s", &s[0][1], &s[1][1]) != EOF) {
    //len[0] = strlen(&s[0][1]);
    //len[1] = strlen(&s[1][1]);
    int n;
    while (scanf("%d", &n) != EOF) {

        for (int j = 0; j < 2; ++j) {
            for (int i = 1; i <= n; ++i) {
                scanf("%d", &s[j][i]);
            }
        }


        preLCS(n, s[0], n, pos);
        int x = getLCS(n, s[1], pos);
        printf("%d\n", x);
    }
    return 0;
}

/*
10
GATCGTGAGC
AGTACG
*/