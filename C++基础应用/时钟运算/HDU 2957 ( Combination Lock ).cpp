#include <iostream>

using namespace std;

int N;

int C( int from, int to ) {
    if( from < to )
        return ( N - (to - from) );
    return from - to;
}

int CC( int from, int to ) {
    if( from > to )
        return ( N - (from - to) );
    return to - from;
}

int T1, T2, T3;
int sum = 0;
int i;

int main() {
    while( scanf("%d %d %d %d", &N, &T1, &T2, &T3) != EOF ) {

        if( !N && !T1 && !T2 && !T3 )
            break;
        sum = 0;
        for(i = 0; i < N; i++) {
            sum += 2*N;
            if( i != T1 )
                sum += C( i, T1 );
            sum += N;
            sum += CC( T1, T2 );
            sum += C( T2, T3 );
        }
        printf("%.3lf\n", sum * 1.0 / N);

    }
}


