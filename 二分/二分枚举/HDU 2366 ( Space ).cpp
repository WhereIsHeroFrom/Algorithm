#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define LL __int64

struct Point {
    int x, y;
    void read() {
        scanf("%d %d", &x, &y);
    }
    void print() {
        printf("<%d, %d>\n", x, y);
    }
    bool operator<(const Point& p) {
        if(x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
}P[MAXN];

int n, d, d2;
vector <Point> pt[MAXN];
int ptsize[MAXN];
int start[MAXN];

LL sqr(LL x) {
    return x*x;
}

// 找到差值平方<val的最大下标
int findY(int val, int y, int pidx, int nowidx) {
    int l = nowidx+1, r = ptsize[pidx]-1, ans = nowidx;
    while(l <= r) {
        int mid = (l + r) / 2;
        if( sqr(pt[pidx][mid].y - y) < val) {
            ans = mid;
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    int t;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &d);
        d2 = d*d;
        for(i = 0; i < n; i++) {
            P[i].read();
            pt[i].clear();
        }
        sort(P, P + n);
        /*int c = 0;
        for(i = 0; i < n; ++i) {
            for(j = i+1; j < n; ++j) {
                if(sqr(P[i].x-P[j].x) + sqr(P[i].y-P[j].y) < d*d) c++;
            }
        }
        printf("real ans = %d\n", c);*/
        
        int    p = 0;
        pt[0].push_back(P[0]);
        for(i = 1; i < n; ++i) {
            if(P[i].x == pt[p][0].x) {
                pt[p].push_back(P[i]);
            }else {
                pt[++p].push_back(P[i]);
            }
        }
        ++p;

        for(i = 0; i < p; ++i) {
            ptsize[i] = pt[i].size();
            /*printf("----%d-----\n", i);
            for(j = 0; j < pt[i].size(); ++j) {
                pt[i][j].print();
            }*/
        }

        LL ans = 0;
        for(i = 0; i < p; ++i) {
            for(j = 0; j < ptsize[i]; ++j) {
                ans += findY(d2, pt[i][j].y, i, j) - j;
                //printf("<[%d], %d> = %I64d\n", i, j, ans);
            }
        }


        for(i = 0; i < p; ++i) {
            for(j = i+1; j < p; ++j) {
                // 强有力剪枝
                int deltaX = pt[j][0].x - pt[i][0].x;
                if(deltaX >= d) {
                    break;
                }
                int y2Limit = d2 - (int)sqr(deltaX);
                start[j] = 0;

                for(k = 0; k < ptsize[i]; ++k) {
                    int yFrom = pt[i][k].y;
                    while(start[j] < ptsize[j]) {
                        int &yTo = pt[j][start[j]].y;
                        if(yTo <= yFrom && sqr(yFrom - yTo) >= y2Limit) {
                            ++start[j];
                        }else 
                            break;
                    }
                    if(start[j] == ptsize[j]) {
                        break;
                    }
                    if(sqr(yFrom - pt[j][start[j]].y) >= y2Limit) {
                        continue;
                    }
                    ans += findY(y2Limit, yFrom, j, start[j]-1) - (start[j]-1);
                }
                //printf("<%d, %d> = %I64d\n", i, j, ans);
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

/*
10
7 4
0 1
0 2
0 3
0 4
0 5
0 6
0 7

16 3
0 0
0 3
2 1
2 3
3 0
3 1
4 0
4 1
4 2
4 3
4 4
4 5
5 0
5 2
5 4
5 6
*/
