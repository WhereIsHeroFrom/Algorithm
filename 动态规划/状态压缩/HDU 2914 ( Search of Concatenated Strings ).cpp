#include <iostream>
#include <bitset>
using namespace std;

bitset < 5010 > dp[1<<12];

char A[ 15 ][ 22 ];
int LA[15];

int n, m;
int i, j, k;
char str[ 5010 ];
char buf[ 200 ];
bool hash[12][5010];

int main() {
    while( scanf("%d %d", &n, &m) != EOF && (n+m) ) {


        memset( hash, 0, sizeof( hash ));

        for(i = 0; i < n; i++) {
            scanf("%s", A[i]);
            LA[i] = strlen( A[i] );
        }    
        
        str[0] = '\0';
        for(i = 0; i < m; i++) {
            scanf("%s", buf);
            strcat( str, buf );
        }
        strcat( str, "#" );

        int len = strlen( str );

        for(i = 0; i < n; i++) {
            for(j = 0; j < len; j++) {

                for(k = 0; A[i][k] && str[j+k]; k ++) {
                    if( A[i][k] != str[j+k] ) {
                        break;
                    }
                }
                if( A[i][k] == 0 ) {
                    hash[i][j] = 1;
                }
            }
        }

        int l = (1 << n);

        for(i = 1; i < l; i++) {
            for(j = 0; j < len; j++)
                dp[i][j] = 0;
        }

        for(i = 0; i < len; i++) {
            dp[0][i] = 1;
        }
        int coun = 0;
        for(i = 0; i < l; i++) {
            for(j = 0; j < len; j++) {
                if( dp[i][j] ) {
                    for(k = 0; k < n; k++) {
                        int nex = ( i & (1<<k) );
                        if( !nex ) {
                            nex = ( i ^ (1<<k) );
                            if( hash[k][j] ) {
                                dp[ nex ][ j+LA[k] ] = 1;
                            }
                        }
                    }
                }
            }
        }
        for(j = 0; j < len; j++) {
            if( dp[l-1][j] )
                coun ++;
        }
        printf("%d\n", coun);
    }
    return 0;
}
