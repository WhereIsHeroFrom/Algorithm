#include <iostream>
#include <map>
#include <string>
using namespace std;
#define IF 0
#define NOT 1

map < string, int > Map[2], ma;

char str[200][200];

struct point {
    int if_or_not;
    int fen;
    int time;
    char str[200];
}p[ 200 ];

string buf;
int zty;
int n;
int Min, Max;

int main() {
    int t;

    int x, y, z;
    int i, j;
    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);
        getchar();

        for(i = 0; i < n; i++) {
            gets(str[i]);

            int pos = 0;
            while(str[i][ pos ] == ' ')
                pos ++;

            sscanf( &str[i][pos], "%d", &x);

            while( !(str[i][ pos ] >= 'A' && str[i][ pos ] <= 'Z') )
                pos ++;

            if(str[i][ pos ] == 'S') {
                p[i].if_or_not = -2;
                p[i].time = x;
                p[i].fen = x;
                zty = x;
            }else {
                p[i].time = x;
                while( !(str[i][ pos ] >= '0' && str[i][ pos ] <= '9') )
                    pos ++;

                sscanf( &str[i][ pos ], "%d", &y);
                p[i].fen = y;

                while( (str[i][ pos ] >= '0' && str[i][ pos ] <= '9') && str[i][ pos ] )
                    pos ++;

                if(str[i][ pos ] == '\0') {
                    p[i].if_or_not = -1;
                }else {
                    for(j = pos; str[i][ j ]; j++) {
                        if(str[i][j] == 'N')
                            break;
                    }

                    if(str[i][j] == 'N') {
                        pos = j;
                        while( !(str[i][ pos ] >= 'a' && str[i][ pos ] <= 'z') )
                            pos ++;
                        p[i].if_or_not = NOT;
                    }else {
                        while( !(str[i][ pos ] >= 'a' && str[i][ pos ] <= 'z') )
                            pos ++;    
                        p[i].if_or_not = IF;
                    }    
                    sscanf(&str[i][pos], "%s", p[i].str);
                }
            }
        }

        Map[0].clear();
        Map[1].clear();
        ma.clear();    
        Min = Max = 0;

        for(i = 0; i < n; i++) {


            if(p[i].if_or_not == -2) {
                Min += p[i].fen;
                Max += p[i].fen;
            }else {
                buf = p[i].str;
                if(p[i].if_or_not > -1) {
                    if( p[i].time <= zty)
                        Map[ p[i].if_or_not ][ buf ] += p[i].fen;
                }
            }
        }

        for(i = 0; i < n; i++) {
            buf = p[i].str;
            
            if(p[i].if_or_not > -1) {
                if( ma[ buf ] )
                    continue;
                ma[ buf ] = 1;
            }

            if(p[i].if_or_not > -2) {
                if(p[i].if_or_not == -1 && p[i].time <= zty) {
                    Max += p[i].fen;
                    Min += p[i].fen;
                }else {
                    int u = Map[0][ buf ];
                    int d = Map[1][ buf ];
                    Min += u < d ? u : d;
                    Max += u > d ? u : d;
                }
            }
        }

        printf("%d TO %d\n", Min, Max);
    }
}
