#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef int ValueType;
const int maxn = 5010;
const ValueType inf = 1e9;
int visited[maxn];
#define maxc 25
ValueType dist[maxn];

// 1. 坐标转换
// 2. 二分查名字： 字符串转数字
// 3. 构建 busstop -> busline，   busline -> busstop  的映射关系
// 4. 寻找满足条件的起点和终点进行 SPFA

int SQR(int x) {
    return x * x;
}

struct Point {
    int x, y;

    void read() {
        scanf("%d %d", &x, &y);
    }

    int distSqr(const Point& o) const {
        return SQR(x - o.x) + SQR(y - o.y);
    }

    void convert(char *str) {
        int p = 40;
        int sx = x * 4, sy = y * 4;
        for (int i = 7; i >= 0; --i) {
            int c = str[i] - '0';
            if (c & 1) {
                sy += p;
            }
            if (c & 2) {
                sx += p;
            }
            p <<= 1;
        }
        x = sx;
        y = sy;
    }
};
char st[10], en[10];
Point s, e;
char str[30];

struct BusPos {
    int id;
    string s;
    Point pt;
    void read(string _s) {
        s = _s;
        pt.read();
    }
    bool operator < (const BusPos& bp) const {
        return s < bp.s;
    }
}B[maxn];

void busstopSort(int n) {
    sort(B, B + n);
}

int busstopFind(int n, char *busstopname) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int cmp = strcmp(B[mid].s.c_str(), busstopname);
        if (cmp == 0) {
            return mid;
        }
        else if (cmp < 0) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
}

vector <int> busLine[110];
vector <int> busStop2Line[maxn];
bool target[maxn];

enum RetType {
    RT_WALK = 0,
    RT_BUS = 1,
    RT_TAXI = 2,
};

bool canWalk(Point st, Point en) {
    return st.distSqr(en) <= SQR(2000);
}

void SPFA(queue <int>& que, int m, ValueType *dist, int& ans) {
    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = 0; i < busLine[u].size(); ++i) {
            int busStop = busLine[u][i];

            if (target[busStop]) {
                ans = min(ans, dist[u]);
            }

            for (int j = 0; j < busStop2Line[busStop].size(); ++j) {
                int nextbusline = busStop2Line[busStop][j];
                if (dist[u] + 1 < dist[nextbusline]) {
                    dist[nextbusline] = dist[u] + 1;
                    que.push(nextbusline);
                }
            }
        }
    }
}


void doSPFA(int n, int m, Point st, Point en, RetType& tp, int& dis) {
    if (canWalk(st, en)){
        tp = RT_WALK;
        return;
    }

    // 目标点标记
    memset(target, false, sizeof(target));
    for (int i = 0; i < n; ++i) {
        if (en.distSqr(B[i].pt) > SQR(1000)) {
            continue;
        }
        target[i] = true;
    }
    dis = inf;
    queue <int> que;
    for (int i = 0; i < m; ++i) {
        int flag = false;

        for (int j = 0; j < busLine[i].size(); ++j) {
            int busStop = busLine[i][j];
            if (st.distSqr(B[busStop].pt) <= SQR(1000)) {
                flag = true;
                break;
            }
        }

        // 找到了一条 busLine
        if (flag) {
            que.push(i);
            dist[i] = 1;
        }
        else {
            dist[i] = inf;
        }
    }
    SPFA(que, m, dist, dis);

    if (dis == inf) {
        tp = RT_TAXI;
    }
    else {
        tp = RT_BUS;
    }
}
int main() {

    int t;
    int n, m;
    int i, j, k;
    scanf("%d", &t);

    while (t--) {

        scanf("%s", st);
        s.read(); s.convert(st);
        scanf("%s", en);
        e.read(); e.convert(en);

        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            scanf("%s", str);
            B[i].read(str);
            busStop2Line[i].clear();
        }
        busstopSort(n);

        scanf("%d", &m);
        for (i = 0; i < m; ++i) {
            scanf("%d", &k);
            busLine[i].clear();
            for (j = 0; j < k; ++j) {
                scanf("%s", str);
                int busId = busstopFind(n, str);
                busLine[i].push_back(busId);
                busStop2Line[busId].push_back(i);
            }
        }
        RetType tp;
        int dis;
        doSPFA(n, m, s, e, tp, dis);
        if (tp == RT_WALK) {
            printf("walk there\n");
        }
        else if (tp == RT_BUS) {
            printf("%d\n", dis);
        }
        else if (tp == RT_TAXI) {
            printf("take a taxi\n");
        }

    }
    return 0;
}

/*
10
00000000 5 5
33333333 10 10
*/