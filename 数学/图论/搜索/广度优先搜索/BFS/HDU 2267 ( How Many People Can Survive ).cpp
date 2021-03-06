#include <iostream>
#include <queue>
using namespace std;

int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

struct point {
    int x;
    int y;
}temp, tt;

int n, m;
char map[300][300];
int hash[300][300];

queue < point > q;
int l, r;
int i, j, k;

int main() {

    while(scanf("%d %d", &n, &m) != EOF) {
        
        for(i = 1; i <= n; i++) {
            scanf("%s", &map[i][1]);
        }
        memset(hash, 0, sizeof(hash));
        while(!q.empty())
            q.pop();


        temp.x = temp.y = 0;
        q.push( temp );

        hash[0][0] = 1;
        while(!q.empty()) {
            temp = q.front();
            q.pop();
            for(i = 0; i < 4; i++) {
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];

                if(tt.x < 0 || tt.y < 0 || tt.x > n + 1 || tt.y > m + 1)
                    continue;

                if(!hash[tt.x][tt.y] && map[tt.x][tt.y] != '#') {
                    hash[ tt.x ][ tt.y ] = 1;
                    q.push( tt );
                }
            }
        }

        int l, r, o, v;

        l = r = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                if(!hash[i][j]) {
                    hash[i][j] = 1;
                    temp.x = i;
                    temp.y = j;
                    o = v = 0;

                    if( map[i][j] == 'o')
                        o ++;
                    if(map[i][j] == 'v')
                        v ++;

                    while(!q.empty())
                        q.pop();

                    q.push( temp );

                    while(!q.empty()) {
                        temp = q.front();
                        q.pop();
                        for(k = 0; k < 4; k++) {
                            tt.x = temp.x + dir[k][0];
                            tt.y = temp.y + dir[k][1];

                            if(tt.x < 1 || tt.x > n || tt.y < 1 || tt.y > m)
                                continue;

                            if(hash[ tt.x ][ tt.y ] || map[ tt.x][tt.y] == '#')
                                continue;

                            if(map[tt.x][tt.y] == 'o')
                                o++;
                            if(map[tt.x][tt.y] == 'v')
                                v ++;

                            hash[ tt.x ][ tt.y ] = 1;
                            q.push( tt );

                        }
                    }

                    if(v > o)
                        r += v;
                    if(o > v)
                        l += o;
                }
            }
        }

        printf("%d %d\n", l, r);
    }
}
