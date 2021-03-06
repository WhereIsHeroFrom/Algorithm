#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define ll __int64

#define maxn 10010
#define BLACK 100000000
#define COMPLEX -1 

vector < int > vec[ maxn ];
int HasV[ maxn ], cas;
int color[ maxn*20 ];

// 询问区间[l, r]中是否有前面的元素
void Query( int p, int l, int r, int a, int b, int index ) {
    
    if( color[p] != COMPLEX ) {
        if( color[p] != BLACK ) {
            if( HasV[ color[p] ] != cas ) {
                HasV[ color[p] ] = cas;
                vec[ color[p] ].push_back ( index );
            }
        }
        return ;
    }

    int mid = ( a + b ) / 2;

    if( r <= mid ) {
        Query( 2*p, l, r, a, mid, index );
    }else if( l > mid ) {
        Query( 2*p+1, l, r, mid+1, b, index );
    }else {
        Query( 2*p, l, mid, a, mid, index );
        Query( 2*p+1, mid+1, r, mid+1, b, index );
    }
}
// 用当前线段来覆盖区间[l, r]
void Insert( int p, int l, int r, int a, int b, int index ) {
    
    if( a == l && r == b ) {
        color[ p ] = index;
        return ;
    }

    if( color[p] != COMPLEX ) {
        color[2*p] = color[2*p+1] = color[p];
        color[p] = COMPLEX;
    }

    int mid = ( a + b ) / 2;

    if( r <= mid ) {
        Insert( 2*p, l, r, a, mid, index );
    }else if( l > mid ) {
        Insert( 2*p+1, l, r, mid+1, b, index );
    }else {
        Insert( 2*p, l, mid, a, mid, index );
        Insert( 2*p+1, mid+1, r, mid+1, b, index );
    }
}

struct Intval {
    int l, r, h;
    int index;
}I[ maxn ];

struct Pos {
    int index;
    int pos;
}H[2];

int cmp( Intval a, Intval b ) {
    return a.h > b.h;
}

int ls[ 10*maxn ], top;
int A[ 10 * maxn ], T;

int Binary( int key ) {
    int low = 1;
    int high = T;
    int mid;

    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( A[ mid ] == key )
            return mid;
        if( key > A[ mid ] ) {
            low = mid + 1;
        }else
            high = mid - 1;
    }
}

#define mod 600007

int hash[ mod + 1 ];
int key[2][ mod + 1 ];
int D;

int HASH( ll index, ll val ) {
    int s = ( index * (ll)(T+1) + val ) % mod;

    while( 1 ) {
        if( hash[s] == -1 ) {
            hash[s] = D++;
            key[0][s] = index;
            key[1][s] = val;
            return hash[s];
        }

        if( key[0][s] == index && key[1][s] == val )
            return hash[s];
        s ++;

        if( s == mod )
            s = 0;
    }
}


struct point {
    int nex;
    ll val;
    point() {
    }
    point( int _n, int _v ) {
        nex = _n;
        val = _v;
    }
}temp, tt;

ll Dis[ 200000 ];
queue < point > q;
vector < point > Ga[ 100000 ];
vector < int > Ha[ maxn ];

int m;
int start, end;

ll bfs( int start, int end ) {
    while( !q.empty()) 
        q.pop();
    int i;

    memset( Dis, -1, sizeof( Dis ) );
    q.push( point( start, 0 ) );
    Dis[ start ] = 0;

    while( !q.empty() ) {
        temp = q.front();
        q.pop();

        for( i = Ga[temp.nex].size()-1; i >= 0; i-- ) {
            tt.nex = Ga[ temp.nex ][i].nex;
            tt.val = Ga[ temp.nex ][i].val + temp.val;

            if( Dis[ tt.nex ] == -1 || tt.val < Dis[ tt.nex ] ) {
                Dis[ tt.nex ] = tt.val;
                q.push( tt );
            }
        }
    }
    return Dis[ end ];
}

