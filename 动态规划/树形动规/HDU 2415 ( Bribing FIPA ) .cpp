/*
第二个 树形DP
和HDOJ 1561 类似，不过条件不一样，但是可以套用
树形DP + 01背包 的模式，只不过一些细节处理一下:
1. 最后答案求的是at least m，所以还要线性扫一遍最小值
2. 选择0个城市的最优值永远是0
3. 处理输入的时候看起来有点麻烦，其实真正写起来也不过如此了


*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define MAXN 210

char str[1000010];
int n, m;
map < string, int >  Map;
string buf;
char name[1000];
int T;
vector < int > vec[ MAXN ];
int dp[ MAXN ][ MAXN ];
int value[ MAXN ];
int in[ MAXN ];
int num[ MAXN ];

void dfs( int key ) {
    int size = vec[ key ].size();
    int i, j, k;


    num[ key ] = 1;

    for(i = 0; i < size; i++) {
        int q = vec[ key ][ i ];
        dfs( q );
        num[ key ] += num [ q ];
    }

    dp[ key ][ num[ key ] ] = value[ key ];

    for( i = 0; i < size; i++ ) {
        int q = vec[ key ][ i ];

        for(j = num[ key ]; j >= 0; j--) {
            
            for(k = 0; k <= j; k++) {
                if( dp[ key ][ j-k ] + dp[ q ][ k ] < dp[ key ][ j ])
                    dp[ key ][ j ] = dp[ key ][ j-k ] + dp[ q ][ k ];
            }
        }
    }

    return ;
}

int main() {

    int i, j;
    while( scanf("%s", str) != EOF ) {

        if( strcmp( str, "#" ) == 0 )
            break;
        Map.clear();
        sscanf(str, "%d", &n );
        memset(in, 0, sizeof( in ) );
        scanf("%d", &m);

        for(i = 0; i < MAXN; i++) {
            vec[i].clear();
            dp[i][0] = 0;
            for(j = 1; j < MAXN; j++) {
                dp[i][j] = 100000000;
            }
        }
        value[0] = 100000000;

        getchar(); T = 1;
        for(i = 0; i < n; i++) {
            gets(str);

            int top = 0;
            for(j = 0; str[j] != ' '; j++) {
                name[ top++ ] = str[j];
            }
            name[ top ] = '\0';
            buf = name;

            int u = Map[ buf ];

            if( !u ) {
                u = Map[ buf ] = T ++;
            }

            while( str[j] == ' ' )
                j ++;

            sscanf( &str[j], "%d", &value[u] );

            while( str[j] >= '0' && str[j] <= '9' || str[j] == ' ')
                j ++;

            while( str[j] ) {

                top = 0;
                while( str[j] != ' ' && str[j] != '\0' ) {
                    name[ top++ ] = str[ j++ ];
                }
                name[ top ] = '\0';
                buf = name;

                int v = Map[ buf ];

                if( !v ) {
                    v = Map[ buf ] = T ++;
                }
                in [ v ] ++;
                vec[ u ].push_back( v );

                while( str[j] == ' ' )
                    j ++;

                if( str[j] == '\0' )
                    break;
            }
        }


        for(i = 1; i <= n; i++) {
            if( !in[i] ) {
                vec[0].push_back( i );
            }
        }

        dfs(0);

        int Min = INT_MAX;
        for(i = m; i <= n; i++) {
            if( dp[0][i] < Min)
                Min = dp[0][i];
        }

        printf("%d\n", Min);

    }
}

