#include <iostream>

using namespace std;

char letters[3][10] = {
    "awyz",
    "bwxz",
    "cxyz",
};
bool isLetter(int idx, char c) {
    int i;
    for(i = 0; i < 4; ++i) {
        if(c == letters[idx][i]) return true;
    }
    return false;
}

#define MAXN 1010
int n, m;
char mat[MAXN][MAXN];

bool IsLetter[MAXN][MAXN];
int U[MAXN][MAXN];
int L[MAXN], R[MAXN];

int getMaxMatrix(int idx) {
    int i, j;
    int Max = 0;
    for(i = 1; i <= n; ++i) {
        for(j = 1; j <= m; ++j) {
            IsLetter[i][j] = isLetter(idx,mat[i][j]);
            if(IsLetter[i][j]) {
                U[i][j] = U[i-1][j] + 1;
            }else {
                U[i][j] = 0;
            }
        } 
        U[i][0] = -1;
        for(j = 1; j <= m; ++j) {
            int l = j-1;
            while(U[i][l] >= U[i][j]) {
                l = L[l];
            }
            L[j] = l;
        }
        U[i][m+1] = -1;
        for(j = m; j >= 1; --j) {
            int r = j+1;
            while(U[i][r] >= U[i][j]) {
                r = R[r];
            }
            R[j] = r;

            int v = U[i][j] * (R[j] - L[j] - 1);
            if(v > Max) Max = v;
        }
    }
    return Max;
}

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF) {
        for(i = 1; i <= n; ++i) {
            scanf("%s", &mat[i][1]);
        }
        int Max = 0;
        for(i = 0; i < 3; ++i) {
            int v = getMaxMatrix(i);
            if(v > Max) Max = v;
        }
        printf("%d\n", Max);
    }
    return 0;
}
/*
5 7
aaaaaaa
abaabaa
bbaabaa
bbaabbb
bbbabbb
*/
