#include <iostream>

using namespace std;

int n, m, p;
int mat[5][5];
int mPos;
int Max;

bool row_attack(int r, int c) {
    int i;
    for(i = c-1; i >= 0; i--) {
        if(mat[r][i]) {
            break;
        }
    }
    if(i == -1) return false;

    for(i--; i >= 0; i--) {
        if(mat[r][i]) {
            break;
        } 
    }
    if(i == -1 || mat[r][i] == -1) return false;
    
    return true;
}

bool col_attack(int r, int c) {
    int i;
    for(i = r-1; i >= 0; i--) {
        if(mat[i][c]) {
            break;
        }
    }
    if(i == -1) return false;

    for(i--; i >= 0; i--) {
        if(mat[i][c]) {
            break;
        } 
    }
    if(i == -1 || mat[i][c] == -1) return false;
    
    return true;
}

bool check(int r, int c) {
    
    if( mat[r][c] ) {
        return false;
    }
    
    if( row_attack(r, c) ) {
        return false;
    }
    
    if( col_attack(r, c) ) {
        return false;
    }
    
    return true;
}

void dfs(int idx, int depth) {
    if(depth > Max) {
        Max = depth;
    }
    for(int i = idx; i < mPos; i++) {
        int r = i / m;
        int c = i % m;
        
        if( check(r, c) ) {
            mat[r][c] = 1;
            dfs(i+1, depth+1);
            mat[r][c] = 0;
        }
    }
}

int main() {
    int i;
    while( scanf("%d %d %d", &n, &m, &p) != EOF ) {
        memset(mat, 0, sizeof(mat));
        while(p--) {
            int x, y;
            scanf("%d %d", &x, &y);
            mat[x][y] = -1;
        }
        Max = 0;
        mPos = n * m;
        dfs(0, 0);
        printf("%d\n", Max);
    }
    return 0;
}
