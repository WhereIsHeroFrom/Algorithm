#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1010;

int f[maxn][maxn];

int gcd(int a, int b) {
    return !b ? a : gcd(b, a%b);    
}

int dfs(int x, int y) {
    int &val = f[x][y];
    if (val != -1) {
        return val;
    }
    int coprime = (gcd(x,y) == 1 ? 1 : 0);
    if(x == 1 && y == 1) {
        val = 1;
    }else if(x == 1) {
        val = coprime + dfs(x, y-1);
    }else if(y == 1) {
        val = coprime + dfs(x-1, y);
    } else {
        val = coprime + max( dfs(x-1,y), dfs(x, y-1) );
    }
    return val;
}

void init() {
    memset(f, -1, sizeof(f));
    f[1000][1000] = dfs(1000, 1000);
}

int main() {
    init();
    int t;
    int a, b;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", f[a][b]);
    }
    
    return 0;
} 
