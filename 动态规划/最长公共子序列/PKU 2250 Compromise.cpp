#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

struct Word {
    char data[110];

    bool operator == (const Word& w) const {
        return strcmp(data, w.data) == 0;
    }
};

typedef Word ValueType;
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

Word w[2][110];

void calc(int hsize, ValueType h[110], int vsize, ValueType v[110]) {
    stack <int> st;
    int l = getLCSLength(hsize, h, vsize, v, st);
    int flag = 0;
    while (!st.empty()) {
        int val = st.top();
        st.pop();
        if (flag++) printf(" ");
        printf("%s", v[val / maxn].data);
    }
    puts("");
    return;

}
int main() {
    int ws[2];
    int idx = 0;
    ws[0] = ws[1] = 0;
    while (scanf("%s", w[idx][++ws[idx]].data) != EOF) {
        if (w[idx][ws[idx]].data[0] == '#') {
            --ws[idx];
            ++idx;
            if (idx == 2) {
                calc(ws[0], w[0], ws[1], w[1]);
                idx = 0;
                ws[0] = ws[1] = 0;
            }
        }
    }
}