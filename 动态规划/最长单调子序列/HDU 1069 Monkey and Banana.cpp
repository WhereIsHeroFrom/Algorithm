#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long
#define maxn 1010

int a[maxn];
ll dp[maxn];

struct Triple {
    int x, y, z;

    Triple(){}
    Triple(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {

    }

    bool operator < (const Triple& t) const {
        if (x == t.x) {
            return y < t.y;
        }
        return x < t.x;
    }
}Tot[maxn];
int TotSize;

int T[6][3] = {
    { 0, 1, 2 },
    { 0, 2, 1 },
    { 1, 0, 2 },
    { 1, 2, 0 },
    { 2, 0, 1 },
    { 2, 1, 0 }
};

int main() {
    int n;
    int cas = 0;
    while (scanf("%d", &n) != EOF && n) {
        TotSize = 0;
        for (int i = 0; i < n; ++i) {
            int a[3];
            scanf("%d %d %d", &a[0], &a[1], &a[2]);
            for (int j = 0; j < 6; ++j) {
                Tot[TotSize++] = Triple(a[T[j][0]], a[T[j][1]], a[T[j][2]]);
            }
        }
        sort(Tot, Tot + TotSize);
        dp[0] = Tot[0].z;

        for (int i = 1; i < TotSize; ++i) {
            ll val = 0;
            for (int j = 0; j < i; ++j) {
                if (Tot[j].x < Tot[i].x && Tot[j].y < Tot[i].y) {
                    val = max(val, dp[j]);
                }
            }
            dp[i] = val + Tot[i].z;
        }
        ll maxv = 0;
        for (int i = 0; i < TotSize; ++i) {
            maxv = max(maxv, dp[i]);
        }
        printf("Case %d: maximum height = %lld\n", ++cas, maxv);

    }
    return 0;
}