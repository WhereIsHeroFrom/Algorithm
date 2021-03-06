#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int map[10][10], now[10][10], next[10][10];
int n, m;
int buf[100][100], Min[100][100];
vector < int > row, col;


void Process() {

    int i, j;
    if(Min[0][0] == -1) {
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                Min[j][i] = next[j][i];
            }
        }
    }

    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(next[j][i] < Min[j][i])
                break;
            if(next[j][i] > Min[j][i])
                return;
        }
        if(j < n)
            break;
    }

    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            Min[j][i] = next[j][i];
        }
    }

}

int main() {
    int t;
    int i, j;

    scanf("%d", &t);
    int ty = t;
    while(t--) {
        scanf("%d %d", &m, &n);
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &map[j][i]);
            }
        }
        Min[0][0] = -1;

        row.clear();
        col.clear();


        for(i = 0; i < m; i++) {
            col.push_back( i );
        }


        do {
            for(i = 0; i < m; i++) {
                for(j = 0; j < n; j++) {
                    now[j][i] = map[j][ col[i] ];
                }
            }
            
            row.clear();
            for(i = 0; i < n; i++) {
                row.push_back( i );
            }
            do {
                for(i = 0; i < n; i++) {
                    for(j = 0; j < m; j++) {
                        next[i][j] = now[ row[i] ][ j ];
                    }
                }
                Process();
            }while( next_permutation(row.begin(), row.end() ) );

        }while( next_permutation(col.begin(), col.end() ) );

        printf("Scenario #%d:\n", ty - t);

        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                if(i || j)
                    printf(" ");
                printf("%d", Min[j][i]);
            }
        }
        puts("\n");


    }

}
