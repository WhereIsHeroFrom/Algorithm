#include <iostream>
#include <algorithm>
using namespace std;
#define ll __int64
#define Maxn 40000

ll L[17][Maxn], l, N[17];
ll R[17][Maxn], r, M[17];
ll a[100], sum;

void dfsl( int depth, ll sum, int num, int Max ) {
    
    if( depth == Max ) {
        L[ num ][ N[ num ] ++ ] = sum;
        return ;
    }
    dfsl( depth+1, sum, num, Max );
    dfsl( depth+1, sum + a[depth], num + 1, Max );
}

void dfsr( int depth, ll sum, int num, int Max ) {
    
    if( depth == Max ) {
        R[ num ][ M[ num ] ++ ] = sum;
        return ;
    }
    dfsr( depth+1, sum, num, Max );
    dfsr( depth+1, sum + a[ l + depth ], num + 1, Max );
}

int Bin( int mod, int key ) {
    int low = 0;
    int high = M[ mod ] - 1;
    int mid;
    
    while( low <= high ) {
        mid = ( low + high ) / 2;
        if( key == R[ mod ][ mid ] )
            return mid;
        if( key > R[ mod ][ mid ] )
            low = mid + 1;
        else
            high = mid - 1;
    }
    return mid;
}

int lr;

int main() {
    int i, j, k;
    int n;
    while( scanf("%d", &n) != EOF ) {
        sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        l = n / 2;
        r = n - n / 2;
        
        lr = l > r ? l : r;
        
        for(i = 0; i < 17; i++) {
            N[i] = M[i] = 0;
        }
        dfsl( 0, 0, 0, l );
        dfsr( 0, 0, 0, r );
        
        /*for(i = 0; i <= l; i++) {
        printf("%d :", i);
        
          for(j = 0; j < N[i]; j++) {
          printf("%lld ", L[i][j]);
          }
          puts("");
          }
          for(i = 0; i <= r; i++) {
          printf("%d :", i);
          for(j = 0; j < M[i]; j++) {
          printf("%lld ", R[i][j]);
          }
          puts("");
    }*/
        
        int zong = 0;
        for(i = 0; i <= l; i++) {
            sort( L[i], L[i] + N[i] );
            zong = 1;
            for(j = 1; j < N[i]; j++) {
                if( L[i][j] != L[i][zong-1] )
                    L[i][ zong++ ] = L[i][j];
            }
            N[i] = zong;
        }
        
        
        for(i = 0; i <= r; i++) {
            sort( R[i], R[i] + M[i] );
            zong = 1;
            for(j = 1; j < M[i]; j++) {
                if( R[i][j] != R[i][zong-1] )
                    R[i][ zong++ ] = R[i][j];
            }
            M[i] = zong;
        }
        
        /*for(i = 0; i <= l; i++) {
        printf("%d :", i);
        
          for(j = 0; j < N[i]; j++) {
          printf("%lld ", L[i][j]);
          }
          puts("");
          }
          for(i = 0; i <= r; i++) {
          printf("%d :", i);
          for(j = 0; j < M[i]; j++) {
          printf("%lld ", R[i][j]);
          }
          puts("");
    }*/
        
        ll Min = -1;
        
        for(i = 0; i <= l; i++) {
            for(j = 0; j < N[i]; j++) {
                ll x = L[i][j];
                int Index = Bin( lr - i, sum / 2 - x );
                int op = Index - 5;
                if( op < 0 )
                    op = 0 ;
                
                for( k = op; k < op + 10 && k < M[ lr - i ]; k++) {
                    ll T;
                    T = 2 * (x + R[ lr-i ][ k ] ) - sum ;
                    if( T < 0 )
                        T = - T;
                    
                    if( T < Min || Min == -1 )
                        Min = T;
                }
            }
        }
        
        printf("%I64d\n", Min );
        
    }
    return 0;
}
