#include <iostream>
#include <queue>
using namespace std;

struct point {
    int lx;
    int ly;
    int rx;
    int ry;
    int step;
    bool friend operator < (point a, point b) {
        return a.step > b.step;
    }
}temp, tt;

int flag;
char map[100][100];
int hash[62][62][7][7];
priority_queue < point > q;

int stack[10000], top;
int n, m;

int bfs(point temp) {

    int i, j;
    while(!q.empty())
        q.pop();
    q.push( temp );

    while(!q.empty()) {
        temp = q.top();
        q.pop();


        if(temp.lx < 500 && map[temp.lx][temp.ly] == 'T' ||
            temp.rx < 500 && map[temp.rx][temp.ry] == 'T') {
            if(flag == -1 || temp.step < flag)
                flag = temp.step;
            return 0;
        }
        //???????????

        if(temp.lx < 500 && temp.ly < 500) {
            tt.lx = temp.lx;
            tt.ly = temp.ly;
            for(i = 3; i >= 1; i--) {
                for(j = -3+i; j <= 3-i; j++) {
                    tt.ry = temp.ly + i;
                    tt.rx = temp.lx + j;

                    if(tt.rx < 0 || tt.ry < 0 || tt.rx >= n || tt.ry >= m)
                        continue;
                    if(map[tt.rx][tt.ry] >= '1' && map[tt.rx][tt.ry] <= '9') {
                        tt.step = temp.step + map[tt.rx][tt.ry] - '0';
                        if(hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ] == -1 || tt.step < hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ]) {
                            hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ] = tt.step;
                            q.push( tt );
                        }
                    }
            

                    if(map[tt.rx][tt.ry] == 'T' || map[tt.rx][tt.ry] == 'S' ) {
                        tt.step = temp.step;
                        if(hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ] == -1 || tt.step < hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ]) {
                            hash[ tt.lx ][ tt.ly ][ i + 3 ][ j + 3 ] = tt.step;
                            q.push( tt );
                        }
                    }
                }
            }
        }

        //???????????
        if(temp.rx < 500 && temp.ry < 500) {
            tt.rx = temp.rx;
            tt.ry = temp.ry;
            for(i = 3; i >= 1; i--) {
                for(j = -3+i; j <= 3-i; j++) {
                    tt.ly = temp.ry - i;
                    tt.lx = temp.rx + j;
                    if(tt.lx < 0 || tt.ly < 0 || tt.lx >= n || tt.ly >= m)
                        continue;
                    if(map[tt.lx][tt.ly] >= '1' && map[tt.lx][tt.ly] <= '9') {
                        tt.step = temp.step + map[tt.lx][tt.ly] - '0';
                        if(hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ] == -1 || tt.step < hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ]) {
                            hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ] = tt.step;
                            q.push( tt );
                        }
                    }

                    if(map[tt.lx][tt.ly] == 'T' || map[tt.lx][tt.ly] == 'S') {
                        tt.step = temp.step;
                        if(hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ] == -1 || tt.step < hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ]) {
                            hash[ tt.lx ][ tt.ly ][ i + 3 ][ -j + 3 ] = tt.step;
                            q.push( tt );
                        }
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    int i, j;

    while(scanf("%d %d", &m, &n) != EOF) {
        if(!m && !n)
            break;

        getchar();
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%c", &map[i][j]);
                getchar();
            }
        }

        top = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(map[i][j] == 'S') {
                    stack[ top++ ] = i * 10000 + j;
                }
            }
        }

        flag = -1;
        memset(hash, -1, sizeof(hash));

        for(i = 0; i < top; i++) {

                temp.lx = stack[i] / 10000;
                temp.ly = stack[i] % 10000;

                temp.rx = 610;
                temp.ry = 610;
                temp.step = 0;

                bfs(temp);
                
                temp.rx = stack[i] / 10000;
                temp.ry = stack[i] % 10000;

                temp.lx = 610;
                temp.ly = 610;
                temp.step = 0;

                bfs(temp);
        }        
        printf("%d\n", flag);

    }
    return 0;
}

