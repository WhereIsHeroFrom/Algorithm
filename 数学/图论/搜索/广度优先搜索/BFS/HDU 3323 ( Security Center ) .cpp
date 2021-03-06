#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int t;

vector < int > hasw[ 20010 ], hasnw[ 20010 ];
int n, m, c;
int wyh;
int att[ 20010 ], natt[ 20010 ];
queue < int > q;


void bfs() {
    int i;
    while( !q.empty() ) {
        int now = q.front();
        q.pop();
        if( natt[ now ] ) continue;
        natt[ now ] = 1;
        for( i = hasnw[now].size()-1; i >= 0; i-- ) {
            q.push( hasnw[now][i] );
        }
    }
}

void bfs( int start ) {
    while( !q.empty() )
        q.pop();

    q.push( start );
    int i;
    while( !q.empty() ) {
        int now = q.front();
        q.pop();
        if( att[ now ] ) continue;
        att[ now ] = 1;
        for( i = hasw[now].size()-1; i >= 0; i-- ) {
            q.push( hasw[now][i] );
        }
    }
}

int main() {
    int i;

    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %d %d", &n, &m, &c );
        for ( i = 0; i < n; i ++ ) {
            hasw[i].clear();
            hasnw[i].clear();
            natt[i] = att[i] = 0;
        }
        while( !q.empty() )
            q.pop();

        scanf( "%d", &wyh );
        for( i = 0; i < c; i ++ ) {
            int x;
            scanf("%d", &x );
            q.push( x );
        }

        while( m-- ) {
            int x, y;
            scanf("%d %d", &x, &y );
            hasw[x].push_back(y);
            hasw[y].push_back(x);
            if( x != wyh && y != wyh ) {
                hasnw[x].push_back(y);
                hasnw[y].push_back(x);
            }
        }
        bfs();
        bfs( wyh );

        int cnt = 0;
        for( i = 0; i < n; i ++ ) {
            if( i != wyh ) {
                if( att[i] && !natt[i] )
                    cnt ++;
            } 
        }
        printf("%d\n", cnt );
    }
    return 0;

}
