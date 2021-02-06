/*
    题意：K临近问题，K <= 100000
    X 轴上的n( n <= 100000 )个数有各自的权值。
    m ( m <= 100000 ) 次询问，每次询问第 i 个数的 K 临近数的平均值是多少，并且修改这个位置上的数为这个平均值。

    题解：三分区间 + 树状数组

    最小化 区间端点和中间值差值的大者，采用三分枚举


*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll double

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


int n, m, k;
int nowpos[MAXV];

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int checkv(int lpos, int pos, int rpos) {
    return Max(P[pos].X - P[lpos].X, P[rpos].X - P[pos].X);
}

int getMin(int pos, int k, int ans, int b) {
    if (ans == -1) {
        return b;
    }

    int v = checkv(b, pos, b + k);
    int ansv = checkv(ans, pos, ans + k);

    if (v < ansv) {
        return b;
    }
    if (v == ansv) {
        if (ans < b) {
            return P[ans].Idx < P[b + k].Idx ? ans : b;
        }
        else {
            return P[ans+k].Idx < P[b].Idx ? ans : b;
        }
    }


    return ans;
}

int tripleFind(int pos, int k) {
    int l = Max(pos - k, 1), r = Min(pos + k, n) - k;
    int ans = -1;
    while (l <= r) {
        int lm = (2 * l + r) / 3;
        int rm = (l + 2 * r) / 3;

        int lv = checkv(lm, pos, lm + k);
        int rv = checkv(rm, pos, rm + k);

        if (lv == rv) {
            break;
        }
        else if (lv < rv) {
            ans = getMin(pos, k, ans, lm);
            r = rm - 1;
        }
        else if (lv > rv) {
            ans = getMin(pos, k, ans, rm);
            l = lm + 1;
        }
    }

    for (int i = l; i <= r; ++i) {
        ans = getMin(pos, k, ans, i);
    }

    return ans;
}


int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            P[i].read(i);
        }
        sort(P + 1, P + n + 1);
        clear();

        for (int i = 1; i <= n; ++i) {
            add(i, n, P[i].V);
            nowpos[P[i].Idx] = i;
        }

        double sums = 0;
        while (m--) {
            int pos;
            scanf("%d %d", &pos, &k);
            pos = nowpos[pos];

            int nwpos = tripleFind(pos, k);
            
            double s = sum(nwpos + k) - sum(nwpos - 1);
            double v = sum(pos) - sum(pos-1);
            s = (s - v) / k;

            add(pos, n, -v + s);
            sums += s;
        }
        printf("%.3lf\n", sums);
    }

    return 0;
}







/*
10
10 10 4

10 7
9  6
7 4 
8 5 
6 6 
1 7
2 8 
3 9 
4 0
5 10

1 2 3 4 5 6 7 8 9 10

60.226624


10
30 200 5
91222180 711
92122121  611
71111111 411
82121121 51
12122116 6111
12121121 711
11212115 811
2121213 911
42112121 011
51111111 1011
912221180 711
921212121  611
711111111 411
821212121 51
121212116 6111
121212121 711
112121115 811
212121213 911
421212121 011
511111111 1011
11 1
21 2
311 3
41111 4
5111 5
611 6
7111 7
11118 8
911 9
111110 10

10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
20 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 28 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6
10 9 8 7 1 2 3 4 5 6 10 9 8 7 1 2 3 4 5 6


2 2 1
1 2113
2 312
2 1


56.473638

10
5 1 1
10 7
9  6
7 4
8 5
6 6
5


10
10 10 10
10 7
9  6
7 4
8 5
6 6
1 3
2 5
3 8
4 9
5 100
1 2 3 4 5 10 9 8 7 6



*/

/*
10
6 1
10   1
8     2
5     3
2     4
0     5
-10   6 
3 4

11

5 3 3
5 8
4 8
3 6
2 3
1 2
4 3 2
*/