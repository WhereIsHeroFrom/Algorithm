#include <iostream>
#include <queue>
using namespace std;

int hash[ 110 ];
struct point {
    int mac;
    int att;
}p[ 110 ];

int n, top, t, Q;
int dp[101][101][101];

struct node {
    int mac;
    int bosshp;
    int herohp;
    int step;
}temp, tt;

queue < node > q;
int BFS() {
    memset( dp, -1, sizeof( dp ) );
    while(!q.empty())q.pop();
    temp.bosshp = 100;
    temp.herohp = 100;
    temp.mac = 100;
    temp.step = 0;
    dp[ temp.bosshp ][ temp.herohp ][ temp.mac ] = 0;
    q.push( temp );

    int i;
    while( !q.empty() ) {
        temp = q.front();
        q.pop();

        for( i = 0; i < n; i ++ ) {
            if( temp.mac >= p[i].mac ) {
                tt.bosshp = temp.bosshp - p[i].att;
                tt.mac = temp.mac - p[i].mac;
                tt.step = temp.step + 1;
                if( tt.bosshp <= 0 ) {
                    return tt.step;
                }
                tt.herohp = temp.herohp - Q;
                if( tt.herohp <= 0 )
                    continue;
                tt.mac += t;
                if( tt.mac > 100 )
                    tt.mac = 100;
                if( dp[tt.bosshp][tt.herohp][tt.step] == -1 ) {
                    dp[tt.bosshp][tt.herohp][tt.step] = tt.step;
                    q.push(tt);
                }
            }
            
        }
    }
    return -1;
}

int main() {
    int i, j;
    while( scanf( "%d %d %d", &n, &t, &Q ) != EOF && (n||t||Q) ) {
        memset( hash, 0, sizeof( hash ) );
        for( i = 0; i < n; i ++ ) {
            scanf("%d %d", &p[i].mac, &p[i].att );
        }
        p[n].att = 1;
        p[n].mac = 0;
        n ++;
        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < n; j ++ ) {
                if( i == j ) {
                    continue;
                }
                if( p[i].mac >= p[j].mac && p[i].att <= p[j].att ) {
                    hash[i] = 1;
                    break;
                }
            }
        }

        top = 0;
        for( i = 0; i < n; i ++ ) {
            if( !hash[i] ) {
                p[ top++ ] = p[i];
            }
        }
        n = top;
        int ans = BFS();
        if( ans == -1 )
            puts("My god");
        else
            printf("%d\n", ans );
    }
    return 0;
}

