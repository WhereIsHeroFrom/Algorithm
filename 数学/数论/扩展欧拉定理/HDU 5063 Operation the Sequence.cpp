#include <iostream>

using namespace std;
#define ll long long
#define MAXN 100010
const int MOD = (1e9 + 7);
int n, m;


int Oper[100010];
int TotalO;

int exp(ll a, ll b, ll c) {
    ll s = 1;
    while (b) {
        if (b & 1) {
            s = s * a % c;
        }
        b >>= 1;
        a *= a;
        a %= c;
    }
    return s;
}

int findAns(int index) {
    int cnt = 0;
    for (int i = TotalO - 1; i >= 0; --i) {
        if (Oper[i] == 3) {
            ++cnt;
        }
        else if (Oper[i] == 2) {
            index = n + 1 - index;
        }
        else if (Oper[i] == 1) {
            int isodd = (index <= (n + 1) / 2);
            if (isodd) {
                index = 2 * index - 1;
            }
            else {
                index = (index - (n + 1) / 2) * 2;
            }
        }
    }
    //printf("%d %d\n", index, cnt);
    if (cnt <= 30) {
        return exp(index, (1 << cnt), MOD);
    }
    else {
        return exp(index, exp(2, cnt, MOD - 1) + MOD - 1, MOD);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        TotalO = 0;
        for (int i = 0; i < m; ++i) {
            char cmd[10];
            int v;
            scanf("%s %d", cmd, &v);
            if (cmd[0] == 'O') {
                Oper[TotalO++] = v;
            }
            else {
                printf("%d\n", findAns(v));
            }

        }
    }

    return 0;
}

/*
121
10 100
O 1
O 2
O 3
O 3
O 1
O 2
Q 5
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
O 3
Q 7
*/