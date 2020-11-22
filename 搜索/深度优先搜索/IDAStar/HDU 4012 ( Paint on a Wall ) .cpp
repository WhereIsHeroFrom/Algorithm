#include <iostream>

using namespace std;

#define MAXN 9


int encode(char c) {
    return c - 'A' + 1;
}

char decode(int v) {
    return v + 'A' - 1;
}

// 0 匹配任何数 
bool same(int a, int b) {
    return (a == b || a == 0 || b == 0);
}

bool same(int a, int b, int c) {
    return same(a, b) && same(b, c) && same(a, c);
}

struct Wall {
    int n;
    char data[2][MAXN];
    void print() {
        int i, j;
        for(i = 0; i < 2; i++) {
            for(j = 0; j < n; j++) {
                printf("%c", decode(data[i][j]));
            }
            puts("");
        }   
        puts("");
    }
    
    void fromData(char str[2][MAXN], int _n) {
        n = _n;
        int i, j;
        for(i = 0; i < 2; i++) {
            for(j = 0; j < n; j++) {
                data[i][j] = encode( str[i][j] );
            }
        }
    }
    
    void coverByZero(int sx, int sy, int ex, int ey) {
        int i, j;
        for(i = sx; i <= ex; i++) {
            for(j = sy; j <= ey; j++) {
                data[i][j] = 0;
            }
        }
    }
    
    bool end() {
        int i, j;
        for(i = 0; i < 2; i++) {
            for(j = 0; j < n; j++) {
                if(data[i][j]) return false;
            }
        }
        return true;
    }
    
    int remainColor() {
        bool col[27];
        int i, j, c = 0;
        memset(col, 0, sizeof(col));
        for(i = 0; i < 2; i++) {
            for(j = 0; j < n; j++) {
                col[ data[i][j] ] = 1;
            }
        }
        for(i = 1; i <= 26; i++) {
            if(col[i]) c++;
        }
        return c;
    }
    
    int h() {
        return remainColor();
    }
    
};


char str[2][MAXN];
int n;
Wall path[1000];

bool dfs(Wall now, int depth, int maxDepth) {
    

    if( now.end() ) {
        /*int i;
        for(i = 0; i < depth; i++) {
            path[i].print();
        }*/
        return true;
    }
    if( now.h() > maxDepth - depth ) {
        return false;
    }
    
    int i, j, k;
    Wall next;
    
    // 枚举高度为2的情况 
    for(i = 0; i < n; i++) {
        char v1 = now.data[0][i], v2 = now.data[1][i];
        if( (v1||v2) && same(v1, v2) ) {
            
            char v = v1?v1:v2;
            for(j = i; j < n; j++) {
                if( !same(now.data[0][j], now.data[1][j], v) ) {
                    break;
                }
            }
            j--;
            next = now;
            next.coverByZero(0, i, 1, j);
            //path[depth] = next;
            if( dfs(next, depth+1, maxDepth) ) {
                return true;
            }
        } 
    } 
    
    // 枚举高度为1的情况
    for(i = 0; i < 2; i++) {
        for(j = 0; j < n; j++) {
            char v = now.data[i][j];
            if(!v) continue;
            
            for(k = j; k < n; k++) {
                if( !same(now.data[i][k], v) ) {
                    break;
                }
            }
            k--;
            next = now;
            next.coverByZero(i, j, i, k);
            //path[depth] = next;
            if( dfs(next, depth+1, maxDepth) ) {
                return true;
            } 
        }
    } 

    return false;    
}

int main() {
    
    int i, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < 2; i++) {
            scanf("%s", str[i]);
        }
        Wall s;
        s.fromData(str, n);
        
        for(i = 0; ; i++) {
            if( dfs(s, 0, i) ) {
                printf("Case #%d: %d\n", ++cases, i);
                break;
            }
        }
    }    
    return 0;
}

/*
10
3
ABA
CBC
3
BAA
CCB
3
BBB
BAB
8
ABCDEFGH
HIJKDCBH
8
AAAAAAAA
AAAAAAAA
8
BBAABBAA
AABBAABB
8
ABCDEFGA
BBBDBBBB
1
D
F
8
EABAAAAG
DAAAAGGG

8
AABABCDG
GFKRODSZ

2
AB
DD
*/
