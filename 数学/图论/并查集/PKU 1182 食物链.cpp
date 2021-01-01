/*
并查集 : 012树
*/

#include <iostream>

using namespace std;


const int MAXN = 300010;
int fset[MAXN], rk[MAXN];
int n;

void init_set() {
    for (int i = 1; i < MAXN; ++i) {
        fset[i] = i;
        rk[i] = 0;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : find_set(fset[x]);
}

int find_depth(int x) {
    return (fset[x] == x) ? 0 : 1 + find_depth(fset[x]);
}

int add_set(int x) {
    fset[x] = ++n;
    rk[fset[x]] = rk[x] + 1;
    return fset[x];
}

bool union_set(int x, int y, int op) {
    int fx = find_set(x), fy = find_set(y);
    int dx = find_depth(x), dy = find_depth(y);
    int mod = ((dy - dx) % 3 + 3) % 3;

    if (fx == fy) {
        if (op == 1) {
            // x 和 y 是同类，那么深度相减 = 0 
            return (mod == 0);
        }
        else if (op == 2) {
            // x 吃 y 
            return (mod == 1);
        }
    }

    int Delta, X;

    if (rk[fx] < rk[fy]) {
        Delta = (op == 1 ? 0 : -1);
        X = ((dy - dx + Delta) % 3 + 3) % 3;
        if (X == 0) {
            X = 3;
        }
        for (int i = 0; i < X - 1; ++i) {
            fx = add_set(fx);
        }
        fset[fx] = fy;
        if (rk[fx] + 1 > rk[fy]){
            rk[fy] = rk[fx] + 1;
        }
    }
    else {
        Delta = (op == 1 ? 0 : 1);
        X = ((dx - dy + Delta) % 3 + 3) % 3;
        if (X == 0) {
            X = 3;
        }
        for (int i = 0; i < X - 1; ++i) {
            fy = add_set(fy);
        }
        fset[fy] = fx;
        if (rk[fy] + 1 > rk[fx]){
            rk[fx] = rk[fy] + 1;
        }
    }


    return true;
}


int main() {
    int m, x, a, b;

    scanf("%d %d", &n, &m);
    init_set();
    int ans = 0;
    int N = n;
    while (m--) {
        scanf("%d %d %d", &x, &a, &b);
        if (a > N || b > N) ++ans;
        else if (!union_set(a, b, x)) ++ans;
    }
    printf("%d\n", ans);

    return 0;
}

