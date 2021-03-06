#include <iostream>
using namespace std;


int n, TT, M;
char str[ 1000 ];
char map[ 500 ][ 500 ];

char hua[9][10] = {
    "....@....",
    "..@~@~@..",
    "@~@\\@/@~@",
    "\\@|@|@|@/",
    ".\\\\\\|///.",
    "..\\\\|//..",
    "...\\|/...",
    "...=&=...",
    ".../|\\..."
};

struct point {
    int Time;
    int L;    
    int a[ 200 ];
}p[ 200 ];

int start, end;
int hash[ 1000 ];
int T[ 10000 ];


void Draw() {
    int i, j, k;
    int W, H;
    int dx, dy;
    int cx, cy;
    int now, Cnt;
    
    W = 9 + (n-1) * 12 + 2;
    H = 9 + (n-1) *  3 + 2;
    
    for( i = 0; i < H; i ++ ) {
        for( j = 0; j < W; j ++ ) {
            map[i][j] = ' ';
        }
        map[i][W] = '\0';
    }
    
    map[0][0] = map[0][W-1] = '+';
    map[H-1][0] = map[H-1][W-1] = '+';
    
    for( i = 1; i < W - 1; i ++ ) {
        map[H-1][i] = map[0][i] = '-';
    }
    for( i = 1; i < H-1; i ++ ) {
        map[i][0] = map[i][W-1] = '|';
    }
    
    
    dx = 5 + ( n-1 ) * 6;
    dy = 1;
    
    for( i = 1; i <= n*(n+1)/2; i ++ ) {
        if( hash[i] ) {
            now = i;
            Cnt = 1;
            while( now > Cnt ) {
                now -= Cnt;
                Cnt ++;
            }
            
            cx = dx - (Cnt-1) * 6;
            cx = cx + 12 * ( now - 1 );
            cy = dy + (Cnt-1) * 3;
            
            cx -= 4;
            
            for( j = 0; j < 9; j ++ ){
                for( k = 0; k < 9; k ++ ) {
                    if(hua[j][k] != '.' )
                    map[ cy+j ][ cx+k ] = hua[j][k];
                }
            }
        }
    }
    
    for( i = 0; i < H; i ++ )
        puts( map[i] );
}

int main() {
    int i, j;
    int a, b;
    int u, flag;

    start = 60 * 8;
    end = 60 * 23;
    
    while( scanf( "%d %d %d", &n, &TT, &M ) != EOF )  {
        for( i = 1; i <= n*(n+1)/2; i ++ ) {
            hash[i] = 1;
        }
        memset( T, -1, sizeof( T ) );
        
         for( i = 0; i < M; i ++ ) {
            scanf("%s %d", str, &p[i].L );

            sscanf(str, "%d:%d", &a, &b );
            p[i].Time = a * 60 + b;
            T[ p[i].Time ] = i;

            for( j = 0; j < p[i].L; j ++ ) {
                scanf("%d", &p[i].a[j] );
            }
        }
        for( i = 0; i < 10000; i ++ ) {
            if( i >= start && i < end ) {
                if( (i - start) % TT == 0 ) {
                    for( j = 1; j <= n*(n+1)/2; j ++ ){
                        if( !hash[j] ) {
                            hash[j] = 1;
                            break;
                        }
                    }
                }
            }
            
            if( T[i] != -1 ) {
                if( i < start || i > end ) {
                    printf("Not yet open for business\n");
                }else {
                    u = T[i];
                    flag = 0;
                    for( j = 0; j < p[u].L; j++ ) {
                        if( hash[ p[u].a[j] ] ) {
                            flag ++;
                            hash[ p[u].a[j] ] = 0;
                        }
                    }
                    
                    if( flag ) {
                        printf("You bought %d beams of rose\n", flag );
                    }else
                        printf("What a pity!\n");
                }
            }
        }
        Draw();
    }
    return 0;
}

/*
3 60 2
8:00 2
2 3
23:00 3
1 2 3

*/

