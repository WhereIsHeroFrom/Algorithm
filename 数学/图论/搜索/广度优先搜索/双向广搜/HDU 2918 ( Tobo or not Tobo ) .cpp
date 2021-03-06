#include <iostream>
#include <map>
using namespace std;

struct point {
    int map[3][3];
    int step;
    int state;
}temp[2], tt[2];

point q[2][ 300000 ];
int front[2], rear[2];
map < int , int > Map[2];
int Step;

int State( point tp ) {
    int i, j;
    int buf = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            buf = buf * 9 + tp.map[i][j];
        }
    }
    return buf;
}

char str[ 1000 ];

int main() {

    int i, j;
    int cas = 1;

    while( scanf("%s", str) != EOF ) {

        if( strcmp( str, "0000000000" ) == 0 )
            break;

        Step = str[0] - '0';
        
        for(i = 0; i < 2; i++) {
            front[i] = rear[i] = 0;
            Map[i].clear();
        }

        int top = 1;
        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                temp[0].map[i][j] = str[ top++ ] - '1';
                temp[1].map[i][j] = i * 3 + j;
            }
        }

        for(i = 0; i < 2; i++) {
            temp[i].step = 0;
            temp[i].state = State( temp[i] );
            Map[i][ temp[i].state ] = 1;
            q[i][ rear[i] ++ ] = temp[i];
        }

        int mod = 0;
        int ans = -1;

        while( front[ 0 ] < rear[ 0 ] || front[1] < rear[1] ) {

            while( front[ mod ] < rear[ mod ] ) {

                temp[ mod ] = q[ mod ][ front[ mod ] ++ ];

                int u = Map[ mod^1 ][ temp[ mod ].state ];
                if( u ) {
                    ans = u + temp[ mod ].step - 1;
                    break;
                }

                for(i = 0; i < 2; i++) {
                    for(j = 0; j < 2; j++) {

                        if( temp[ mod ].step <= Step ) {
                            tt[ mod ] = temp[ mod ];
                            tt[ mod ].step = temp[ mod ].step + 1;

                            tt[ mod ].map[i][j] = temp[ mod ].map[i][j+1];
                            tt[ mod ].map[i][j+1] = temp[ mod ].map[i+1][j+1];
                            tt[ mod ].map[i+1][j+1] = temp[ mod ].map[i+1][j];
                            tt[ mod ].map[i+1][j] = temp[ mod ].map[i][j];
                            tt[ mod ].state = State( tt[ mod ] );

                            if( !Map[ mod ][ tt[ mod ].state ] ) {
                                Map[ mod ][ tt[ mod ].state ] = tt[ mod ].step + 1;
                                q[ mod ][ rear[ mod ] ++ ] = tt[ mod ];
                            }

                            tt[ mod ].map[i][j] = temp[ mod ].map[i+1][j];
                            tt[ mod ].map[i+1][j] = temp[ mod ].map[i+1][j+1];
                            tt[ mod ].map[i+1][j+1] = temp[ mod ].map[i][j+1];
                            tt[ mod ].map[i][j+1] = temp[ mod ].map[i][j];
                            tt[ mod ].state = State( tt[ mod ] );

                            if( !Map[ mod ][ tt[ mod ].state ] ) {
                                Map[ mod ][ tt[ mod ].state ] = tt[ mod ].step + 1;
                                q[ mod ][ rear[ mod ] ++ ] = tt[ mod ];
                            }
                        }
                    }
                }

                if( front[ mod ] < rear[ mod ] ) {
                    if( q[ mod ][ front[ mod ] ].step != temp[ mod ].step ) {
                        break;
                    }
                }
            }

            if( ans != -1 )
                break;

            mod ^= 1;
        }

        if( ans > Step )
            ans = -1;

        printf("%d. %d\n", cas++, ans);
    }
    return 0;
}
