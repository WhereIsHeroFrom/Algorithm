#include <iostream>
#include <queue>
using namespace std;

int t;

struct point {
    int bar[4];
    int top;
    int poi[4];
    int num;
}temp, tt;

queue < point > q;

int a[ 4 ][ 100 ];
int num[ 4 ];
int hash[ 41 ][ 41 ][ 41 ][ 41 ];
int T;
int main() {
    int t;
    int i, j, k, l;
    scanf("%d", &t);

    while( t-- ) {

        for(i = 0; i < 4; i++) {
            scanf("%d", &num[i] );
            for(j = 0; j < num[i]; j++) {
                scanf("%d", &a[i][j]);
            }
        }

        for(i = 0; i <= num[0]; i ++) {
            for(j = 0; j <= num[1]; j ++) {
                for(k = 0; k <= num[2]; k ++) {
                    for(l = 0; l <= num[3]; l ++) {
                        hash[i][j][k][l] = -1;
                    }
                }
            }
        }

        temp.top = 0;
        temp.poi[0] = temp.poi[1] = temp.poi[2] = temp.poi[3] = 0;
        temp.num  = 0;

        q.push( temp );

        int Max = 0;
        while( !q.empty() ) {
            temp = q.front();
            q.pop();
            
            if( temp.num > Max )
                Max = temp.num;
            for(i = 0; i < 4; i++) {
                tt = temp;

                if( tt.poi[i] >= num[ i ] )
                    continue;

                if( tt.top && tt.bar[ tt.top-1 ] == a[i][ tt.poi[i] ] ) {
                    tt.poi[i] ++;
                    tt.top --;
                    tt.num += 2;
                    if( tt.num > hash[ tt.poi[0] ][ tt.poi[1] ][ tt.poi[2] ][ tt.poi[3] ] ) {
                        hash[ tt.poi[0] ][ tt.poi[1] ][ tt.poi[2] ][ tt.poi[3] ] = tt.num;
                        q.push( tt );
                    }
                }else {

                    if( tt.top == 4 )
                        continue;
                    tt.bar[ tt.top++ ] = a[i][ tt.poi[i]++ ];
                    if( tt.num > hash[ tt.poi[0] ][ tt.poi[1] ][ tt.poi[2] ][ tt.poi[3] ] ) {
                        hash[ tt.poi[0] ][ tt.poi[1] ][ tt.poi[2] ][ tt.poi[3] ] = tt.num;
                        q.push( tt );
                    }
                }
            }
        }

        printf("%d\n", Max);
    }

    return 0;
}

