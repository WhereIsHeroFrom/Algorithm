#include <iostream>

using namespace std;

int n;
int tri[410][810];
int sum[410][810];
int i, j, k;

int main() {

    int cas = 1;
    while( scanf("%d", &n) != EOF && n ) {
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= 2*i-1; j++) {
                scanf("%d", &tri[i][j]);
            }
        }

        for(i = 1; i <= n; i++) {
            for(j = 1; j <= 2*i-1; j++) {
                sum[i][j] = sum[i][j-1] + tri[i][j];
            }
        }

        int Min = INT_MIN;

        int coun = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= 2*i-1; j += 2) {

                int las = 0;
                for(k = 1; i + k - 1 <= n; k++ ) {
                    las += sum[ i+k-1 ][ j+ (k-1)*2 ] - sum[ i+k-1 ][ j-1 ];
                    if( las > Min )
                        Min = las;
                }
            }
        }

        for(i = n; i >= 2; i--) {
            for(j = 2; j <= 2*i; j += 2 ) {
                int las = 0;
                for(k = 1; i - k + 1 >= 2 && j - 2*(k-1) >= 2 && j <= 2*(i-k+1) - 2; k ++ ) {
                    las += sum[ i-k+1 ][ j ] - sum[ i-k+1 ][ j - 2*(k-1) - 1 ];

                    if( las > Min )
                        Min = las;
                }
            }
        }

        printf("%d. %d\n", cas++, Min);
    }
}
