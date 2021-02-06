/*
    题意：K 临近问题
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll long long

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    while (x <= maxn) {
        c[x] += v;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

struct XV {
    int X;
    int Idx;
    double V;
    
    void read(int i) {
        int v;
        scanf("%d %d", &X, &v);
        V = v;
        Idx = i;
    }
    bool operator < (const XV& o) const {
        return X < o.X;
    }
}P[MAXV];

struct Index {
    int idx;
    int abs;

    Index() {}
    Index(int i, int a) : idx(i), abs(a) {

    }

    bool operator < (const Index& i) const {
        if (abs != i.abs) {
            return abs > i.abs;
        }
        return P[idx].Idx > P[i.idx].Idx;
    }
};


int n, m, k;
int nowpos[MAXV];

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d", &n, &m, &k);
        for (int i = 1; i <= n; ++i) {
            P[i].read(i);
        }
        sort(P + 1, P + n + 1);
        for (int i = 1; i <= n; ++i) {
            nowpos[P[i].Idx] = i;
        }

        double sums = 0;
        while (m--) {
            int pos;
            scanf("%d", &pos);
            pos = nowpos[pos];

            priority_queue <Index> q;
            for (int i = 1; i <= k; ++i) {
                if (pos - i >= 1)
                    q.push(Index(pos - i, P[pos].X - P[pos - i].X));
            }
            for (int i = 1; i <= k; ++i) {
                if (pos + i <= n)
                    q.push(Index(pos + i, P[pos + i].X - P[pos].X));
            }
            int cnt = k;
            double s = 0;
            while (cnt--) {
                Index I = q.top();
                q.pop();


                s += P[I.idx].V;

            }
            s /= k;
            P[pos].V = s;
            sums += P[pos].V; 
        }
        printf("%.6lf\n", sums);
    }

    return 0;
}
/*
5 3 2
5 8
4 8
3 6
2 3
1 2
2
3
4
*/