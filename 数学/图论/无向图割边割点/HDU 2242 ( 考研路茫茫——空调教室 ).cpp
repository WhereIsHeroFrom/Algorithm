#include <iostream>
#include <map>
#define MAXN 100010
using namespace std;

map < int, int > Map;

struct list {
    list *next;
    int ID;
};

int n, m;
int value[ MAXN ];

list data[ 1000000 ];
list *vec[ MAXN ];
list *Bri[ MAXN ];
int Ance[ MAXN ];
int Dep[ MAXN ];
int Color[ MAXN ];
int father[ MAXN ];
bool Cut[ MAXN ];
int num[ MAXN ];
#define G 0  // Grey    正在访问
#define B 1  // Black   访问完毕
#define W 2  // White   未曾访问
int root, T;

/*******************求无向图割边割点**********************
* list vec[i] 表示原的邻接表                             * 
* list Bri[i] 保存割边                                   *
* bool Cut[i] 保存割点                                   *
* int Ance[i] 保存和i或i的子孙邻接的最高辈分的祖先的深度 *
* int Dep[i] 保存i点所在的深度                           *
* int Color[i] 保存当前结点访问情况                      *
* int father[i] 保存i的父亲结点的编号                    *
* int num[i] 缩点后每个点所在的新块的编号                *
*********************************************************/

int Min ( int a, int b ) {
    return a < b ? a : b;
}

void BridgeCut( int key, int depth ) {

    int son = 0;
    Dep[ key ] = depth;
    Color[ key ] = G;
    Ance[ key ] = depth;

    list *p, *q;

    for( p = vec[ key ]->next; p ; p = p->next ) {

        int next = p->ID;

        if( next != father[ key ] && Color[ next ] == G) {
            Ance[ key ] = Min( Ance[ key ], Dep[ next ] );
        }

        if( Color[ next ] == W ) {

            father[ next ] = key;
            BridgeCut( next, depth + 1);
            son ++; Ance[ key ] = Min( Ance[ key ], Ance[ next ] );
            // 判割点
            if( key == root ) {
                if( son > 1 ) {
                    Cut[ key ] = true;
                }
            }else {
                if( Ance[ next ] >= Dep[ key ] ) {
                    Cut[ key ] = true;
                }
            }

            // 判割边
            if( Ance[ next ] > Dep[ key ] ) {

                //重边非割边
                if( Map[ next * 100000 + key ] > 1 )
                    continue;
                q = &data[ T++ ];
                q->ID = next;
                q->next = Bri[ key ]->next;
                Bri[ key ]->next = q;
                
                q = &data[ T++ ];
                q->ID = key;
                q->next = Bri[ next ]->next;
                Bri[ next ]->next = q;
            }
        }
    }

    Color[ key ] = B;
}


void CreateGraph() {

    int i, x, y;
    T = 0;

    for(i = 1; i <= n; i++)
        scanf("%d", &value[i]);

    for(i = 1; i <= n; i++) {

        Bri[i] = &data[ T++ ];
        Bri[i]->ID = i;
        Bri[i]->next = NULL;

        vec[i] = &data[ T++ ];
        vec[i]->ID = i;
        vec[i]->next = NULL;

        Ance[i] = INT_MAX;

        Cut[i] = false;
        Color[ i ] = W;
    }

    list *p;
    while( m-- ) {
        scanf("%d %d", &x, &y);

        x ++;
        y ++;

        Map[ x * 100000 + y ] ++;
        Map[ y * 100000 + x ] ++;

        p = &data[ T++ ];
        p->next = vec[x]->next;
        p->ID = y;
        vec[x]->next = p;

        p = &data[ T++ ];
        p->next = vec[y]->next;
        p->ID = x;
        vec[y]->next = p;
    }
}

/*
割边割点输出，以及缩块后的图的邻接表
*/

void Print() {
    list *p;
    int i;
    for(i = 1; i <= n; i++) {
        printf("%d: ", i);
        for(p = Bri[i]->next; p; p = p->next) {
            printf("%d ", p->ID);
        }
        puts("");
    }
    for(i = 1; i <= n; i++) {
        if( Cut[i] )
            printf("point : %d\n", i);
    }
}



/*以下是树形DP的过程*/


bool IsBridge(int u, int v) {
    list *p;
    for( p = Bri[u]->next; p ; p = p->next ) {
        if( p->ID == v )
            return 1;
    }
    return 0;
}

int F;

// 分块 
void dfs( int key ) {
    list *p;
    num[ key ] = F;
    for(p = vec[ key ]->next; p ; p = p->next ) {
        if( Color[ p->ID ] == W  && !IsBridge(key, p->ID) ) {
            Color[ p->ID ] = B;
            dfs( p->ID );
        }
    }
}



void FloodFill() {
    int i;
    for(i = 1; i <= n; i++)
        Color[i] = W;
    F = 1;
    for(i = 1; i <= n; i++) {
        if( Color[i] == W ) {
            Color[i] = B;
            dfs(i);
            F ++;
        }
    }
}

int AllVal[ MAXN ];
int M, zong;
list *New[ MAXN ];
int hash[ MAXN ];


// TreeDp
void Search( int key ) {
    list *p;
    int son = 0;

    for( p = New[ key ]->next; p; p = p->next) {
        
        int q = p->ID;
        if( hash[ q ] )
            continue;
        son ++;
        hash[ q ] = 1;
        Search(q);
        AllVal[ key ] += (__int64)AllVal[ q ];
        __int64 a = zong - AllVal[ q ];
        __int64 b = AllVal[ q ];
        a -= b;
        if( a < 0)
            a = -a;
        if( a < M )
            M = a;
    }    
}


void TreeDp() {

    int i;
    M = 0;
    memset( AllVal, 0, sizeof(AllVal) );
    for(i = 1; i <= n; i++) {
        AllVal[ num[i] ] += value[i];
        M += value[i];
    }
    zong = M;
    F --;
    for(i = 1; i <= F; i++) {
        New[i] = &data[ T++ ];
        New[i]->ID = i;
        New[i]->next = NULL;
    }

    list *p, *q;

    for(i = 1; i <= n; i++) {
        for(p = Bri[i]->next; p; p = p->next) {
            q = &data[ T++ ];
            q->ID = num[ p->ID ];
            q->next = New[ num[i] ]->next;
            New[ num[i] ]->next = q;
        }
    }

    memset( hash, 0, sizeof(hash) );
    hash[1] = 1;
    Search(1);
}

int main() {

    int i;
    int t = 1;

    while( scanf("%d %d", &n, &m) != EOF && (n || m) ) {
        Map.clear();
        CreateGraph();
        root = 1;
        father[ root ] = 0;
        BridgeCut( root, 0 );
        FloodFill();
        //Print();
        TreeDp();
        if( M == zong )
            printf("impossible\n");
        else
            printf("%d\n", M);
    }
    return 0;
}

