#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
/*
    题意：给定 n (n <= 100) 组数据，第 i 组数据有 m[i] 个二元组，分别为 (b[i][j], p[i][j]);
    要求每组选择出一个二元组，并且使得 min(b) / sum(p) 最大化

    题解：贪心

    1）对所有的b进行排序
    2）枚举所有的b，如果大于等于b的，在每个组里面选择一个 p最小的，这样所有组都能找到的话就累加和
    3）统计 b / sum(p) 最小的就是答案了
*/

int a[10010], atop;
struct v {
    int b, p;
}V[110][110];

#define inf 1000000000

int getminprice(int idx, int m, int minB) {
    int ret = inf;
    for (int i = 0; i < m; ++i) {
        if (V[idx][i].b >= minB) {
            if (V[idx][i].p < ret) ret = V[idx][i].p;
        }
    }
    return ret;
}

double getans(int n, int m, int minB) {
    int i;
    int sump = 0;
    for (i = 0; i < n; ++i) {
        int p = getminprice(i, m, minB);
        if (p == inf) return -inf;
        sump += p;
    }
    return minB * 1.0 / sump;
}

int main() {
    int i, j;
    int n, m;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        atop = 0;
        for (i = 0; i < n; ++i) {
            scanf("%d", &m);
            int max = 0;
            for (j = 0; j < m; ++j) {
                int b, p;
                scanf("%d %d", &b, &p);
                V[i][j].b = b;
                V[i][j].p = p;
                a[atop++] = b;
            }
        }
        sort(a, a + atop);
        double Max = 0.0;
        for (i = 0; i < atop; ++i) {
            if (i && a[i] == a[i - 1]) continue;
            double ans = getans(n, m, a[i]);
            if (ans > Max) Max = ans;
        }
        printf("%.3lf\n", Max);
    }

    return 0;
}

/*
100
3
3 100 1 200 1 300 1 
3 100 2 200 2 300 2
3 100 3 200 3 300 3

*/