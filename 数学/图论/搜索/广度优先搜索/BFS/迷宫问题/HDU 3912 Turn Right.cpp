#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n, m;

const int DIR_COUNT = 4;

enum eDirection {
    ED_RIGHT = 0,
    ED_UP = 1,
    ED_LEFT = 2,
    ED_DOWN = 3,
};

const int dir[DIR_COUNT][2] = {
    { 0, 1 },   // 0. 右
    { -1, 0 },  // 1. 上
    { 0, -1 },  // 2. 左
    { 1, 0 },   // 3. 下
};

const int dirIndex[DIR_COUNT][DIR_COUNT] = {
    { 3, 0, 1, 2 },
    { 0, 1, 2, 3 },
    { 1, 2, 3, 0 },
    { 2, 3, 0, 1 },
};

const int MAXN = 510;
bool block[MAXN][MAXN][DIR_COUNT];        // block[x][y][d]     (x,y)的d方向是否有障碍
int step[MAXN][MAXN][DIR_COUNT];
int b[MAXN][MAXN];

struct Pos {
    int x, y, d;
    Pos() {}
    Pos(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {

    }
    bool isValid() {
        if (x < 0 || y < 0 || x >= n || y >= m) {
            return false;
        }
        return true;
    }
    int getStep() {
        return step[x][y][d];
    }
    void setStep(int s) {
        step[x][y][d] = s;
    }

    void print() {
        printf("[%d %d] [%d]\n", x, y, d);
    }

    bool operator == (const Pos & o) {
        return x == o.x && y == o.y;
    }
};


Pos pStart, pEnd;

void bfs(Pos start) {
    memset(step, -1, sizeof(step));
    queue <Pos> Q;
    Q.push(start);
    start.setStep(0);

    while (!Q.empty()) {
        start = Q.front();
        Q.pop();

        int stp = start.getStep() + 1;
        // start.print();

        for (int i = 0; i < 4; ++i) {
            // 按照右手系顺序，得到的方向为
            int d = dirIndex[start.d][i];
            // 检测这个格子对应方向是否能走
            bool canstep = !block[start.x][start.y][d];
            if (canstep) {
                Pos next = Pos(start.x + dir[d][0], start.y + dir[d][1], d);
                if (!next.isValid()) continue;

                if (next.getStep() == -1) {
                    next.setStep(stp);
                    Q.push(next);
                }
                break;
            }
        }
    }
}

int main() {
    int t;
    int v;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d", &n, &m, &pStart.y, &pEnd.y);
        pStart.x = 0;
        pStart.d = 3;

        pEnd.x = n - 1;
        pEnd.d = 3;

        memset(block, 0, sizeof(block));

        for (int i = 0; i < (n << 1) - 1; ++i) {
            if (i & 1) {
                int r = (i + 1) >> 1;
                for (int j = 0; j < m; ++j) {
                    scanf("%d", &v);
                    block[r - 1][j][eDirection::ED_DOWN] = v;
                    block[r][j][eDirection::ED_UP] = v;
                }
            }
            else {
                int r = (i >> 1);
                for (int j = 0; j < m - 1; ++j) {
                    scanf("%d", &v);
                    block[r][j][eDirection::ED_RIGHT] = v;
                    block[r][j + 1][eDirection::ED_LEFT] = v;
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            block[0][i][eDirection::ED_UP] = (pStart.y == i) ? 0 : 1;
            block[n - 1][i][eDirection::ED_DOWN] = (pEnd.y == i) ? 0 : 1;
        }

        for (int i = 0; i < n; ++i) {
            block[i][0][eDirection::ED_LEFT] = 1;
            block[i][m - 1][eDirection::ED_RIGHT] = 1;
        }
        memset(b, 0, sizeof(b));

        bfs(pStart);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (step[i][j][0] != -1 || step[i][j][1] != -1 || step[i][j][2] != -1 || step[i][j][3] != -1) {
                    b[i][j] = 1;
                }
            }
        }


        Pos temp = pStart; pStart = pEnd; pEnd = temp;
        pStart.d = pEnd.d = 1;
        bfs(pStart);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (step[i][j][0] != -1 || step[i][j][1] != -1 || step[i][j][2] != -1 || step[i][j][3] != -1) {
                    b[i][j] = 1;
                }
            }
        }

        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (b[i][j] == 0) {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }

        printf("%s\n", flag ? "YES" : "NO");
    }

    return 0;
}

/*
1212
1 3 0 0
0 0

*/