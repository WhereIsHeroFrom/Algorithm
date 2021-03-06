/*************************************************************************************|
/**************************************最近公共祖先***********************************|
/*******************************************************************************V1.20*/
/*
模板简介：
7
1 6 13
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
边及权值，并且无向。

dfs生成的数组：
  E[i] = 1 6 3 5 3 6 1 4 2 4 7 4 1

E[i] 数组中对应点的深度：
Dep[i] = 0 1 2 3 2 1 0 1 2 1 2 1 0

R[i] 表示点i个点在E数组中第一次出现的位置
R[i] = 1 9 3 8 4 2 11

LCA( x, y ) = E[ RMQ( D, R[x], R[y] ) ];
*/
#include <iostream>
#include <cmath>
#include <vector >
using namespace std;

#define M 10010 
struct nextpoint {
    int nex;
    int val;
};
vector < nextpoint > vec[ M ];
int n;
int hash[ M ];
int E[ 2*M ], top;              // 开两倍的点
int R[ M ];                     // 当前点在E数组中第一次出现的位置，就是dfs时入点的位置
int Dep[ 2*M ];                 // 根节点到当前点的深度(作为RMQ的查询用)
int Dis[ M ];                   // 根节点到当前点的距离
int Min[ 2*M ][ 20 ];
int f[ 20 ];

struct LCA {
    void CreatGraph();
    void preCal();
    int Query( int s, int e ); // 返回s到e区间最小值的下标
    void dfs( int , int , int );
    void Test();
}Lca;


void LCA::preCal() {
    int i, j;
    f[0] = 1;
    for(i = 1; i < 20; i++)
        f[i] = f[i-1] * 2;

    for(i = 1; i < top; i++) {
        Min[i][0] = i;
    }

    for( j = 1; j < 20; j++) {
        for( i = 1; i < top; i++ ) {
            Min[i][j] = Min[i][j-1];

            if( i + f[j-1] < top ) {
                if( Dep[ Min[ i + f[j-1] ][ j-1 ] ] < Dep[ Min[i][j] ] )
                    Min[i][j] = Min[ i + f[j-1] ][ j-1 ];
            }
        }
    }
}

int LCA::Query( int x, int y ) {
    x = R[x];
    y = R[y];

    if( x > y ) {
        int temp = x;
        x = y;
        y = temp;
    }
    int k = log( y - x + 1.0 ) / log( 2.0 );
    return E[ Dep[ Min[x][k] ] < Dep[ Min[ y - f[k] + 1 ][k] ] ? Min[x][k] : Min[ y - f[k] + 1 ][k] ];
}

void LCA::dfs( int key, int sum, int depth ) {
    int i, size = vec[ key ].size();

    E[ top ] = key;
    Dep[ top ] = depth;

    R[ key ] = top;
    Dis[ key ] = sum;

    top ++;

    int flag = 0;
    for(i = 0; i < size; i++) {
        if( hash[ vec[key][i].nex ] )
            continue;
        hash[ vec[key][i].nex ] = 1;
        dfs( vec[key][i].nex, sum + vec[key][i].val, depth+1 );

        E[ top ] = key;
        Dep[ top ] = depth;
        top ++;
    }
}

void LCA::CreatGraph() {
    // 建图
    memset( hash, 0, sizeof( hash ));
    top = 1;
    hash[0] = 1;
    dfs( 0, 0, 0 );
}

void LCA::Test() {
    int i;
    printf("E[i] = ");
    for(i = 1; i < top; i++)
        printf("%d ", E[i]);
    puts("");

    printf("Dep[i] = ");
    for(i = 1; i < top; i++)
        printf("%d ", Dep[i]);
    puts("");

    printf("R[i] = ");
    for(i = 0; i <= n; i++)
        printf("%d ", R[i]);
    puts("");
}

int main() {
    int i;
    int m, c;
    nextpoint temp;
    int x, y, L;

    while( scanf( "%d %d %d", &n, &m, &c ) != EOF ) {
        for(i = 0; i <= n; i++) {
            vec[i].clear();
            if( i ) {
                temp.nex = i;
                temp.val = 1;
                vec[0].push_back( temp );
            }
        }
        while( m-- ) {
            scanf("%d %d %d", &x, &y, &L );
            temp.nex = y;
            temp.val = L;
            vec[x].push_back( temp );

            temp.nex = x;
            vec[y].push_back( temp );
        }

        Lca.CreatGraph();
        Lca.preCal();
        //Lca.Test();



        while( c-- ) {
            scanf("%d %d", &x, &y);
            int W = Lca.Query( x, y );
            if( W == 0 )
                printf("Not connected\n");
            else
                printf("%d\n", Dis[x] + Dis[y] - 2 * Dis[W] );
        }
    }
    return 0;
}
