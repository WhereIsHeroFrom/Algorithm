#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct point {
    int nex;
    int Val;

    bool friend operator < ( point a, point b ) {
        return a.Val > b.Val;
    }
}temp, tt;

vector < point > vec[ 2010 ];
priority_queue < point > q;
int hash[ 2010 ];
int ty[ 2010 ];

struct RT {
    int l;
    int r;
    int w;
}rt[ 2010 ];

int n, m;

int main() {

    int t;
    int i, j;

    scanf("%d", &t);
    while( t-- ) {
        scanf("%d %d", &n, &m);

        for(i = 1; i <= n; i++) {
            vec[i].clear();
        }

        for(i = 1; i <= n; i++) {
            scanf("%d %d %d", &rt[i].l, &rt[i].r, &rt[i].w );
        }

        for(i = 1; i <= n; i++) {
            for(j = i+1; j <= n; j++) {
                if( rt[i].r >= rt[j].l ) {
                    temp.nex = j;
                    temp.Val = rt[j].w;
                    vec[ i ].push_back( temp );

                }
            }
        }
        memset( ty, 0, sizeof( ty ) );
        memset( hash, -1, sizeof( hash ) );
        int T = m;

        temp.nex = 1;
        temp.Val = rt[1].w;


        while( !q.empty() )
            q.pop();
        q.push( temp );

        hash[ temp.nex ] = temp.Val;

        while( !q.empty() ) {
            temp = q.top();
            q.pop();

            int size = vec[ temp.nex ].size();
            for(i = 0; i < size; i++) {
                point to = vec[ temp.nex ][ i ];
                tt.nex = to.nex;
                tt.Val = temp.Val + to.Val;

                if( hash[ tt.nex ] == -1 || tt.Val < hash[ tt.nex ] ) {
                    hash[ tt.nex ] = tt.Val;
                    q.push( tt );
                }
            }
        }

        while( m-- ) {
            int o;
            scanf("%d", &o);
            printf("%d\n", hash[o] );
        }

    }
    return 0;
}
