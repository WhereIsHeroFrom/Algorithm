#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define LL __int64
#define MAXP 10010
#define MOD 19880502

// 二分快速幂 
LL mod(LL a, LL b, LL p) {
    if(!b) {
        return 1;
    }
    LL x = mod(a*a%p, b>>1, p);
    if(b&1) {
        x = x * a % p;
    }
    return x;
}

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
vector <factor> F[MAXP];

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    for(int i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            primes[ ++primes[0] ] = i;
            for(int j = i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

LL GCD(LL a, LL b) {
    return b ? GCD(b, a%b) : a;
}

// 扩展欧几里得
// aX + bY = 1 
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

LL Product_Mod(LL a, LL b, LL mod) {
    LL sum = 0;
    LL flag = b >= 0?1:-1;
    if(flag < 0) {
        b = -b;
    }
    while(b) {
        if(b & 1) sum = (sum + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return (sum * flag + mod) % mod;
}

// K = m[0] * x + r[0];
// K = m[1] * y + r[1];
// K = m[2] * z + r[2];

// 计算出y的表达式 m[0] * x - m[1] * y = r[1] - r[0];
// y = m[3] * v + r[3];


// 孙子定理 模板
// -1 表示无解 
LL chineseRemain(int n, LL mod[], LL rem[]) {
    LL lcm = 1;
    int i;
    // 1. 预处理，将所有的mod[]和rem[]都转化成正整数
    for(i = 0; i < n; ++i) {
        // K = x[i]*mod[i] + rem[i];     (K为最终解，x[i]为未知数)
        // a.除数取正 
        if(mod[i] < 0) {
            mod[i] = -mod[i];
        } 
        // b.余数取正
        rem[i] = (rem[i] % mod[i] + mod[i]) % mod[i];
    } 
    // 2.计算所有被模数的最小公倍数 
    for(i = 0; i < n; i++) {
        LL g = GCD(lcm, mod[i]);
        lcm = lcm / g * mod[i];
    }
    // 3.算法主流程 （令最终解为K） 
    //   枚举 i = 1 to n-1 
    //   1) 合并等式(0)和(i)， mod[0]*x[0] + rem[0]      = mod[i]*x[i] + rem[i];
    //                         mod[0]*x[0] - mod[i]*x[i] = rem[i] - rem[0];
    //                            A  *  X  +   B   * Y   = C;
    //   2) 根据扩展欧几里得，求得x[i] = Y = Y0 + A*t; 
    //   3) 将x[i]代入等式(i)，得到：   K = mod[0]*mod[i]*t + (rem[i]+mod[i]*Y0); 
    //   4) 更新等式(0)，    mod[0] = mod[0]*mod[i]
    //                       rem[0] = (rem[i]+mod[i]*Y0) % mod[0];
    //   5) n-1次迭代完毕，rem[0]就是最小非负整数解。 
    LL A, B, C, X, Y;
    for(i = 1; i < n; i++) {
        A = mod[0];
        B = -mod[i];
        C = rem[i] - rem[0];
        LL g = GCD(A, B);
        if( C % g ) {
            return -1;
        }
        // 等式两边同时除上g或-1，等式不变 
        A /= g, B /= g, C /= g;
        if(A < 0) {
            // 这一步是为了把A和B都转化成正数 
            A = -A, B = -B, C = -C;
            B = ((B % A) + A) % A;
        }
        ExpGcd(A, B, X, Y);
        Y = Product_Mod(Y, C, A);
        mod[0] = A * mod[i];
        rem[0] = (rem[i] +  Product_Mod(mod[i], Y, mod[0])) % mod[0];
    }
    return rem[0];
}
 
LL m[10], r[10];
int a[10];

int main() {
    Eratosthenes();
    int n, i, j;
    while(scanf("%d", &n) != EOF) {
        LL t = 1;
        for(i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        LL ans = 1;
        bool noAns = false;
        for(i = 1; i <= primes[0]; ++i) {
            int p = primes[i];
            for(j = 0; j < n; j++) {
                int v = a[j], cnt = 0;
                while(v % p == 0) {
                    v /= p;
                    ++cnt;
                }    
                m[j] = a[j];
                r[j] = cnt; 
            }
            LL ch = chineseRemain(n, m, r);
            if(ch == -1) {
                noAns = true;
                break;
            }else {
                ans = ans * mod(p, ch, MOD) % MOD;
            }
        }
        printf("%I64d\n", noAns?-1:ans);
        
    } 
    return 0;
}