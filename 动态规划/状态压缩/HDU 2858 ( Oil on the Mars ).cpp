#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define INF -100000000
#define MAXN 18

int N, M, K;
int mat[MAXN][MAXN];
int sum[MAXN][MAXN];

// dp[k][r][l][r][0-3]
// 前四维分别表示在第r行取的为[l,r]这个区间的格子，
// 并且r行以上取的格子一定满足左区间最多一个极值，右区间最多一个极值，总共取k个的最大值
// 最后一维的意义为：
// 0 左区间递减、右区间递增
// 1 左区间递减、右区间递减
// 2 左区间递增、右区间递增
// 3 左区间递增、右区间递减

int dp[MAXN*MAXN][MAXN][MAXN][MAXN][4];
int pre[MAXN*MAXN][MAXN][MAXN][MAXN][4];

int Min(int a, int b) {
    return a < b ? a : b;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

bool isLAscending(int mask) {
    return (mask & 2) != 0;
}

bool isRAscending(int mask) {
    return (mask & 1) == 0;
}

int c = 0;
int getPackCode(int l, int r, int mask) {
    return (mask << 16) | (l << 8) | r;
}

int calc(int cnt, int row, int l, int r, int mask) {
    if(cnt == 0) {
        return 0;
    }

    if( cnt < (r - l + 1) || cnt > (row-1)*M + (r - l + 1) ) {
        return INF;
    }
    if(mask == 0) {
        if( cnt > row * (r - l + 1) ) {
            return INF;
        }
    }

    if(row == 1) {
        if(cnt == (r - l + 1) && mask == 0) {
            return sum[1][r] - sum[1][l-1];
        }else {
            return INF;
        }
    }
    int i, j, premask;
    int MaxVal = INF;

    for(premask = 0; premask < 4; premask++) {
        // 可行性剪枝

        // 当前行左区间递减，上一行左区间递增，不符合题意
        if( !isLAscending(mask) && isLAscending(premask) ) {
            continue;
        }
        // 当前行右区间递增，上一行右区间递减，不符合题意
        if( isRAscending(mask) && !isRAscending(premask) ) {
            continue;
        }

        // 枚举上一行区间
        for(i = 1; i <= r; i++) {
            if( isLAscending(mask) && (l < i) || !isLAscending(mask) && (l > i) ) continue;

            for(j = Max(i, l); j <= M; j++) {
                
                if( isRAscending(mask) && (r < j) || !isRAscending(mask) && (r > j) ) continue;

                int precnt = cnt - (r - l + 1);
                int preval = dp[precnt][row-1][i][j][premask];
                if( preval > MaxVal ) {
                    MaxVal = preval;
                    pre[cnt][row][l][r][mask] = getPackCode(i, j, premask);
                    c ++;
                }
            }
        }
    }

    return MaxVal + sum[row][r] - sum[row][l-1];
}

class pathInfo {
public:
    int cnt;
    int row;
    int l, r, mask;
    pathInfo(){}
    pathInfo(int _c, int _row, int _l, int _r, int _m) {
        cnt = _c;
        row = _row;
        l = _l;
        r = _r;
        mask = _m;
    }
    int getPrePackCode() {
        return pre[cnt][row][l][r][mask];
    }
};

class posInfo {
public:
    int r, c;
    posInfo(){}
    posInfo(int _r, int _c) {
        r = _r;
        c = _c;
    }
}p[10000];

int cmp( posInfo a, posInfo b ) {
    if(a.r == b.r) {
        return a.c < b.c;
    }
    return a.r < b.r;
}

int main() {
    int i, j, k;
    int l, r;

    while( scanf("%d %d %d", &N, &M, &K) != EOF) {
        for(i = 1; i <= N; i++) {
            for(j = 1; j <= M; j++) {
                scanf("%d", &mat[i][j]);
                sum[i][j] = sum[i][j-1] + mat[i][j];
            }
        }
        memset(dp, -1, sizeof(dp));
        int MaxV = -1;
        pathInfo ans;

        for(k = 0; k <= K; k++) {
            for(i = 1; i <= N; i++) {
                for(l = 1; l <= M; l++) {
                    for(r = l; r <= M; r++) {
                        for(j = 0; j < 4; j++) {
                            int v = calc(k, i, l, r, j);
                            dp[k][i][l][r][j] = v;
                            if(v > MaxV && k == K) {
                                MaxV = v;
                                ans = pathInfo(k, i, l, r, j);
                            }
                        }
                    }
                }
            }
        }

        //printf("%d\n", c);
        printf("Oil : %d\n", MaxV);
    }
    /*int s = 0;
    while (ans.cnt > 0) {
        int precnt = ans.cnt - (ans.r - ans.l + 1);
        int prerow = ans.row - 1;
        int precode = ans.getPrePackCode();
        int premask = (precode >> 16) & 0xff;
        int prel = (precode >> 8) & 0xff;
        int prer = precode & 0xff;

        for(i = ans.l; i <= ans.r; i++) p[s++] = posInfo(ans.row, i);
        ans = pathInfo(precnt, prerow, prel, prer, premask);
    }

    sort(p, p + s, cmp);
    for(i = 0; i < s; i++) {
        printf("%d %d\n", p[i].r, p[i].c);
    }*/
}

/*
2 3 4 
10 20 30 
40 2 3 

2 3 4
1 2 3
4 5 6

5 4 9
5 4 6 7
3 2 5 7
8 3 4 8
8 4 2 1
8 7 9 12

15 15 225
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

15 15 224
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

6 8 12
0 0 0 0 0 0 0 0
1 1 1 0 0 0 0 0
0 0 1 0 0 0 0 0
0 0 1 1 0 0 0 0
0 0 0 1 1 1 1 1
0 0 0 0 0 0 0 1

3 4 10
0 0 0 0
0 0 0 0
0 0 0 0

3 5 6
0 1 0 1 0
2 1 0 1 0
1 0 0 0 99

3 4 0
0 0 0 0 
0 0 0 0
0 0 0 0
*/

