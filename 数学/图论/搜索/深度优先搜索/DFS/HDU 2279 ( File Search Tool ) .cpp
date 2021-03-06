#include <iostream>

using namespace std;

int n, m;
struct point {
    char str[30];
    int len;
}p[10010];

char str[10];
int len;

int dfs(int u, int pa, int fi) {
    int i;
    if(pa == len && fi == p[u].len) {
        return 1;
    }

    if( str[ pa ] != '*' && str[ pa ] != '?' ) {
        if(str[ pa ] == p[u].str[fi]) {
            return dfs(u, pa + 1, fi + 1);
        }else
            return 0;
    }else if( str[ pa ] == '?') {
        return dfs(u, pa + 1, fi + 1);
    }else {
        for(i = fi; i <= p[u].len; i++) {
            if( dfs(u, pa+1, i) )
                return 1;
        }
        return 0;
    }
}

int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        for(i = 0; i < n; i++) {
            scanf("%s", p[i].str);
            p[i].len = strlen( p[i].str );
        }

        for(i = 0; i < m; i++) {
            scanf("%s", str);
            len = strlen( str );

            int coun = 0;
            for(j = 0; j < n; j++) {
                if( dfs(j, 0, 0) )
                    coun ++;
            }

            if( !coun )
                puts("Not match");
            else
                printf("%d\n", coun);
        }
    }
}
