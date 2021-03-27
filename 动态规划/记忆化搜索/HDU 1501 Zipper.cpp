#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1010;
#define ll long long
int n;
int f[maxn][maxn];
char a[maxn], b[maxn], c[maxn];


void init() {
    memset(f, -1, sizeof(f));
}

int dfs(int apos, int bpos) {
    int cpos = apos + bpos;
    if (apos == 0 && bpos == 0) {
        return 1;
    }
    int &val = f[apos][bpos];
    if (val != -1) {
        return val;
    }

    val = 0;

    if (bpos != 0 && c[cpos] == b[bpos]) {
        val |= dfs(apos, bpos - 1);
        if (val) return true;
    }
    if (apos != 0 && c[cpos] == a[apos]) {
        val |= dfs(apos - 1, bpos);
    }

    return val;
}


bool solve() {
    int alen = strlen(a + 1);
    int blen = strlen(b + 1);
    int clen = strlen(c + 1);

    if (alen + blen != clen) {
        return false;
    }
    return dfs(alen, blen);
}

int main() {
    int t, cas = 0;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%s %s %s", a + 1, b + 1, c + 1);
        printf("Data set %d: %s\n", ++cas, solve() ? "yes" : "no");

    }
    return 0;
}