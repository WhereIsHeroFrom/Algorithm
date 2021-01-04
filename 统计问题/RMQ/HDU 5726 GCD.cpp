#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

// RMQ 区间 GCD 询问

const int MAXM = 18;
const int MAXN = (1 << MAXM) + 1;

// typedef long long ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

ValueType GCD(ValueType a, ValueType b) {
    return !b ? a : GCD(b, a % b);
}

void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
    int i, j, k = 0;

    for (i = 1; i <= ALen; i++) {
        lg2K[i] = k - 1;
        if ((1 << k) == i) k++;
    }

    for (i = 0; i < MAXM; i++) {
        for (j = 1; j + (1 << i) - 1 <= ALen; j++) {
            if (i == 0) {
                f[i][j] = A[j];
            }
            else {
                f[i][j] = GCD(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
}

/*
设区间长度为2^k，则X表示的区间为[a, a + 2^k)，Y表示的区间为(b - 2^k, b]，
则需要满足一个条件就是X的右端点必须大于等于Y的左端点-1，即 a+2^k-1 >= b-2^k，
则2^(k+1) >= (b-a+1), 两边取对数（以2为底），得 k+1 >= lg(b-a+1)，则k >= lg(b-a+1) - 1。
k 只要需要取最小的满足条件的整数即可( lg(x)代表以2为底x的对数 )。
*/
ValueType RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
    if (a == b) {
        return A[a];
    }
    else if (a > b) {
        a = a^b, b = a^b, a = a^b;
    }
    int k = lg2K[b - a + 1];
    return GCD(f[k][a], f[k][b - (1 << k) + 1]);
}


int n;
int f[MAXM][MAXN];

int a[MAXN];

struct Cnt {
    int gcdval;
    long long cnt;

    Cnt() {}

    Cnt(int g, long long c) {
        gcdval = g;
        cnt = c;
    }

    bool operator < (const Cnt& o) {
        return gcdval < o.gcdval;
    }
};

vector <Cnt> vAns;
int vSize;

void preProcess() {

    vAns.clear();
    for (int i = 1; i <= n; ++i) {
        int from = i, to = i;

        while (to <= n) {
            int l = to, r = n;
            ValueType nowGCD = RMQ_Query(a, f, i, to);
            while (l <= r) {
                int mid = (l + r) >> 1;
                ValueType targetGCD = RMQ_Query(a, f, i, mid);
                if (targetGCD == nowGCD) {
                    to = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            if (to <= n) {
                vAns.push_back(Cnt(nowGCD, to - from + 1));
                from = to + 1;
                to = to + 1;
            }
        }
    }

    sort(vAns.begin(), vAns.end());

    int p = 0;

    for (int i = 1; i < vAns.size(); ++i) {
        if (vAns[i].gcdval == vAns[p].gcdval) {
            vAns[p].cnt += vAns[i].cnt;
        }
        else {
            vAns[++p] = vAns[i];
        }
    }
    vSize = p + 1;
}

int main() {
    int t, i, cas = 0;

    vAns.reserve(100000);

    scanf("%d", &t);

    while (t--) {

        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        RMQ_Init(a, n, f);

        preProcess();

        printf("Case #%d:\n", ++cas);
        int Q;
        scanf("%d", &Q);
        while (Q--) {

            int l, r;
            scanf("%d %d", &l, &r);
            int gcdv = RMQ_Query(a, f, l, r);
            long long ans = 0;
            int idxl = 0, idxr = vSize - 1;
            while (idxl <= idxr) {
                int mid = (idxl + idxr) >> 1;
                if (gcdv == vAns[mid].gcdval) {
                    ans = vAns[mid].cnt;
                    break;
                }
                else if (gcdv > vAns[mid].gcdval){
                    idxl = mid + 1;
                }
                else {
                    idxr = mid - 1;
                }
            }
            printf("%d %lld\n", gcdv, ans);
        }



    }

    return 0;
}

/*
10
20
1024 512 256 128 64 32 16 8 4 2 1 1 1 1 1 1 1 1 1 1

5
1 2 4 6 7

*/