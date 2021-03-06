/*
仔细分析一下就可知道答案的分子不会超过3（假设N是100，
分子是4，那么1/50~1/100必定是以1为分子的最小的几个，
2/67~2/99(注意分母分子保持互质)必定是以2为分子的最小
的几个，3/76~3/100必定是以3为分子的最小的几个，总数加
起来已经超过100了，而K的值最大才100）。
      
方法：枚举分子，然后二分分母，计算某个即可。
*/

#include <iostream>

using namespace std;

#define ll __int64
 
int N, K;
int low, high, mid;
bool flag;

int gcd( int a, int b ) {
    int m = 1;
    while( m ) {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

ll Calc( ll d, ll m ) {
    ll num = 0;
    ll down;    // 下界
    // 计算小于 d / m 的有多少个
    
    //分子为1的情况      1 / P < d / m;   P > m / d;
    down = m / d + 1;
    num += N - down + 1;
    
    //分子为2的情况       2 / P < d / m;   P > m*2 / d;
    down = m*2 / d + 1;
    if( down <= N ) {
        if( down & 1 )
            num += ( N - down ) / 2 + 1;
        else
            num += ( N - down + 1 ) / 2;
    }

    if( down <= N ) {
        //分子为3的情况       3 / P < d / m;   P > m*3 / d;
        down = m*3 / d + 1;
        int A = 0;
        if( down % 3 == 0 ) {
            A += (N - down + 1) - ( (N - down + 3)/3 );
        }else if( down % 3 == 1 ) {
            A += (N - down + 1) - ( (N - down + 1)/3 );
        }else if( down % 3 == 2 ) 
            A += (N - down + 1) - ( (N - down + 2)/3 );
        if( A > 0 )
            num += A;
    }
    return num;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d %d", &N, &K );
        for( i = 1; i <= 4; i ++ ) {
            low = i + 1;
            high = N;
            flag = false;
            while( low <= high ) {
                mid = ( low + high ) / 2;
                int ans = Calc( i, mid );
                if( ans == K-1 && gcd(i, mid) == 1 ) {
                    flag = true;
                    break;
                }
                if( ans > K-1 ) {
                    low = mid + 1;
                }else 
                    high = mid - 1;
            }
            if( flag )
                break;
        }
        printf("%d/%d\n", i, mid );
    }
    return 0;
}

