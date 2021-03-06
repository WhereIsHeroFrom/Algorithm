/*
题意：
    给定N(N <= 50000)条信息，表示第yi年的降水量是ri，然后给出M(M <= 10000)
条询问，每条询问的格式是Y X，表示自从第Y年以来X这一年是最大的降水量，问这句
话正确与否。
    正确的判断条件是：
1.Y到X这些年的所有年份的降水量已知。
2.Y的降水量 >= X的降水量。
3.对于每个Z，Y < Z < X，Z的降水量小于X的降水量。
    可能正确的判断条件是：
其中有一年的降水量不知道。
    错误的判断条件是：
其他情况。

题解：
    线段树（区间最值）

思路：


*/
#include <iostream>

using namespace std;

#define maxn 50010

int n, m;

struct point {
    int year, r;
}pt[maxn];

struct Tree {
    int Max;
    int l, r;
}T[maxn*4];

int MMax(int a, int b) {
    return a > b ? a : b;
}

void Build(int p, int l, int r) {
    T[p].l = l;
    T[p].r = r;
    if(l == r) {
        T[p].Max = pt[l].r;
        return ;
    }
    int mid = (l + r) >> 1;
    Build(p<<1, l, mid);
    Build(p<<1|1, mid+1, r);
    T[p].Max = MMax(T[p<<1].Max, T[p<<1|1].Max);
}

int Query(int p, int l, int r) {
    if(r < T[p].l || l > T[p].r)
        return 0;
    if(l <= T[p].l && T[p].r <= r) 
        return T[p].Max;
    return MMax(Query(p<<1, l, r), Query(p<<1|1, l, r));
}

int Binary(int val, int l, int r) {
    int ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(pt[m].year <= val) {
            l = m + 1;
            ans = m;
        }else
            r = m - 1;
    }
    return ans;
}

// 连续的块种类
int Coces[maxn];

int main() {
    int i;
    int t = 0;

    while(scanf("%d", &n) != EOF) {

        if(t++ && n) {
            puts("");
        }
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &pt[i].year, &pt[i].r);
            if(i == 1) {
                Coces[i] = 1;
            }else {
                if(pt[i].year - pt[i-1].year == 1)
                    Coces[i] = Coces[i-1];
                else
                    Coces[i] = Coces[i-1] + 1;
            }
        }
        if(n)
            Build(1, 1, n);

        scanf("%d", &m);
        int bufM = m;

        while(bufM--) {
            int Y, X;
            int ans; // 0 true 1 maybe 2 false
            scanf("%d %d", &Y, &X);
            int fY = Binary(Y, 1, n);
            int fX = Binary(X, 1, n);

            if(pt[fY].year == Y && pt[fX].year == X) {        
                // 都能找到数据中有的年份

                int Yr = Query(1, fY, fY);
                int Zr = Query(1, fY+1, fX-1);
                // Y+1 == X 的情况在这里Zr返回的是0，所以肯定满足
                int Xr = Query(1, fX, fX);

                if(Coces[fY] == Coces[fX]) {        
                    // 之间的年份全部连续
                    if(Yr >= Xr && Zr < Xr) {
                        ans = 0;
                    }else
                        ans = 2;
                }else {
                    // 之间的年份不连续
                    if(Yr >= Xr && Zr < Xr) {
                        ans = 1;
                    }else
                        ans = 2;
                }
            }else if(pt[fX].year == X) {
                // X这一年数据中有
                if(Y + 1 == X) {
                    // 当前两年连续
                    ans = 1;
                }else {
                    int Zr = Query(1, fY+1, fX-1);
                    int Xr = Query(1, fX, fX);
                    if(Zr < Xr)
                        ans = 1;
                    else
                        ans = 2;
                }
            }else if(pt[fY].year == Y) {
                int Yr = Query(1, fY, fY);
                int Zr = Query(1, fY+1, fX);
                if(Yr > Zr) {
                    ans = 1;
                }else
                    ans = 2;
            }else {
                // X 和 Y 都没有出现，肯定是maybe
                ans = 1;
            }

            if(!ans)
                puts("true");
            else if(ans == 1)
                puts("maybe");
            else
                puts("false");
        }

        if(!n && !m) {
            break;
        }
    }
    return 0;
}
/*
4
2002 4920
2003 5901
2004 2832
2005 3890
2
2002 2005
2003 2005
3
1985 5782
1995 3048
2005 4890
2
1985 2005
2005 2015
*/
