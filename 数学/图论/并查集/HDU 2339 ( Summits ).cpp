#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 251000


int n, m;
int p[MAXN];
int hashv[MAXN];
int H[MAXN];
int goDir[MAXN][5];
int allDone[MAXN];

struct Pos {
    int r, c;
    int pos;
    int val;
    void reset(int _r, int _c, int _v) {
        r = _r;
        c = _c;
        pos = r * m + c;
        val = _v;
    }
    bool operator < (const Pos& other) {
        return val > other.val;
    }
}P[MAXN];

void reset_set() {
    int i;
    for(i = n*m; i >= 0; i--) {
        p[i] = i;
        allDone[i] = 0;
        hashv[i] = 0;
    }
}

int find_set(int x) {
    return (p[x] == x) ? x : p[x] = find_set(p[x]);
}

void union_set(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);

    if(px != py) {
        if( H[px] > H[py] ) {
            p[py] = px;
        }else {
            p[px] = py;
        }
    }
}

int dir[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

int pos(int r, int c) {
    return m*r+c;
}

void do_merge(int nowPos) {
    if(allDone[nowPos] == goDir[nowPos][0]) {
        return ;
    }
    // 标记这个点已经可以被连通
    hashv[nowPos] = 1;
    for(int i = 1; i <= goDir[nowPos][0]; ++i) {
        int nextPos = goDir[nowPos][i];
        if( hashv[ nextPos ] ) {
            union_set( nowPos, nextPos );
            ++allDone[nowPos];
        }
    }
}

int main() {
    int t;
    int i, j, k;
    int d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &d);
        reset_set();
        int tot = 0;
        for(i = 0; i < n; ++i) {
            for(j = 0; j < m; ++j) {
                int ps = pos(i, j);
                int &v = H[ps];

                scanf("%d", &v);
                //v = rand() % 30;
                P[tot++].reset(i, j, v);

                goDir[ps][0] = 0;
                for(k = 0; k < 4; ++k) {
                    int tr = dir[k][0] + i;
                    int tc = dir[k][1] + j;
                    if(tr >= n || tr < 0 || tc >= m || tc < 0) {
                        continue;
                    }
                    goDir[ps][ ++goDir[ps][0] ] = pos(tr, tc);
                }
            }
        }
        sort(P, P + tot);

        int ans = 0;
        int pre = 0;
        for(i = 0; i < tot; ++i) {
            // 从P[i]的坡往下找，直到找到第1个j， P[i].val-P[j].val >= d
            // 代表第j个坡是不能由P[i]走到的
            for(j = pre; j < tot; ++j) {
                if(P[i].val - P[j].val >= d) {
                    break;
                }
                do_merge(P[j].pos);
                //printf("(%d, %d) ", P[j].r, P[j].c);
            }
            //printf("<>\n");
            for(k = i; k < j && P[k].val == P[i].val; ++k) {
                if( H[find_set(P[k].pos)] <= H[P[k].pos] ) {
                    //printf("%d %d\n", P[k].r, P[k].c);
                    ++ans;
                }
            }
            i = k - 1;
            pre = j;
        }
        printf("%d\n", ans);

    }
    return 0;
}

/*
6 10 2
2 0 0 0 0 9 9 9 9 9
0 1 2 1 1 5 8 0 1 0
0 2 1 2 9 3 1 9 0 0
0 1 9 1 3 3 1 1 0 0
0 2 1 2 1 1 1 0 2 0
2 0 0 0 0 0 0 0 0 0

3534
500 500 10 500 500 20 500 500 30
50049
50144
49801
*/
