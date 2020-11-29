#include <iostream>
#include <vector>
using namespace std;

#define LL __int64
#define MAXN 65540

int f[MAXN], primes[MAXN], pcnt;
 
LL GCD(LL a, LL b) {
    return b ? GCD(b, a%b) : a;
}

LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

void primeFilter() {
    f[0] = f[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if( !f[i] ) {
            primes[ pcnt++ ] = i;
            for(int j = i+i; j < MAXN; j += i) {
                f[j] = 1;
            }
        }
    }
}

LL Euler(LL n) {
    if(n <= 1) {
        return n;
    }
    LL ans = 1;

    for(int i = 0; i < pcnt; i++) {
        if(n % primes[i] == 0) {
            n /= primes[i];
            ans *= (primes[i] - 1);
            while ( n % primes[i] == 0 ) {
                n /= primes[i];
                ans *= primes[i];
            }

            if(n == 1) {
                return ans;
            }
        }
    }
    if(n != 1) {
        ans *= (n - 1);
    }
    return ans;
}

//计算 a*b % n
LL Produc_Mod(LL a, LL b, LL mod) {
    LL sum = 0;
    while(b) {
        if(b & 1) sum = (sum + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return sum;
}

  
//计算a^b % n
LL Power(LL a, LL b, LL mod) {
    LL sum = 1;
    while(b) {
        if(b & 1) sum = Produc_Mod(sum, a, mod);
        a = Produc_Mod(a, a, mod);
        b >>= 1;
    }
    return sum;
}

struct factor {
    int p, cnt;
    factor() {}
    factor(int _p, int _c) {
        p = _p;
        cnt = _c;
    }
};

void factor_split(int n, vector <factor>& ans) {
    if(n <= 1) {
        return;
    }
    for(int i = 0; i < pcnt; i++) {
        if(n % primes[i] == 0) {
            int cnt = 0;
            while ( n % primes[i] == 0 ) {
                n /= primes[i];
                cnt ++;
            }
            ans.push_back( factor(primes[i], cnt) );
            
            if(n == 1) {
                return ;
            }
        }
    }
    if(n != 1) {
       ans.push_back( factor(n, 1) );   
    }
}

// 上面的代码都是模板



 
// 三个数，小的那个是small，大的那个是big，求总共多少种排列情况 
int solve(int small, int big) {
    if(small == big) {
        return 1;
    }
    return (3 * 2 * 1) * (big - small - 1) + 3 + 3;
}

int main() {
    int T;
    int G, L;
    int i;
    primeFilter();
    
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &G, &L);
        
        if(L % G) {
            puts("0");
            continue;
        }
        
        vector <factor> ans;
        factor_split(L, ans);
        int v = 1;
        for(i = 0; i < ans.size(); i++) {
            int cnt = 0;
            while( G % ans[i].p == 0 ) {
                G /= ans[i].p;
                cnt ++;
            }
            v *= solve(cnt, ans[i].cnt);
        }
        printf("%d\n", v);
    }
    return 0;
}
