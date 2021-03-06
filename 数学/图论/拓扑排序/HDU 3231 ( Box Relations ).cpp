#include <iostream>
#include <vector>
using namespace std;

#define MAXN 2010

vector <int> vec[3][MAXN];
vector <int> ans[3];
int deg[3][MAXN];
int has[3][MAXN];
int box[3][MAXN][2];

void addEdge(int d, int u, int v) {
    deg[d][v] ++;
    vec[d][u].push_back(v);
}

int main() {
    int n, m;
    int i, j;
    int t = 1;
    while( scanf("%d %d", &n, &m) != EOF && (n+m) ) {
        memset( deg, 0, sizeof(deg) );
        memset( has, 0, sizeof(has) );
        
        // 拆点，每个box拆成两个点 
        // (i, i+n)
        for(i = 0; i < 3; i++) {
            for(j = 1; j <= 2*n; j++) {
                vec[i][j].clear();
                if(j <= n) {
                    addEdge(i, j, j+n);
                }
            }
        }
        
        while(m--) {
            char str[10];
            scanf("%s", str);
            int x, y;
            scanf("%d %d", &x, &y);
                     
            if( str[0] == 'I' ) {
                // 三个方向相交 
                for(i = 0; i < 3; i++) {
                    addEdge(i, y, x+n);
                    addEdge(i, x, y+n);
                }
            }else {
                int id;
                if(str[0] == 'X') {
                    id = 0;
                }else if(str[0] == 'Y') {
                    id = 1;
                }else if(str[0] == 'Z') {
                    id = 2;
                }
                addEdge(id, x+n, y);
            }
        }
        
        for(i = 0; i < 3; i++) {
            int cnt = 0;
            ans[i].clear();
            while(1) {
                int u = -1;
                for(j = 1; j <= 2*n; j++) {
                    if(!has[i][j] && !deg[i][j]) {
                        u = j;
                        break;
                    }
                }
                if(u == -1) break;
                
                cnt ++;
                has[i][u] = 1;
                ans[i].push_back( u );
                
                for(j = 0; j < vec[i][u].size(); j++) {
                    deg[i][  vec[i][u][j]  ] --;                    
                }
            }
            if(cnt != 2*n) break;
            
        }
        printf("Case %d: ", t++);
        if(i < 3) {
            printf("IMPOSSIBLE\n");
            
        }else {
            printf("POSSIBLE\n");
            
            for(i = 0; i < 3; i++) {
                int val = 0;
                for(j = 0; j < ans[i].size(); j++) {
                    if( ans[i][j] <= n ) {
                        box[i][ ans[i][j] ][0] = val;
                    }else {
                        box[i][ ans[i][j]-n ][1] = val;
                    }
                    val ++;
                }
            }
            for(i = 1; i <= n; i++) {
                printf("%d %d %d %d %d %d\n", box[0][i][0], box[1][i][0], box[2][i][0], 
                                              box[0][i][1], box[1][i][1], box[2][i][1]  );
            }
        }
        printf("\n");
    }
    return 0;
}

