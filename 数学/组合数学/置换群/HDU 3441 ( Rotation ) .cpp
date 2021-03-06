#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;


#define MAXP 65540
#define LL __int64
#define MOD ((LL)1000000007) 

LL A, C;

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
    bool operator<(const factor& f) {
        return prime < f.prime;
    }
};

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
    if(n <= 1) {
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

LL power(LL a, LL b, LL c) {
    if(b == 0) {
        return 1 % c; 
    }
    LL x = power(a*a%c, b/2, c);
    if(b&1)
        x = x * a % c;
    return x;
}

int ans;

int polyaPart(LL cnt, LL color, LL fac, LL facEula) {
    return facEula % MOD * power(color % MOD, cnt/fac, MOD) % MOD;
}

// 因式分解后递归枚举所有因子 
// 枚举因子的同时，枚举每个因子的欧拉函数 
void emunFactor(int depth, vector <factor> fact, LL n, LL color, LL now, LL eula) {
    if(fact.size() == depth) {
        //printf("%d %d\n", now, eula);
        ans = (ans + polyaPart(n, color, now, eula) ) % MOD;
        return ;
    }
    factor &f = fact[depth];
    int i;
    emunFactor(depth+1, fact, n, color, now, eula);
    eula *= (f.prime - 1);
    now *= f.prime;
    for(i = 1; i <= f.count; ++i) {
        emunFactor(depth+1, fact, n, color, now, eula);
        now *= f.prime;
        eula *= f.prime;
    }
}

void mergeFactor(vector<factor> v1, vector<factor> v2, vector<factor>& ans) {
    int i, j;
    ans.clear();
    
    // v[0]有的 
    for(i = 0; i < v1.size(); ++i) {
        for(j = 0; j < v2.size(); ++j) {
            if(v2[j].prime == v1[i].prime) {
                ans.push_back( factor(v1[i].prime, v1[i].count + v2[j].count) );
                break;
            }
        }
        if(j == v2.size()) {
            ans.push_back( v1[i] );
        }
    }

    /// v[0]没有的且v[1]有的 
    for(i = 0; i < v2.size(); ++i) {
        for(j = 0; j < v1.size(); ++j) {
            if(v2[i].prime == v1[j].prime) {
                break;
            }
        }
        if(j == v1.size()) {
            ans.push_back( v2[i] );
        }
    }
    
    /*for(i = 0; i < ans.size(); ++i) {
        ans[i].print();
    }*/
} 

void mergeSub(vector<factor> v1, vector<factor> v2, vector<factor>& ans) {
    ans.clear();
    int i, j;
    for(i = 0; i < v1.size(); ++i) {
        for(j = 0; j < v2.size(); ++j) {
            if(v1[i].prime == v2[j].prime) {
                ans.push_back( factor(v1[i].prime, v1[i].count - 2*v2[j].count) );
                break;
            }
        }
        if(j == v2.size()) {
            ans.push_back( v1[i] );
        }
    }
    
}

LL calcColor(LL B) {
    LL v = 0; 
    // 0度置换   B^2
    v = (v + power(C, B*B, MOD));
    // 90、180、270度置换  
    LL tmp;
    if(B & 1) {
        // 90 和 270
        tmp = 2*power(C, (B*B+3)/4, MOD) % MOD;
        v = (v + tmp) % MOD;
        
        // 180
        tmp = power(C, (B*B+1)/2, MOD) % MOD;
        v = (v + tmp) % MOD;
    }else {
        // 90 和 270
        tmp = 2*power(C, (B/2)*(B/2), MOD) % MOD;
        v = (v + tmp) % MOD;
        
        // 180
        tmp = power(C, B*B/2, MOD) % MOD;
        v = (v + tmp) % MOD; 
    }
    
    LL X,Y;
    ExpGcd(4, MOD, X, Y);
    X = (X % MOD + MOD) % MOD;
    X = (X * v) % MOD;
    
    
    LL K = (A*A-1)/B/B;
    // !!!!! K 可能大于int32，素因子分解不能直接求K的素因子 
    vector <factor> VS[3], VV, SS;
    Factorization((A-1), VS[0]);
    Factorization((A+1), VS[1]);
    mergeFactor(VS[0], VS[1], VV);
    Factorization(B, VS[2]);
    mergeSub(VV, VS[2], SS);
    
    ans = 0;
    emunFactor(0, SS, K, X, 1, 1);
    
    ExpGcd(K, MOD, X, Y);
    X = (X % MOD + MOD) % MOD;
    X = (X * ans) % MOD;
    
    return X * C % MOD;
}


// B*B*K + 1 = A*A
// 枚举每个B
void emunBFactor(LL& ret, int depth, vector <factor> fact, LL now) {
    if(fact.size() == depth) {
        //printf("B = %I64d\n", now);
        // now 就是每个枚举出来的B
        LL v = calcColor(now);
        //printf("v = %I64d\n", v);
        ret = (ret + v) % MOD;
        return ;
    }
    factor &f = fact[depth];
    int i;
    emunBFactor(ret, depth+1, fact, now);
    now *= f.prime;
    for(i = 1; i <= f.count/2; ++i) {
        emunBFactor(ret, depth+1, fact, now);
        now *= f.prime;
    }
}

LL solve() {
    if(A == 1) {
        return C;
    }
    int i, j;
    vector <factor> v[2], vv;
    Factorization(A-1, v[0]);
    Factorization(A+1, v[1]);
    mergeFactor(v[0], v[1], vv);
    
    LL ret = 0;
    emunBFactor(ret, 0, vv, 1);
    return ret;
}

int main() {
    Eratosthenes();
    int i, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        int aa, cc;
        scanf("%d %d", &aa, &cc);
        A = aa;
        C = cc;
        printf("Case %d: %I64d\n", ++cases, solve());
        
        /*LL vv = 0;
        for(LL B = 1; B <= A; ++B) {
            if( (A*A-1) % (B*B) == 0 ) {
                vv = (vv + calcColor(B) ) % MOD;
            }
        }
        printf("%I64d\n", vv);*/
    }
    return 0;
} 

/*
99911 12
*/
