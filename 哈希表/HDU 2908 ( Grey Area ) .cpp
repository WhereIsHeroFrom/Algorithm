#include <iostream>

using namespace std;

int n, w;
int a[ 1000 ];
int i, j;
int hash[ 10000 ];

int main() {
    while( scanf("%d %d", &n, &w) != EOF ) {

        if( !n && !w )
            break;
        memset( hash, 0, sizeof( hash ));

        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            hash[ a[i] ] ++;
        }
        
        int sum = 0;
        double ans = 0;
        int coun;


        int Max = -1000000;
        for(i = 0;  ; i++) {

            int rt = 0;
            for(j = w * i; j < w * (i+1); j++) {
                sum += hash[j];
                rt += hash[j];
            }
            if( rt > Max )
                Max = rt;

            if( sum == n )
                break;
        }

        coun = i;

        sum = 0;
        for(i = 0; ; i ++  ) {

            int rt = 0;
            for(j = w * i; j < w * (i+1); j++) {
                sum += hash[j];
                rt += hash[j];
            }

            //printf("%d %d\n", rt, Max);
            ans += rt * 1.0 / Max * (coun - i) * 1.0 / coun;
            if( sum == n )
                break;
        }

        printf("%.11lf\n", ans + 0.01 );


    }
}
