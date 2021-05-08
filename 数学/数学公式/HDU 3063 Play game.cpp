#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#pragma warning(disable : 4996)

char ch[1000];
int inv[5];
const int mod = 9999;
int sqr(int x) {
    return x * x;
}

int main() {
    int t;
    int n, m;
    for (int i = 2; i <= 4; i += 2) {
        for (int j = 1; ; ++j) {
            if (j * i % mod == 1) {
                inv[i] = j; break;
            }
        }
    }

    while (scanf("%s", ch) != EOF) {
        int s = 0;
        for (int i = 0; ch[i]; ++i) {
            s = (s * 10 + ch[i] - '0') % mod;
        }
        s = sqr(s * (s + 1) % mod) % mod * inv[4] + s * (s + 1) % mod * (2 * s + 1) % mod * inv[2] + s * (s + 1);
        s %= mod;
        printf("%d\n", s);
    }
    return 0;
}