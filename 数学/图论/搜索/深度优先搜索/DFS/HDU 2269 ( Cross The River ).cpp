#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, t, g;

struct point {
    char name[30];
    int ID;
}p[ 100 ];

int find( char *name ) {
    int i;
    for(i = 0; i < n; i++) {
        if( strcmp( p[i].name, name ) == 0 )
            return i;
    }
    return 20;
}

struct elem {
    int status;
    int step;
}temp, tt;

int map[ 12 ][ 12 ];
int dig[ 3000 ];    // 统计到2048每个数字1的个数
int hash[ 3000 ];
int line[ 1000 ];
int stack[2][ 12 ], top[2];
queue < elem > q;
int vip[ 12 ];

void dfs( int depth, int nowstate, int index, int mod ) {
    int i, j;

    top[0] = top[1] = 0;

    //printf("lala : %d\n", nowstate);


    int flag = 0;
    for(j = 0; j < g; j++) {

        if(j && line[j] == line[j-1] )
            continue;

        if( dig[ line[j] ] == 1 )
            continue;
        for(i = 0; i < n; i++) {
            int chang = ( (1<<i) & nowstate );
            chang = (chang ? 1 : 0);

            if( chang != mod && ( (1<<i) & line[j] ) )
                break;
        }

        if( i == n ) {
            flag = 1;
            break;
        }
    }

    if( !flag ) {
        if( hash[ nowstate ] < 3 ) {
            hash[ nowstate ] ++;
            tt.status = nowstate;
            tt.step = temp.step + 1;
            q.push( tt );
        }
    }


    if( depth == t )
        return ;
    for(i = index; i < n; i++) {
        int chang = ( (1<<i) & nowstate );
        chang = ( chang ? 1 : 0 );
        if( chang == (mod ^ 1) )
            continue;

        if( mod )
            dfs( depth+1, (nowstate ^ (1<<i) ), i+1, mod);
        else
            dfs( depth+1, (nowstate | (1<<i) ), i+1, mod);
    }
}

char beh[ 30000 ];
int main() {
    int i, j;
    char fro[200][ 30 ];

    for(i = 0; i < 3000; i++) {
        int num = i;
        dig[i] = 0;
        while( num ) {
            if( num & 1 )
                dig [i] ++;
            num /= 2;
        }
    }



    while( scanf("%d %d %d", &n, &m, &t) != EOF ) {
        
        for(i = 0; i < n; i++) {
            scanf("%s", p[i].name);
            p[i].ID = i;
        }

        getchar();
        memset(hash, 0, sizeof(hash));
        memset( map, 0, sizeof(map) );
        g = m;
        while( m-- ) {
            gets( beh );
            int all = 0, ty = 0;
            for(i = 0; beh[i]; i++) {
                if( beh[i] == ' ' ){
                    fro[ all ][ ty ] = '\0';
                    all ++;
                    ty = 0;
                }else
                    fro[ all ][ ty ++ ] = beh[i];
            }
            
            if( ty ){
                fro[ all ][ ty ] = '\0';
                all ++;
                ty = 0;
            }
            
            line[m] = 0;
            for(i = 0; i < all; i++) {
                line[ m ] |= (1<<find( fro[i] ));
                //puts( fro[i] );
            }
        }

        sort( line, line + g);

        temp.status = 0;
        temp.step = 0;

        hash[ 0 ] = 1;
        while (!q.empty()) {
            q.pop();
        }

        q.push( temp );

        int flag = -1;
        while( !q.empty() ) {
            temp = q.front();
            q.pop();
            if( temp.status == (1<<n)-1 ) {
                flag = temp.step;
                break;
            }
            dfs(0, temp.status, 0, (temp.step&1) );
        }

        printf("%d\n", flag);
    }
}

