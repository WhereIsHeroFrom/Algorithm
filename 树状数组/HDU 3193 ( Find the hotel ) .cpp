#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 10010
int c[MAXN];

struct Hotel {
    int price, dist;
    void read() {
        scanf("%d %d", &price, &dist);
    }

    bool operator < (const Hotel& other) {
        if(price == other.price) {
            return dist < other.dist;
        }
        return price < other.price;
    }

    void Print() {
        printf("%d %d\n", price, dist);
    }
}H[MAXN];
int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x) {
    while(x < MAXN) {
        ++c[x];
        x += lowbit(x);
    }
}

bool hasVal(int x) {
    while(x) {
        if(c[x]) return true;
        x ^= lowbit(x);
    }
    return false;
}

int ans[MAXN];

int main() {
    int i, j;
    while(scanf("%d", &n) != EOF) {
        memset(c, 0, sizeof(c));
        for(i = 0; i < n; ++i) {
            H[i].read();
        }    
        sort(H, H+n);

        ans[0] = 0;
        // 插入的时候，dist的值需要+1，因为可能为0，树状数组下标从1开始记
        for(i = 0; i < n; ++i) {
            if (!hasVal(H[i].dist)) {
                ans[ ++ans[0] ] = i;
            }
            if( i < n-1 && H[i+1].price != H[i].price) {
                j = i;
                while(j >= 0 && H[j].price == H[i].price) {
                    add(H[j].dist + 1);
                    --j;
                }
            }
        }

        printf("%d\n", ans[0]);
        for(i = 1; i <= ans[0]; ++i) {
            H[ans[i]].Print();
        }
    }
    return 0;
}

/*
3
1 2
1 5
1 4

3
3 10
1 10
5 10

4
3 10
4 10
4 10
0 10
*/
