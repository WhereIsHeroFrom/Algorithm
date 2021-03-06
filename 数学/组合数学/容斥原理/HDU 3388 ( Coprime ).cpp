#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 65540
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

struct factor {
    int prime, count;
    factor() {
    } 
    factor(int p, int c) {
        prime = p;
        count = c;
    }
    void print() {
        printf("(%d, %d)\n", prime, count);
    }
};

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for(int i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            primes[ ++primes[0] ] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for(LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

// 因式分解 - 将n分解成素数幂乘积的形式
// 举例：
// 252 = (2^2) * (3^2) * (7^1) 
// 则 ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
    ans.clear();
    if(n == 1) {
        return ;
    }
    // 素数试除 
    for(int i = 1; i <= primes[0]; i++) {
        if(n % primes[i] == 0) {
            factor f(primes[i], 0);
            while( !(n % primes[i]) ) {
                n /= primes[i];
                f.count ++;
            }
            ans.push_back(f);
        }
        if(n == 1) {
            return ;
        }
    }
    // 漏网之素数， 即大于MAXP的素数，最多1个 
    ans.push_back( factor(n, 1) );
}

 
// 容斥原理 - 求[1, n]中和m互素的数的个数
// 其中m的素因子为p[...]
// 参数 
// depth - 递归深度
// n     - 上述n
// mul   - 容斥时候的分母乘积
// op    - 容斥时候的符号(每取一个数就改变一次符号，对应递归中的异或) 
// p     - 素数列表
// ans   - 初始为0 

// 举例：
// 求[1, 9]中和6互素的数的个数，这时p = [2, 3] 
// ans = 9/1 - 9/2 - 9/3 + 9/6 = 3
// ans分为三部分，0个数的组合，1个数的组合，2个数的组合
 
void IncludeExclude(int depth, LL n, LL mul, int op, int* p, LL &ans) {
    // 小小优化 
    if(n < mul) {
        return ;
    }
    
    if(depth == p[0]) {
        ans += (op ? -1 : 1) * (n / mul);
        return ;
    }
    
    for(int i = 0; i < 2; i++) {
        // 0 表示不取, 1表示取 
        IncludeExclude( depth+1, n, mul * (i?p[depth+1]:1), op^i, p, ans );
    }
}

int n[2], k;
vector <factor> f[2];
int p[1000];
LL v;

void proc() {
    for(int i = 0; i < 2; i++)
        Factorization(n[i], f[i]);
    
    int idx[2] = {0, 0};
    while( idx[0] < f[0].size() || idx[1] < f[1].size() ) {
        if( idx[0] == f[0].size() ) {
            p[ ++p[0] ] = f[1][ idx[1]++ ].prime;
        }else if( idx[1] == f[1].size() ) {
            p[ ++p[0] ] = f[0][ idx[0]++ ].prime;
        }else {
            int x0 = f[0][ idx[0] ].prime;
            int x1 = f[1][ idx[1] ].prime;
            if( x0 == x1 ) {
                p[ ++p[0] ] = x0;
                idx[0] ++, idx[1] ++;
            }else if(x0 < x1) {
                p[ ++p[0] ] = x0;
                idx[0] ++;
            }else {
                p[ ++p[0] ] = x1;
                idx[1] ++;
            }
        }
    }
}

int main() {
    Eratosthenes();
    int t, cases = 0;
    int i, j;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d %d %d", &n[0], &n[1], &k);
        p[0] = 0;
        proc();
    
        LL l = 1, r = (LL)(INT_MAX-10)*(LL)(INT_MAX-10);
        LL last;
        //for(i = 1; i <= p[0]; i++) printf("%d \n", p[i]);
        while(l <= r) {
            LL mid = (l + r) / 2;
            LL ans = 0;
            IncludeExclude(0, mid, 1, 0, p, ans);
            if(ans >= k) {
                r = mid - 1;
                last = mid;
            }else {
                l = mid + 1;
            }
        }
        
        printf("Case %d: %I64d\n", ++cases, last);
        
    }
    return 0;
}

/*
12

6 9 1
6 9 2
6 9 3
*/