int main() {
    int t;
    int i, j;


    scanf("%d", &t);

    while( t-- ) {
        scanf("%d", &m );
        top = 0;
        
        memset( hash, -1, sizeof( hash ) );
        for( i = 0; i < maxn*20; i ++ )
            color[i] = BLACK;

        for( i = 0; i < 2; i++ ) {
            scanf("%d %d %d", &I[i].h, &I[i].l, &I[i].r );
            I[i].index = i;
            scanf("%d", &H[i].pos );
            H[i].index = i;

            ls[ top++ ] = I[i].l;
            ls[ top++ ] = I[i].l - 1;
            ls[ top++ ] = I[i].l + 1;

            ls[ top++ ] = I[i].r;
            ls[ top++ ] = I[i].r - 1;
            ls[ top++ ] = I[i].r + 1;

            ls[ top++ ] = H[i].pos;
        }
        for( i = 2; i < m; i ++ ) {
            scanf("%d %d %d", &I[i].h, &I[i].l, &I[i].r );
            I[i].index = i;

            ls[ top++ ] = I[i].l;
            ls[ top++ ] = I[i].l - 1;
            ls[ top++ ] = I[i].l + 1;

            ls[ top++ ] = I[i].r;
            ls[ top++ ] = I[i].r - 1;
            ls[ top++ ] = I[i].r + 1;
        }
        sort( ls, ls + top );
        sort( I, I + m, cmp );

        T = 0;
        A[ ++T ] = ls[0];
        for( i = 1; i < top; i ++ ) {
            if( ls[i] != ls[i-1] )
                A[ ++T ] = ls[i];
        }

        for( i = 0; i < 2; i ++ ) {
            H[i].pos = Binary( H[i].pos );
        }
        for( i = 0; i < m; i++ ) {
            I[i].l = Binary( I[i].l );
            I[i].r = Binary( I[i].r );
        }

        for( i = 0; i < m; i ++ ) {
            vec[i].clear();
            Ha[i].clear();
        }

        for( i = 0; i < m; i ++ ) {
            cas ++;
            if( i ) {
                Query( 1, I[i].l, I[i].r, 1, T, i );
            }
            Insert(1, I[i].l, I[i].l, 1, T, i );
            Insert(1, I[i].r, I[i].r, 1, T, i );
            if( I[i].l+1 <= I[i].r-1 )
                Insert( 1, I[i].l+1, I[i].r-1, 1, T, BLACK );
        }

        for( i = 0; i < 100000; i ++ )
            Ga[i].clear();
        D = 0;

        for( i = 0; i < m; i++ ) {

            Ha[i].push_back( I[i].l );
            Ha[i].push_back( I[i].r );

            if( H[0].index == I[i].index ) {
                Ha[i].push_back( H[0].pos );
                int u = HASH( i, H[0].pos );
                end = u;
            }
            if( H[1].index == I[i].index ) {
                Ha[i].push_back( H[1].pos );
                int u = HASH( i, H[1].pos );
                start = u;
            }

            for( j = 0; j < vec[i].size(); j ++ ) {
                int to = vec[i][j];
                if( I[i].h - I[to].h == 1 ) { 
                    if( I[to].l <= I[i].l && I[i].l <= I[to].r ) {
                        int from = HASH( i, I[i].l );
                        int u = HASH( to, I[i].l );
                        Ha[to].push_back( I[i].l );
                        Ga[ from ].push_back( point( u, 1 ) );
                        Ga[ u ].push_back( point( from, 1 ) );
                    }

                    if( I[to].l <= I[i].r && I[i].r <= I[to].r ) {
                        int from = HASH( i, I[i].r );
                        int u = HASH( to, I[i].r );
                        Ha[to].push_back( I[i].r );            
                        Ga[ from ].push_back( point( u, 1 ) );
                        Ga[ u ].push_back( point( from, 1 ) );
                    }
                }
            }
        }

        for( i = 0; i < m; i ++ ) {
            sort( Ha[i].begin(), Ha[i].end() );
            for( j = 1; j < Ha[i].size(); j ++ ) {
                int from = Ha[i][j-1];
                int to = Ha[i][j];
                int val = A[to] - A[from];

                //if( from == to ) continue;

                from = HASH( i, from );
                to = HASH( i, to );
                Ga[ from ].push_back( point( to, val ) );
                Ga[ to ].push_back( point( from, val ) );
            }
        }
        printf("%I64d\n", bfs( start, end ) );
    }
    return 0;
}

/*
34
6
100 10 40 12
99  5 12 12
98  30 50
93  3 100
3   2 1000
1   10000 1000000
*/
