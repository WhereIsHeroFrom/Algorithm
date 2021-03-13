#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

typedef char ValueType;
const int maxn = 1010;
int f[2][maxn];
int p[maxn][maxn];

int pack(int x, int y) {
    return x * maxn + y;
}

int getLCSLength(int hsize, ValueType *h, int vsize, ValueType *v, stack<int>& path) {
    memset(f, 0, sizeof(f));
    while (!path.empty())
        path.pop();
    int cur = 1, last = 0;
    for (int i = 1; i <= vsize; ++i) {
        for (int j = 1; j <= hsize; ++j) {
            if (v[i] == h[j]) {
                f[cur][j] = f[last][j - 1] + 1;
                p[i][j] = pack(i - 1, j - 1);
            }
            else {
                f[cur][j] = max(f[last][j], f[cur][j - 1]);
                p[i][j] = f[last][j] > f[cur][j - 1] ? pack(i - 1, j) : pack(i, j - 1);
            }
        }
        swap(last, cur);
    }
    int vidx = vsize, hidx = hsize;
    while (vidx && hidx) {
        int pre = p[vidx][hidx];
        int previdx = pre / maxn;
        int prehidx = pre % maxn;
        if (vidx - previdx && prehidx - hidx) {
            path.push(vidx * maxn + hidx);
        }
        vidx = previdx;
        hidx = prehidx;
    }
    return f[last][hsize];
}

char s[2][maxn];
char t[1010];

int main() {
    int len[2];
    while (scanf("%s %s", &s[0][1], &s[1][1]) != EOF) {
        len[0] = strlen(&s[0][1]);
        len[1] = strlen(&s[1][1]);
        stack <int> path;
        getLCSLength(len[0], s[0], len[1], s[1], path);
        int h = 1, v = 1;
        while (!path.empty()) {
            int val = path.top();
            path.pop();

            int toh = val % maxn;
            int tov = val / maxn;
            //printf("(%d, %d)\n", toh, tov);
            while (h < toh) {
                printf("%c", s[0][h++]);
            }

            while (v < tov) {
                printf("%c", s[1][v++]);
            }

            printf("%c", s[0][h]);
            ++h, ++v;

        }
        while (h <= len[0]) {
            printf("%c", s[0][h++]);
        }

        while (v <= len[1]) {
            printf("%c", s[1][v++]);
        }
        puts("");

    }
    return 0;
}
