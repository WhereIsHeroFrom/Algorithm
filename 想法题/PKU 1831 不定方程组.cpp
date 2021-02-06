#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
#define maxn 70000

int stack[maxn];
int ans[maxn], all;

int hasans[maxn];
vector <int> gans[maxn];

ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a%b);
}

bool dfs(int nowS, int s, int pre, ll u, ll d) {
    if (s < 0) {
        return false;
    }
    if (u > d * s) {    //  u/d  > s 
        return false;
    }

    if (!s && !u) {
        for (int i = 0; i < all; ++i) {
            gans[nowS].push_back(stack[i]);
        }
        return true;
    }

    for (int i = pre; i <= s; ++i) {
        ll newu = u * i - d;
        ll newd = d * i;
        if (newu < 0) continue;
        ll g = gcd(newu, newd);
        newu /= g;
        newd /= g;

        stack[all++] = i;
        if (dfs(nowS, s - i, i, newu, newd)) {
            --all;
            return true;
        }
        --all;
    }

    return false;
}

void caclans(int s) {
    if (hasans[s] == -1) hasans[s] = dfs(s, s, 1, 1, 1) ? 1 : 0;
}

void processans(int s, int tp, int parm1, int parm2, int parm3 = 0) {
    vector <int> tmp;
    if (tp == 0) {
        for (int i = 0; i < gans[parm1].size(); ++i) {
            tmp.push_back(gans[parm1][i] << 1);
        }
        for (int i = 0; i < gans[parm2].size(); ++i) {
            tmp.push_back(gans[parm2][i] << 1);
        }
    }
    else {
        for (int i = 0; i < gans[parm1].size(); ++i) {
            tmp.push_back(gans[parm1][i] * 6);
        }
        for (int i = 0; i < gans[parm2].size(); ++i) {
            tmp.push_back(gans[parm2][i] * 3);
        }
        for (int i = 0; i < gans[parm3].size(); ++i) {
            tmp.push_back(gans[parm3][i] * 2);
        }
    }

    sort(tmp.begin(), tmp.end());

    for (int i = 0; i < tmp.size(); ++i) {
        gans[s].push_back(tmp[i]);
    }
}

bool solve(int s) {
    if (hasans[s] != -1) {
        return (hasans[s] == 1);
    }

    if (s < 100) {
        caclans(s);
        return hasans[s] == 1;
    }
    else {
        if (s % 2 == 0) {
            int s2 = (s >> 1);
            int s4 = (s2 >> 1);
            for (int A = 1; A <= s4; ++A) {
                int B = s2 - A;
                solve(A);
                solve(B);
                if (hasans[A] && hasans[B]) {
                    processans(s, 0, A, B);
                    return hasans[s] = 1;
                }
            }
        }

        for (int A = 1; 6 * A + 5 <= s; ++A) {
            solve(A);
            for (int B = 1; 6 * A + 3 * B + 2 <= s; ++B) {
                int C2 = s - (6 * A + 3 * B);
                if (C2 % 2 == 0) {
                    int C = (C2 >> 1);
                    solve(B);
                    solve(C);
                    if (hasans[A] && hasans[B] && hasans[C]) {
                        processans(s, 1, A, B, C);
                        return hasans[s] = 1;
                    }

                }
            }
        }

    }


    return hasans[s] = 0;
}

int main() {
    memset(hasans, -1, sizeof(hasans));

    int i, t, s;
    scanf("%d", &t);
    while (t--) {
        all = 0;
        scanf("%d", &s);
        if (!solve(s)) {
            printf("-1\n");
        }
        else {
            printf("%d", gans[s].size());
            for (i = 0; i < gans[s].size(); i++) {
                printf(" %d", gans[s][i]);
            }
            puts("");
        }
    }
    return 0;
}