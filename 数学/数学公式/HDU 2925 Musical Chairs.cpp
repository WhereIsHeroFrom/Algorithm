#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#pragma warning(disable : 4996)

int main() {
    int t;
    int n, m;
    while (scanf("%d %d", &m, &n) != EOF && (n || m)) {
        int s = 0;
        for (int i = 1; i <= m; ++i) {
            s = (s + n) % i;
        }
        printf("%d %d %d\n", m, n, s + 1);
    }
    return 0;
}