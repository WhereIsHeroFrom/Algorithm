#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;
#pragma warning(disable : 4996)

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

const int MAXN = 25;
bool block[MAXN][MAXN][DIR_COUNT];        // block[x][y][d]     (x,y)的d方向是否有障碍
char mat[MAXN][MAXN];
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

    bool operator == (const Pos& o) {
        return x == o.x && y == o.y;
    }
};


Pos pStart, pEnd;

int bfs(Pos start, Pos end) {
    memset(step, -1, sizeof(step));
    queue <Pos> Q;
    Q.push(start);
    start.setStep(0);

    while (!Q.empty()) {
        start = Q.front();
        Q.pop();
        if (start == end) {
            return start.getStep();
        }
        int stp = start.getStep() + 1;
        // start.print();

        for (int i = 0; i < 2; ++i) {
            // 按照右手系顺序，得到的方向为
            int d = dirIndex[start.d][i];
            int nx = start.x + dir[d][0];
            int ny = start.y + dir[d][1];
            // 检测这个格子对应方向是否能走
            bool canstep = (mat[nx][ny] != 'X');
            if (canstep) {
                Pos next = Pos(start.x + dir[d][0], start.y + dir[d][1], d);
                if (!next.isValid()) continue;

                if (next.getStep() == -1) {
                    next.setStep(stp);
                    Q.push(next);
                }
                // break;
            }
        }
    }
    return 111111111;
}

int main() {
    int t;
    int v;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        getchar();
        for (int i = 0; i < n; ++i) {
            gets(mat[i]);
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == 'S') {
                    pStart.x = i;
                    pStart.y = j;
                }
                else if (mat[i][j] == 'F') {
                    pEnd.x = i;
                    pEnd.y = j;
                }
            }
        }
        int ret = 1000000;
        for (int i = 0; i < 4; ++i) {
            pStart.d = i;
            int ans = bfs(pStart, pEnd);
            if (ans < ret) ret = ans;
        }
        printf("%d\n", ret);

    }

    return 0;
}

/*
1212
1 3 0 0
0 0

*/