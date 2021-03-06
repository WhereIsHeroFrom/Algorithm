#include <iostream>
#include <cmath>
using namespace std;


__int64 n, a, b, x;

struct point {
    __int64 area;
    __int64 lenth;
    __int64 width;
}temp;

int main() {
    int t;

    scanf("%d", &t);

    while( t-- ) {
        scanf("%I64d", &n);

        n = (n + (__int64)4) / (__int64)5;

        double S = sqrt( n * 1.0 );

        b = S;
        __int64 i;

        temp.area = -1;

        for(i = b; ; i--) {
            if( i < 1 )
                break;
            a = (n + (i-1))/ i;
            b = i;
            if( (44 * a + 4) * (10 * b + 2) < temp.area || temp.area == -1 ) {
                temp.area = (44 * a + 4) * (10 * b + 2);
                a = (44 * a + 4);
                x = (10 * b + 2);

                if( a < x ) {
                    __int64 tp = a;
                    a = x;
                    x = tp;
                }

                temp.lenth = a;
                temp.width = x;
            }else if( (44 * a + 4) * (10 * b + 2) == temp.area ) {
                __int64 bufa = (44 * a + 4);
                __int64 bufb = (10 * b + 2);

                if( bufa < bufb ) {
                    __int64 tp = bufa;
                    bufa = bufb;
                    bufb = tp;
                }

                if( bufa - bufb < temp.lenth - temp.width ) {
                    temp.lenth = bufa;
                    temp.width = bufb;
                }
            }
            
            b = (n + (i-1))/ i;
            a = i;
            if( (44 * a + 4) * (10 * b + 2) < temp.area || temp.area == -1 ) {
                temp.area = (44 * a + 4) * (10 * b + 2);
                a = (44 * a + 4);
                x = (10 * b + 2);

                if( a < x ) {
                    __int64 tp = a;
                    a = x;
                    x = tp;
                }

                temp.lenth = a;
                temp.width = x;
            }else if( (44 * a + 4) * (10 * b + 2)  == temp.area ) {
                __int64 bufa = (44 * a + 4);
                __int64 bufb = (10 * b + 2);

                if( bufa < bufb ) {
                    __int64 tp = bufa;
                    bufa = bufb;
                    bufb = tp;
                }

                if( bufa - bufb < temp.lenth - temp.width ) {
                    temp.lenth = bufa;
                    temp.width = bufb;
                }
            }
        }

        printf("%I64d X %I64d = %I64d\n", temp.lenth, temp.width, temp.area);
    }
}

