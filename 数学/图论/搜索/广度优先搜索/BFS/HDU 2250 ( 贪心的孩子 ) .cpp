#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    double val;
    int next;
};

int m;
int n;
double money;
map < int, int > Map;
vector < edge > vec[ 20010 ];
double hash[ 20010 ];
int at[ 20010 ];
double chos[ 20010 ];
int T;
queue < edge > q;

void bfs() {

    int i;
    edge temp, tt;
    temp.next = 0;
    temp.val = money;
    hash[ 0 ] = temp.val;

    while( !q.empty() )
        q.pop();

    q.push( temp );

    while( !q.empty() ) {
        temp = q.front();
        q.pop();

        int size = vec[ temp.next ].size();
        for(i = 0; i < size; i++) {
            edge p = vec[ temp.next ][ i ];
            tt.val = p.val * temp.val;
            tt.next = p.next;

            if( tt.val > hash[ tt.next ] )  {
                hash[ tt.next ] = tt.val;
                q.push( tt );
            }
        }
    }
}

int main() {
    int i;
    int a, b, u, v;
    double ty;

    while ( scanf("%lf %d", &money, &m) != EOF ) {
        Map.clear();
        T = 1;
        for(i = 0; i <= 20009; i++) {
            vec[i].clear();
            hash[i] = 0;
            at[i] = 0;
        }

        while( m-- ) {
            scanf("%d %d %lf", &a, &b, &ty);

            edge temp;
            if( a == 0 ) {
                u = 0;
            }else {
                u = Map[ a ];
                if( !u ) {
                    u = Map[ a ] = T ++;
                }
            }

            if( b == 0 ) {
                v = 0;
            }else {
                v = Map[ b ];
                if( !v ) {
                    v = Map[ b ] = T ++;
                }
            }

            if( v == 0 ) {
                at[ u ] = 1;
                chos[ u ] = ty;
            }else {

                temp.next = v;
                temp.val = ty;
                vec[ u ].push_back( temp );
            }
        }

        bfs();

        for(i = 1; i < T; i++) {
            if( at[i] ) {
                if( chos[i] * hash[i] > hash[0] )
                    hash[0] = chos[i] * hash[i];
            }
        }

        printf("%.2lf\n", hash[0] );
    }

    return 0;
}


