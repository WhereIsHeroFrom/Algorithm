#include <iostream>

using namespace std;

int r, f, n;
char str[10000];
int F[1010][52], R[1010][52];

int main() {

    int i, j;
    while( scanf("%d %d", &r, &f) != EOF ) {

        if( !r && !f )
            break;


        scanf("%s", &str[1]);
        int len = strlen( &str[1] );
        n = len;

        for(i = 0; i < 1010; i++) {
            for(j = 0; j < 52; j++) {
                F[i][j] = R[i][j] = -1000000;
            }
        }

        F[1][0] = (str[1] == '1') ? 1 : 0;
        F[1][1] = (str[1] == '1') ? 0 : 1;
        
        R[1][0] = (str[1] == '1') ? 0 : 1;
        R[1][1] = (str[1] == '1') ? 1 : 0;

        int Max;

        for(i = 2; i <= len; i++) {

            Max = 0;
            for(j = 0; j <= f - 1; j++) {
                if( F[i-1][j] > Max )
                    Max = F[i-1][j];
            }
            if( Max + ((str[i] == '1') ? 0 : 1) > R[i][0] )
                R[i][0] = Max + ((str[i] == '1') ? 0 : 1);

            for(j = 1; j <= r; j++) {
                R[i][j] = R[i-1][j-1] + ((str[i] == '1') ? 1 : 0);
            }

            Max = 0;
            for(j = 0; j <= r - 1; j++) {
                if( R[i-1][j] > Max )
                    Max = R[i-1][j];
            }
            if( Max + ((str[i] == '1') ? 1 : 0) > F[i][0] )
                F[i][0] = Max + ((str[i] == '1') ? 1 : 0);

            for(j = 1; j <= f; j++) {
                F[i][j] = F[i-1][j-1] + ((str[i] == '1') ? 0 : 1);
            }
        }

        Max = 0;
        for(i = 0; i <= r; i++) {
            if(R[n][i] > Max)
                Max = R[n][i];
        }
        for(i = 0; i <= f; i++) {
            if(F[n][i] > Max)
                Max = F[n][i];
        }

        printf("%d\n", Max);
    }
}
