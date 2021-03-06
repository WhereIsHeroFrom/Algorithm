#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define MAXC 260
#define MAXN 90
#define inf -12345678

char mat[5];
char tar[MAXN];

int dp[MAXC][51][51];
int has[MAXC];
char to[MAXC][MAXC];

struct Char {
    char u, v;
    Char() {
        
    }
    Char(char _u, char _v) {
        u = _u;
        v = _v;
    }
};

vector <Char> edges[MAXC];

int Max(int a, int b) {
    return a > b ? a : b;
} 

int dfs(char c, int l, int r) {
    if(l == r) {
        if(c == tar[l]) {
            return 0;
        }
        return inf;
    }
    
    int &v = dp[c][l][r];
    if(v != -1) {
        return v;
    }
    v = inf;
    int i, j;
    for(i = 0; i < edges[c].size(); ++i) {
        Char ch = edges[c][i];
        for(j = l; j < r; ++j) {
            int ef = dfs(ch.u, l, j);
            if(ef != inf) {
                int fg = dfs(ch.v, j+1, r);
                if(fg != inf) {
                    int max = Max(ef, fg);
                    if( max+1 < v || v == inf) {
                        v = max + 1;
                    }
                }
            }
        }
    }
    return v;
} 
int main() {
    int n;
    int i, j;
    while(scanf("%d", &n) != EOF && n) {
        memset(dp, -1, sizeof(dp));
        memset(has, 0, sizeof(has));
        for(i = 0; i < MAXC; ++i) {
            edges[i].clear();
        }
        
        for(i = 0; i < n; ++i) {
            scanf("%s", mat);
            has[mat[0]] = 1;
            edges[mat[0]].push_back(Char(mat[1], mat[2]));
        }
        
        scanf("%s", tar);
        
        int len = strlen(tar);
        int step = -1;
        for(char c = 'A'; c <= 'T'; ++c) {
            if(!has[c]) {
                continue;
            }
            int v = dfs(c, 0, len-1);
            if(v == inf) continue;
            
            if(v < step || step == -1) {
                step = v;
            }
        }
        if(len==1) step = 0;
        
        printf("%d\n", step);
    }
    return 0;
}

/*
2
AAB
CAB
ABB

2
CAB
AAB
ABB
*/
