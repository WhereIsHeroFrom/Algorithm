#include <iostream>
#include <queue>
using namespace std;

struct point {
    int h;
    int x; 
    int y;
    friend bool operator < (point a, point b) {
        return a.h > b.h;
    }
};

int t;
int map[501][501];
int hash[501][501];
int sum;

priority_queue < point > Q;
queue < point > q;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;
int i, j;

int FloodFill() {
    int i, sum = 0;
    point temp, tt;

    while(!Q.empty()) {
        point buf = Q.top();
        Q.pop();


        while(!q.empty())
            q.pop();
        q.push( buf );
        
        while(!q.empty()) {
            temp = q.front();
            q.pop();

            for(i = 0; i < 4; i++) {
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];
                if(tt.x < 0 || tt.y < 0 || tt.x >= n || tt.y >= m)
                    continue;
                if(hash[ tt.x ][ tt.y ])
                    continue;
                hash[ tt.x ][ tt.y ] = 1;
                if(map[ tt.x ][ tt.y ] >= temp.h) {
                    tt.h = map[ tt.x ][ tt.y ];
                    Q.push( tt );
                }else {
                    tt.h = temp.h;
                    sum += temp.h - map[ tt.x ][ tt.y ];
                    q.push(tt); 
                }
            }
        }
    }
    return sum;
}

int main() {
    scanf("%d", &t);

    while(t--) {

        point temp;
        scanf("%d %d", &n, &m);    
        memset(hash, 0, sizeof(hash));
        while( !q.empty() ) q.pop();
        sum = 0;

        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%d", &map[i][j]);
                if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    temp.x = i;
                    temp.y = j;
                    temp.h = map[i][j];
                    hash[ i ][ j ] = 1;
                    Q.push( temp );
                }
            }
        }
        printf("%d\n", FloodFill());
    }
}

