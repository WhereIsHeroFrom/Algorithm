#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct point {
    int next;
    int time;
    friend bool operator < (point a, point b) {
        return a.time > b.time;
    }
};

int t;
int pri[201];
int n;
int hash[201];
int map[201][201];
int M[201][201];

vector < point > vec[201];
priority_queue < point > q;
int Dijkstra_Heap(int u, int k) {
    
    int i;
    point temp, tt;
    temp.next = u;
    temp.time = 0;
    memset(hash, -1, sizeof(hash));
    hash[ temp.next ] = 0;
    q.push( temp );

    while(!q.empty()) {
        temp = q.top();
        q.pop();

        int size = vec[ temp.next ].size();

        for(i = 0; i < size; i++) {
            tt.next = vec[temp.next][i].next;
            tt.time = temp.time + vec[temp.next][i].time;

            if(pri[ tt.next ] > k) {

                if(tt.time < hash[ tt.next ] || hash[ tt.next ] == -1) { 
                    hash[ tt.next ] = tt.time;
                }

                continue;
            }

            if(tt.time < hash[ tt.next ] || hash[ tt.next ] == -1) { 
                hash[ tt.next ] = tt.time;
                q.push( tt );
            }
        }
    }
    return -1;
}


int main() {
    int i, j;
    int m;
    int x, y, z, k;
    scanf("%d", &t);

    while(t--) {
        scanf("%d %d", &n, &m);
        int Max = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &pri[i]);
            vec[i].clear();
            for(j = 0; j < n; j++) {
                if(i == j)
                    map[i][j] = 0;
                else
                    map[i][j] = 10000000;
            }
        }

        point temp;
        while(m--) {
            scanf("%d %d %d", &x, &y, &temp.time);
            temp.next = y;
            vec[x].push_back( temp );
            temp.next = x;
            vec[y].push_back( temp );
            map[x][y] = map[y][x] = temp.time;
        }
        for(i = 0; i < n; i++) {
            Dijkstra_Heap(i, pri[i]);
            for(j = 0; j < n; j++) {
                M[i][j] = hash[j];
            }
        }

        int Q;
        scanf("%d", &Q);

        while(Q --) {

            scanf("%d %d %d", &x, &y, &k);
            int Min = map[x][y];

            for(i = 0; i < n; i++) {
                if(i == x || i == y)
                    continue;
                if(pri[i] <= k && M[i][x] >= 0 && M[i][y] >= 0 && M[i][x] + M[i][y] < Min)
                    Min = M[i][x] + M[i][y];
            }

            if(Min == 10000000)
                printf("-1\n");
            else
                printf("%d\n", Min);
        }
        puts("");
    }
    return 0;
}

